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

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

#include "GetTestPid.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "silkit/SilKit.hpp"
#include "silkit/vendor/CreateSilKitRegistry.hpp"
#include "silkit/services/orchestration/ILifecycleService.hpp"
#include "silkit/services/all.hpp"
#include "silkit/services/orchestration/string_utils.hpp"

#include "ConfigurationTestUtils.hpp"
#include "ITestThreadSafeLogger.hpp"

namespace {

using namespace std::chrono_literals;
using namespace SilKit;
using namespace SilKit::Config;
using namespace SilKit::Services::PubSub;
using namespace SilKit::Services::Orchestration;
using namespace SilKit::Tests;

const std::string systemMasterName{"SystemMaster"};
uint64_t numMsgToPublishPerController;
uint64_t numMsgToReceiveTotal;

const std::chrono::milliseconds communicationTimeout{5000s};

class TestParticipant
{
public:
    TestParticipant(const TestParticipant&) = delete;
    TestParticipant& operator=(const TestParticipant&) = delete;
    TestParticipant(TestParticipant&&) = default;
    TestParticipant& operator=(TestParticipant&&) = default;

    TestParticipant(const std::string& newName, std::vector<std::string> newPubTopics,
                    std::vector<std::string> newSubTopics)
    {
        name = newName;
        pubTopics = newPubTopics;
        subTopics = newSubTopics;

        if (pubTopics.size() > 0)
        {
            pubControllers.reserve(pubTopics.size());
            hasPubControllers = true;
        }

        if (subTopics.size() > 0)
        {
            subControllers.reserve(subTopics.size());
            hasSubControllers = true;
        }
        else
        {
            AffirmCommunication();
        }
    }
    ~TestParticipant()
    {
        if (preSimulationWorker.joinable())
        {
            preSimulationWorker.join();
        }
    }

    void ResetReception()
    {
        receiveMsgCount = 0;
        allReceivedPromise = std::promise<void>{};
        allReceived = false;
    }

    void AffirmCommunication()
    {
        allReceived = true;
        allReceivedPromise.set_value();
    }

    void AwaitCommunication()
    {
        auto futureStatus = allReceivedPromise.get_future().wait_for(communicationTimeout);
        EXPECT_EQ(futureStatus, std::future_status::ready) << "Test Failure: Awaiting test communication timed out";
    }

    void AffirmAllDone()
    {
        if (!allDone)
        {
            allDone = true;
            allDonePromise.set_value();
        }
    }

    void AwaitAllDone()
    {
        auto futureStatus = allDonePromise.get_future().wait_for(communicationTimeout);
        EXPECT_EQ(futureStatus, std::future_status::ready) << "Test Failure: Awaiting all done timed out";
    }

    void Publish()
    {
        Log() << "[" << name << "] Start publishing...";
        // Publish in reversed order that lastly created publishers come first
        for (auto publisher = pubControllers.rbegin(); publisher != pubControllers.rend(); ++publisher)
        {
            for (uint64_t i = 0; i < numMsgToPublishPerController; i++)
            {
                (*publisher)->Publish(std::vector<uint8_t>{0});
            }
        }
        Log() << "[" << name << "] ...all published";
    }

