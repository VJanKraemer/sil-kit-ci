/* Copyright (c) 2022 Vector Informatik GmbH

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include <iostream>
#include <atomic>
#include <thread>
#include <future>
#include <mutex>
#include <condition_variable>

#include "silkit/services/all.hpp"
#include "silkit/services/orchestration/all.hpp"
#include "functional.hpp"

#include "SimTestHarness.hpp"
#include "GetTestPid.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace {
using namespace std::chrono_literals;
using namespace SilKit::Tests;

const std::chrono::nanoseconds expectedTime{10ms};

std::atomic<bool> wakeup{false};
std::mutex mx;
std::condition_variable cv;

TEST(ITest_AsyncSimTask, test_async_simtask_lockstep)
{
    // The async participant uses the CompleteSimTask calls to request next simulation step.
    // The sync participant will run as often as possible.
    // Async may not start a new SimTask before calling CompleteSimtask to complete the current one

    SimTestHarness testHarness({"Sync", "Async"}, MakeTestRegistryUri());

    std::atomic<std::chrono::nanoseconds> syncTimeNs{0ns};
    std::atomic<bool> done{false};
    std::atomic<int> numActiveSimtasks{0};
    std::atomic<int> numSyncSimtasks{0};

    auto* sync = testHarness.GetParticipant("Sync")->GetOrCreateLifecycleServiceWithTimeSync()->GetTimeSyncService();
    auto* asyncParticipant = testHarness.GetParticipant("Async");
    auto* async = testHarness.GetParticipant("Async")->GetOrCreateLifecycleServiceWithTimeSync()->GetTimeSyncService();

    sync->SetSimulationStepHandler([&numSyncSimtasks](auto) {
        // run as fast as possible
        numSyncSimtasks++;
    }, 1ms);


    async->SetSimulationStepHandlerAsync([&](auto now, auto) {
        std::cout << "Async SimTask now=" << now.count()
            << " numActiveSimtasks=" << numActiveSimtasks
            << " numSyncSimtasks=" << numSyncSimtasks
            << std::endl;

        syncTimeNs = now;
        numActiveSimtasks++;

        if (now == expectedTime)
        {
            //Only allow time progress up to expectedTime
            std::cout << "Stopping simulation at expected time" << std::endl;
            asyncParticipant->GetOrCreateSystemController()->Stop();
            {
                std::unique_lock<decltype(mx)> lock(mx);
                done = true;
                wakeup = true;
            }
            cv.notify_one();
        }
        if (now < expectedTime)
        {
            //tell our completer thread that this simTask needs a call to CompleteSimTask
            {
                std::unique_lock<decltype(mx)> lock(mx);
                wakeup = true;
            }
            cv.notify_one();
        }
    },1ms);

    auto completer = std::thread{[&](){
        while (!done && (syncTimeNs.load() < expectedTime))
        {
            std::unique_lock<decltype(mx)> lock(mx);
            cv.wait(lock, [] { return wakeup.load();});
            wakeup = false;
            if(done)
            {
                return;
            }
            std::cout <<"Completer numActiveSimtasks=" << numActiveSimtasks << std::endl;
            if(numActiveSimtasks != 1)
            {
                ASSERT_EQ(numActiveSimtasks,0 ) << "Only one SimTask should be active until CompleteSimTask is called";
                done = true;
            }
            numActiveSimtasks--;
            async->CompleteSimulationStep();
        }
    }};
    ASSERT_TRUE(testHarness.Run(5s)) << "TestSim Harness should not reach timeout"
        << " numActiveSimtasks=" << numActiveSimtasks
        << " numSyncSimtasks=" << numSyncSimtasks
        ;
    done=true;
    wakeup=true;
    cv.notify_all();
    if(completer.joinable())
    {
        completer.join();
    }
}

TEST(ITest_AsyncSimTask, test_async_simtask_nodeadlock)
{
    // The async participant uses the CompleteSimTask calls to request next simulation step.
    // The sync participant will be used to check the time progress

    SimTestHarness testHarness({"Sync", "Async"}, MakeTestRegistryUri());

    auto syncTimeNs{0ns};

    auto* sync = testHarness.GetParticipant("Sync")->GetOrCreateLifecycleServiceWithTimeSync()->GetTimeSyncService();
    auto* asyncParticipant = testHarness.GetParticipant("Async");
    auto* async = testHarness.GetParticipant("Async")->GetOrCreateLifecycleServiceWithTimeSync()->GetTimeSyncService();

    sync->SetSimulationStepHandler([&syncTimeNs](auto now) {
        std::cout << "Sync SimTask now=" << now.count() << std::endl;
        syncTimeNs = now;
    }, 1ms);

    async->SetSimulationStepHandlerAsync([&](auto now, auto) {
        std::cout << "Async SimTask now=" << now.count() 
            << " expectedTime=" << expectedTime.count()
            << std::endl;
        if (now == expectedTime)
        {
            std::cout << "Stopping simulation at expected time" << std::endl;
            asyncParticipant->GetOrCreateSystemController()->Stop();
        }
        if (now < expectedTime)
        {
            //Only allow time progress up to expectedTime
            async->CompleteSimulationStep();
        }
    },1ms);

    ASSERT_TRUE(testHarness.Run(5s)) << "TestSim Harness should not reach timeout";

    auto isSame = expectedTime == syncTimeNs;
    auto isOffByOne = syncTimeNs == (expectedTime + 1ms);
    ASSERT_TRUE(isSame || isOffByOne)
        << "Simulation time should be at most off by one expectedTime "
        << " (due to NextSimTask handling in distributed participants): "
        << " expectedTime=" << expectedTime.count()
        << " syncTime=" << syncTimeNs.count();
}

std::promise<bool> startupPromise;
std::promise<void> nextIterPromise;

auto BackgroundThread(SilKit::Services::Orchestration::ITimeSyncService* parti)
{
    while (true)
    {
        auto start = startupPromise.get_future();
        start.wait();
        if (!start.valid())
        {
            std::cout << "Background thread terminating" << std::endl;
            return;
        }
        if (start.get())
        {
            std::cout << "Background thread terminating" << std::endl;
            return;
        }
        else
        {
            std::cout << "Calling CompleteSimulationTask from background thread" << std::endl;
            parti->CompleteSimulationStep();
            startupPromise = decltype(startupPromise){}; // reset for next iteration
            nextIterPromise.set_value();
        }
    }
}

TEST(ITest_AsyncSimTask, test_async_simtask_completion_from_foreign_thread)
{
    // The async participant uses the ExecuteSimtaskNonBlocking and CompleteSimTask calls
    // The sync participant will be used to check the time progress

    SimTestHarness testHarness({"Sync", "Async"}, MakeTestRegistryUri());

    std::atomic<std::chrono::nanoseconds> syncTime{0ns};

    auto* sync = testHarness.GetParticipant("Sync")->GetOrCreateLifecycleServiceWithTimeSync()->GetTimeSyncService();
    auto* asyncParticipant = testHarness.GetParticipant("Async");
    auto* async = testHarness.GetParticipant("Async")->GetOrCreateLifecycleServiceWithTimeSync()->GetTimeSyncService();

    sync->SetSimulationStepHandler([&syncTime](auto now) {
        syncTime = now;
    }, 1ms);

    async->SetSimulationStepHandlerAsync([&](auto now, auto) {
        if (now == expectedTime)
        {
            std::cout << "Stopping simulation at expected time" << std::endl;
            asyncParticipant->GetOrCreateSystemController()->Stop();
            startupPromise.set_value(true);
            return;
        }

        if (now < expectedTime)
        {
            //Signal other thread to call CompleteSimTask
            startupPromise.set_value(syncTime.load() == expectedTime);
            //Wait until other thread has signaled
            auto nextIter = nextIterPromise.get_future();
            nextIter.wait();
            nextIter.get();
            nextIterPromise = decltype(nextIterPromise){};
        }
    }, 1ms);

    auto thread = std::thread{[&]() {
        BackgroundThread(async);
    }};

    ASSERT_TRUE(testHarness.Run(5s)) << "TestSim Harness should not reach time out";

    thread.join();
    const auto currentSyncTime = syncTime.load();
    auto isSame = expectedTime == currentSyncTime;
    auto isOffByOne = (currentSyncTime == (expectedTime + 1ms)) || (currentSyncTime == (expectedTime - 1ms));
    ASSERT_TRUE(isSame || isOffByOne)
        << "Simulation time should be at most off by one expectedTime "
        << " (due to NextSimTask handling in distributed participants): "
        << " expectedTime=" << expectedTime.count()
        << " syncTime=" << currentSyncTime.count();
}

TEST(ITest_AsyncSimTask, test_async_simtask_different_periods)
{
    // The async and sync participant use different time periods to validate the that a slower participant does
    // not execute its simtask too often.

    SimTestHarness testHarness({"Sync", "Async"}, MakeTestRegistryUri());

    auto syncTime{0ns};
    auto asyncTime{0ns};
    const int periodFactor = 10;

    auto* sync = testHarness.GetParticipant("Sync")->GetOrCreateLifecycleServiceWithTimeSync()->GetTimeSyncService();
    auto* asyncParticipant = testHarness.GetParticipant("Async");
    auto* async = testHarness.GetParticipant("Async")->GetOrCreateLifecycleServiceWithTimeSync()->GetTimeSyncService();
    int countSync = 0;
    int countAsync = 0;

    sync->SetSimulationStepHandler([&syncTime, &countSync](auto now) {
        syncTime = now;
        countSync++;
    }, 1ms);

    async->SetSimulationStepHandlerAsync([&](auto now, auto) {
        asyncTime = now;
        countAsync++;
        if (countAsync > periodFactor * 100000)
        {
            asyncParticipant->GetOrCreateSystemController()->Stop();
        }
        async->CompleteSimulationStep();
        },
    periodFactor * 1ms);
    // validate that they are called approximately equally often
    ASSERT_TRUE(std::abs(countAsync * periodFactor - countSync) < periodFactor);
}


TEST(ITest_AsyncSimTask, test_async_simtask_multiple_completion_calls)
{
    // Verify that multiple CompleteSimTask calls do not trigger malicious behaviour

    SimTestHarness testHarness({"Sync", "Async"}, MakeTestRegistryUri());

    auto syncTime{0ns};
    auto asyncTime{0ns};
    const int periodFactor = 7;

    auto* sync = testHarness.GetParticipant("Sync")->GetOrCreateLifecycleServiceWithTimeSync()->GetTimeSyncService();
    auto* asyncParticipant = testHarness.GetParticipant("Async");
    auto* async = testHarness.GetParticipant("Async")->GetOrCreateLifecycleServiceWithTimeSync()->GetTimeSyncService();
    int countSync = 0;
    int countAsync = 0;

    sync->SetSimulationStepHandler([&syncTime, &countSync](auto now) {
        ASSERT_TRUE(now - syncTime == 1ms);
        syncTime = now;
        countSync++;
    }, 1ms);

    async->SetSimulationStepHandlerAsync([&](auto now, auto) {
        ASSERT_TRUE(now - asyncTime == periodFactor * 1ms);
        asyncTime = now;
        countAsync++;
        if (countAsync > periodFactor * 100000)
        {
            asyncParticipant->GetOrCreateSystemController()->Stop();
        }
        async->CompleteSimulationStep();
        async->CompleteSimulationStep();
        async->CompleteSimulationStep();
        },
        periodFactor * 1ms);
    // validate that they are called approximately equally often
    ASSERT_TRUE(std::abs(countAsync * periodFactor - countSync) < periodFactor);
}
} // anonymous namespace