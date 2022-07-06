// Copyright (c) Vector Informatik GmbH. All rights reserved.

#include <chrono>

#include "gtest/gtest.h"

#include "SyncSerdes.hpp"

using namespace std::chrono_literals;

namespace {

TEST(MwVAsioSerdes, MwSync_ParticipantCommand)
{
    using namespace SilKit::Services::Orchestration;
    SilKit::Core::MessageBuffer buffer;

    ParticipantCommand in{7, ParticipantCommand::Kind::Restart};
    ParticipantCommand out{0, ParticipantCommand::Kind::Invalid};

    Serialize(buffer , in);
    Deserialize(buffer,out);

    EXPECT_EQ(in.participant, out.participant);
    EXPECT_EQ(in.kind, out.kind);
}

TEST(MwVAsioSerdes, MwSync_SystemCommand)
{
    using namespace SilKit::Services::Orchestration;
    SilKit::Core::MessageBuffer buffer;

    SystemCommand in{SystemCommand::Kind::Run};
    SystemCommand out{SystemCommand::Kind::Invalid};

    Serialize(buffer , in);
    Deserialize(buffer,out);

    EXPECT_EQ(in.kind, out.kind);
}

TEST(MwVAsioSerdes, MwSync_ParticipantStatus)
{
    using namespace SilKit::Services::Orchestration;
    SilKit::Core::MessageBuffer buffer;

    auto now = std::chrono::system_clock::now();
    decltype(now) nowUs = std::chrono::system_clock::time_point{std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch())};

    ParticipantStatus in;
    ParticipantStatus out{};

    in.participantName = "Name";
    in.state = ParticipantState::ReadyToRun;
    in.enterReason = "Finished initialization";
    in.enterTime = nowUs;
    in.refreshTime = nowUs;

    Serialize(buffer , in);
    Deserialize(buffer,out);

    EXPECT_EQ(in.participantName, out.participantName);
    EXPECT_EQ(in.state, out.state);
    EXPECT_EQ(in.enterReason, out.enterReason);
    EXPECT_EQ(in.enterTime, out.enterTime);
    EXPECT_EQ(in.refreshTime, out.refreshTime);
}

} // anonymous namespace