    //Participant's entry point
    void ThreadMain( const std::string& registryUri)
    {
        participant =
            SilKit::CreateParticipant(SilKit::Config::MakeParticipantConfigurationWithLogging(Services::Logging::Level::Warn), name, registryUri);

        LifecycleConfiguration lc{};
        lc.operationMode = OperationMode::Coordinated;
        lifecycleService = participant->CreateLifecycleService(lc);
        auto* timeSyncService = lifecycleService->CreateTimeSyncService();

        // We need to create a dedicated thread, so we do not block the 
        // CommunicationReadyHandlerAsync when we communication becomes ready.
        preSimulationStart = preSimulationPromise.get_future();
        preSimulationWorker = std::thread{[this] {
            preSimulationStart.wait_for(communicationTimeout);

            if (hasPubControllers)
            {
                Publish();
            }

            if (hasSubControllers)
            {
                AwaitCommunication();
            }

            lifecycleService->CompleteCommunicationReadyHandlerAsync();
        }};

        lifecycleService->SetCommunicationReadyHandlerAsync([this]() {
            Log() << "[" << name << "] CommunicationReadyHandlerAsync: invoking preSimulationWorker";
            preSimulationPromise.set_value();
        });

        lifecycleService->SetStopHandler([this]() {
            Log() << "[" << name << "] StopHandler";
        });

        lifecycleService->SetShutdownHandler([this]() {
            Log() << "[" << name << "] ShutdownHandler";
        });

        if (hasPubControllers)
        {
            Log() << "[" << name << "] Creating publishers...";
            uint32_t controllerIndex = 0;
            for (auto& topic : pubTopics)
            {
                const DataPublisherSpec spec{topic, ""};
                const auto controllerName = "Pub-" + std::to_string(controllerIndex);
                controllerIndex++;
                pubControllers.push_back(participant->CreateDataPublisher(controllerName, spec));
            }
            Log() << "[" << name << "] ...created publishers";
        }

        if (hasSubControllers)
        {
            Log() << "[" << name << "] Creating subscribers...";
            uint32_t controllerIndex = 0;
            for (auto& topic : subTopics)
            {
                const DataSubscriberSpec spec{topic, ""};
                const auto controllerName = "Sub-" + std::to_string(controllerIndex);
                controllerIndex++;
                subControllers.push_back(participant->CreateDataSubscriber(
                    controllerName, spec,
                    [this](IDataSubscriber* /*subscriber*/, const DataMessageEvent& /*dataMessageEvent*/) {
                        if (!allReceived)
                        {
                            receiveMsgCount++;
                            if (receiveMsgCount >= numMsgToReceiveTotal)
                            {
                                Log() << "[" << name << "] All received";
                                AffirmCommunication();
                            }
                        }
                    }));
            }
            Log() << "[" << name << "] ...created subscribers";
        }

        timeSyncService->SetSimulationStepHandler(
            [this](std::chrono::nanoseconds /*now*/) {
                AffirmAllDone();
            }, 1s);

        auto finalStateFuture = lifecycleService->StartLifecycle();
        Log() << "[" << name << "] Started Lifecycle";

        finalStateFuture.get();
    }

    auto Name() const -> std::string { return name; }

private: //Members
    std::string name;
    std::unique_ptr<IParticipant> participant;
    Services::Orchestration::ILifecycleService* lifecycleService{nullptr};
    std::vector<IDataPublisher*> pubControllers;
    std::vector<IDataSubscriber*> subControllers;
    std::vector<std::string> pubTopics;
    std::vector<std::string> subTopics;

    bool hasPubControllers = false;
    bool hasSubControllers = false;

    uint64_t receiveMsgCount = 0;

    bool allReceived{false};
    std::promise<void> allReceivedPromise = std::promise<void>{};

    bool allDone{false};
    std::promise<void> allDonePromise = std::promise<void>{};

    // allow communication before the simulation enters the actual running state
    std::promise<void> preSimulationPromise;
    std::future<void> preSimulationStart;
    std::thread preSimulationWorker;
};

class ITest_CommunicationReady : public testing::Test
{
protected:
    ITest_CommunicationReady() {}

    struct SystemMaster
    {
        ILifecycleService* lifecycleService;
        std::unique_ptr<IParticipant> participant;
        ISystemController* systemController;
        ISystemMonitor* systemMonitor;

        std::promise<void> systemStateRunningPromise;
        std::future<void> systemStateRunning;
    };

    void SystemStateHandler(SystemState newState)
    {
        switch (newState)
        {
        case SystemState::Error:
            Log() << "SystemState = " << newState;
            AbortAndFailTest("Reached SystemState::Error");
            break;
        case SystemState::Running:
            Log() << "SystemState = " << newState;
            systemMaster.systemStateRunningPromise.set_value();
            break;
        default:
            Log() << "SystemState = " << newState;
            break;
        }
    }

    void AbortAndFailTest(const std::string& reason)
    {
        systemMaster.systemController->AbortSimulation();
        FAIL() << reason;
    }

    void RunRegistry(const std::string& registryUri)
    {
        registry = SilKit::Vendor::Vector::CreateSilKitRegistry(SilKit::Config::MakeEmptyParticipantConfiguration());
        registry->StartListening(registryUri);
    }

    void RunSystemMaster(const std::string& registryUri)
    {
        systemMaster.participant = SilKit::CreateParticipant(SilKit::Config::MakeEmptyParticipantConfiguration(),
                                                             systemMasterName, registryUri);

        LifecycleConfiguration lc{};
        lc.operationMode = OperationMode::Coordinated;
        systemMaster.lifecycleService = systemMaster.participant->CreateLifecycleService(lc);
        systemMaster.systemController = systemMaster.participant->CreateSystemController();
        systemMaster.systemMonitor = systemMaster.participant->CreateSystemMonitor();

        systemMaster.systemController->SetWorkflowConfiguration({participantNames});

        systemMaster.systemMonitor->AddSystemStateHandler([this](SystemState newState) {
            SystemStateHandler(newState);
        });

        systemMaster.systemStateRunning = systemMaster.systemStateRunningPromise.get_future();

        systemMaster.lifecycleService->StartLifecycle();
    }

    void RunParticipantThreads(std::vector<TestParticipant>& participants, const std::string& registryUri)
    {
        for (auto& p : participants)
        {
            participantThreads.emplace_back(
                [&p, registryUri] { p.ThreadMain(registryUri); });
        }
    }

    void JoinParticipantThreads()
    {
        for (auto&& thread : participantThreads)
        {
            thread.join();
        }
        participantThreads.clear();
    }

    void SetupSystem(const std::string& registryUri, std::vector<TestParticipant>& participants)
    {
        for (auto&& p : participants)
        {
            participantNames.push_back(p.Name());
        }
        participantNames.push_back(systemMasterName);

        RunRegistry(registryUri);
        RunSystemMaster(registryUri);
    }

    void ShutdownSystem()
    {
        systemMaster.participant.reset();
        registry.reset();
    }

    void ExecuteTest(std::vector<TestParticipant>& participants)
    {
        try
        {
            auto registryUri = MakeTestRegistryUri();
            SetupSystem(registryUri, participants);
            RunParticipantThreads(participants, registryUri);
            Log() << ">> Await all done";
            for (auto& p : participants)
                p.AwaitAllDone();
            Log() << ">> SystemMaster: Waiting for SystemState::Running";
            ASSERT_EQ(systemMaster.systemStateRunning.wait_for(1s), std::future_status::ready);
            Log() << ">> SystemMaster: Stopping due to END-OF-TEST";
            systemMaster.lifecycleService->Stop("End of test");
            Log() << ">> Joining participant threads";
            JoinParticipantThreads();
            ShutdownSystem();
        }
        catch (const std::exception& error)
        {
            std::stringstream ss;
            ss << "Something went wrong: " << error.what();
            AbortAndFailTest(ss.str());
        }
    }

protected:
    std::vector<std::string> participantNames;
    std::unique_ptr<SilKit::Vendor::Vector::ISilKitRegistry> registry;
    SystemMaster systemMaster;
    std::vector<std::thread> participantThreads;
};

// Tests that basic pubsub communication in the CommunicationReadyHandler works
TEST_F(ITest_CommunicationReady, test_receive_in_comm_ready_handler)
{

    const uint32_t numPub = 1u;
    const uint32_t numSub = 1u;
    const std::string commonTopic = "Topic";

    numMsgToPublishPerController = 100u;
    numMsgToReceiveTotal = numMsgToPublishPerController * numPub * numSub;

    std::vector<std::string> pubTopics;
    for (uint32_t i = 0; i < numPub; i++)
    {
        pubTopics.push_back(commonTopic);
    }

    std::vector<std::string> subTopics;
    for (uint32_t i = 0; i < numSub; i++)
    {
        subTopics.push_back(commonTopic);
    }

    std::vector<TestParticipant> participants;
    participants.push_back({"Pub", pubTopics, {}});
    participants.push_back({"Sub", {}, subTopics});

    ExecuteTest(participants);
}

// Setup lots of publishers and 1 subscriber on each side that both sides are busy doing the subscription handshakes.
// The CommunicationReadyHandler should be delayed between CommunicationInitializing and CommunicationInitialized
// until all handshakes are done. E.g., with numPub = 10000:
//[2022-07-27 14:34:44.680] [PubSub1] [info] New ParticipantState: CommunicationInitializing; reason: Received SystemState::ServicesCreated
//[2022-07-27 14:35:16.269] [PubSub1] [info] New ParticipantState: CommunicationInitialized; reason: Received SystemState::CommunicationInitializing
TEST_F(ITest_CommunicationReady, test_delay_comm_ready_handler)
{

    const uint32_t numPub = 100u;
    const uint32_t numSub = 1u;
    const std::string topic1 = "Topic1";
    const std::string topic2 = "Topic2";

    numMsgToPublishPerController = 2u;
    numMsgToReceiveTotal = numMsgToPublishPerController * numPub * numSub;

    std::vector<std::string> pubTopics1;
    for (uint32_t i = 0; i < numPub; i++)
    {
        pubTopics1.push_back(topic1);
    }

    std::vector<std::string> pubTopics2;
    for (uint32_t i = 0; i < numPub; i++)
    {
        pubTopics2.push_back(topic2);
    }

    std::vector<TestParticipant> participants;
    participants.push_back({"PubSub1", pubTopics1, {topic2}});
    participants.push_back({"PubSub2", pubTopics2, {topic1}});

    ExecuteTest(participants);
}

} // anonymous namespace
