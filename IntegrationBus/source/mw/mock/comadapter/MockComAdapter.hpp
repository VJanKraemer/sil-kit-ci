// Copyright (c) Vector Informatik GmbH. All rights reserved.

#pragma once

#include <chrono>

#include "ib/mw/sync/SyncDatatypes.hpp"
#include "ib/mw/logging/LoggingDatatypes.hpp"
#include "ib/mw/logging/ILogger.hpp"
#include "ib/mw/sync/IParticipantController.hpp"
#include "ib/mw/sync/ISystemController.hpp"
#include "ib/mw/sync/ISystemMonitor.hpp"

#include "ib/sim/fwd_decl.hpp"
#include "ib/sim/can/CanDatatypes.hpp"
#include "ib/sim/eth/EthDatatypes.hpp"
#include "ib/sim/fr/FrDatatypes.hpp"
#include "ib/sim/lin/LinDatatypes.hpp"
#include "ib/sim/io/IoDatatypes.hpp"
#include "ib/sim/generic/GenericMessageDatatypes.hpp"
#include "ib/sim/data/DataMessageDatatypes.hpp"
#include "ib/sim/rpc/RpcDatatypes.hpp"

#include "TimeProvider.hpp"
#include "IComAdapterInternal.hpp"
#include "IServiceDiscovery.hpp"

#include "gtest/gtest.h"
#include "gmock/gmock.h"


#ifdef SendMessage
#undef SendMessage
#endif

namespace ib {
namespace mw {
namespace test {

class DummyLogger : public logging::ILogger
{
public:
    void Log(logging::Level /*level*/, const std::string& /*msg*/) override {}
    void Trace(const std::string& /*msg*/) override {}
    void Debug(const std::string& /*msg*/) override {}
    void Info(const std::string& /*msg*/) override {}
    void Warn(const std::string& /*msg*/) override {}
    void Error(const std::string& /*msg*/) override {}
    void Critical(const std::string& /*msg*/) override {}
    void RegisterRemoteLogging(const LogMsgHandlerT& /*handler*/) {}
    void LogReceivedMsg(const logging::LogMsg& /*msg*/) {}
protected:
    bool ShouldLog(logging::Level) const override { return true; }
};


class MockTimeProvider : public sync::ITimeProvider
{
public:
    struct MockTime
    {
        MOCK_METHOD0(Now, std::chrono::nanoseconds());
    };

    //XXX gtest 1.10 has a MOCK_METHOD macro with specifiers like const, noexcept.
    //    until then we use an auxiliary struct mockTime to get rid of "const this".
    auto Now() const -> std::chrono::nanoseconds override
    {
        return mockTime.Now();
    }
    auto TimeProviderName() const -> const std::string& override
    {
        return _name;
    }

    void RegisterNextSimStepHandler(NextSimStepHandlerT handler)
    {
        _handlers.emplace_back(std::move(handler));
    }

    std::vector<NextSimStepHandlerT> _handlers;
    const std::string _name = "MockTimeProvider";
    mutable MockTime mockTime;
};


class MockParticipantController : public sync::IParticipantController {
public:
    MOCK_METHOD1(SetInitHandler, void(InitHandlerT));
    MOCK_METHOD1(SetStopHandler, void(StopHandlerT));
    MOCK_METHOD1(SetShutdownHandler, void(ShutdownHandlerT));
    MOCK_METHOD1(SetSimulationTask, void(SimTaskT task));
    MOCK_METHOD1(SetSimulationTaskAsync, void(SimTaskT task));
    MOCK_METHOD0(CompleteSimulationTask, void());
    MOCK_METHOD1(SetSimulationTask, void(std::function<void(std::chrono::nanoseconds now)>));
    MOCK_METHOD0(EnableColdswap, void());
    MOCK_METHOD1(SetPeriod, void(std::chrono::nanoseconds period));
    MOCK_METHOD1(SetEarliestEventTime, void(std::chrono::nanoseconds eventTime));
    MOCK_METHOD0(Run, sync::ParticipantState());
    MOCK_METHOD0(RunAsync, std::future<sync::ParticipantState>());
    MOCK_METHOD1(ReportError, void(std::string errorMsg));
    MOCK_METHOD1(Pause, void(std::string reason));
    MOCK_METHOD0(Continue, void());
    MOCK_METHOD1(Stop, void(std::string reason));
    MOCK_CONST_METHOD0(State,  sync::ParticipantState());
    MOCK_CONST_METHOD0(Status, sync::ParticipantStatus&());
    MOCK_METHOD0(RefreshStatus, void());
    MOCK_CONST_METHOD0(Now, std::chrono::nanoseconds());
    MOCK_METHOD0(LogCurrentPerformanceStats, void());
    MOCK_METHOD1(ForceShutdown, void(std::string reason));
};

class MockSystemMonitor : public sync::ISystemMonitor {
public:
    MOCK_METHOD1(RegisterSystemStateHandler, void(SystemStateHandlerT));
    MOCK_METHOD1(RegisterParticipantStateHandler, void(ParticipantStateHandlerT));
    MOCK_METHOD1(RegisterParticipantStatusHandler, void(ParticipantStatusHandlerT));
    MOCK_CONST_METHOD0(SystemState,  sync::SystemState());
    MOCK_CONST_METHOD1(ParticipantStatus, const sync::ParticipantStatus&(const std::string& participantId));
};

class MockSystemController : public sync::ISystemController {
public:
    MOCK_CONST_METHOD1(Initialize, void(ParticipantId participantId));
    MOCK_CONST_METHOD1(ReInitialize, void(ParticipantId participantId));
    MOCK_METHOD(void, Initialize, (const std::string& participantId), (const, override));
    MOCK_METHOD(void, ReInitialize, (const std::string& participantId), (const, override));
    MOCK_CONST_METHOD0(Run, void());
    MOCK_CONST_METHOD0(Stop, void());
    MOCK_CONST_METHOD0(Shutdown, void());
    MOCK_CONST_METHOD0(PrepareColdswap, void());
    MOCK_CONST_METHOD0(ExecuteColdswap, void());
};

class MockServiceDiscovery : public service::IServiceDiscovery
{
public:
    MOCK_METHOD(void, NotifyServiceCreated, (const ServiceDescriptor& serviceDescriptor), (override));
    MOCK_METHOD(void, NotifyServiceRemoved, (const ServiceDescriptor& serviceDescriptor), (override));
    MOCK_METHOD(void, RegisterServiceDiscoveryHandler, (ServiceDiscoveryHandlerT handler), (override));
};

class DummyComAdapter : public IComAdapterInternal
{
public:
    DummyComAdapter()
    {
    }

    auto CreateCanController(const std::string& /*canonicalName*/) -> sim::can::ICanController* override { return nullptr; }
    auto CreateEthController(const std::string& /*canonicalName*/) -> sim::eth::IEthController* override { return nullptr; }
    auto CreateFlexrayController(const std::string& /*canonicalName*/) -> sim::fr::IFrController* override { return nullptr; }
    auto CreateLinController(const std::string& /*canonicalName*/) -> sim::lin::ILinController* override { return nullptr; }
    auto CreateAnalogIn(const std::string& /*canonicalName*/) -> sim::io::IAnalogInPort* override { return nullptr; }
    auto CreateDigitalIn(const std::string& /*canonicalName*/) -> sim::io::IDigitalInPort* override { return nullptr; }
    auto CreatePwmIn(const std::string& /*canonicalName*/) -> sim::io::IPwmInPort* override { return nullptr; }
    auto CreatePatternIn(const std::string& /*canonicalName*/) -> sim::io::IPatternInPort* override { return nullptr; }
    auto CreateAnalogOut(const std::string& /*canonicalName*/) -> sim::io::IAnalogOutPort* override { return nullptr; }
    auto CreateDigitalOut(const std::string& /*canonicalName*/) -> sim::io::IDigitalOutPort* override { return nullptr; }
    auto CreatePwmOut(const std::string& /*canonicalName*/) -> sim::io::IPwmOutPort* override { return nullptr; }
    auto CreatePatternOut(const std::string& /*canonicalName*/) -> sim::io::IPatternOutPort* override { return nullptr; }
    auto CreateGenericPublisher(const std::string& /*canonicalName*/) -> sim::generic::IGenericPublisher* override { return nullptr; }
    auto CreateGenericSubscriber(const std::string& /*canonicalName*/) -> sim::generic::IGenericSubscriber* override { return nullptr; }
    auto CreateDataPublisher(const std::string& /*canonicalName*/,
                             const sim::data::DataExchangeFormat& /*dataExchangeFormat*/, size_t /* history */)
        -> sim::data::IDataPublisher* override
    {
        return nullptr;
    }
    auto CreateDataSubscriber(const std::string& /*canonicalName*/,
                              const sim::data::DataExchangeFormat& /*dataExchangeFormat*/,
                              sim::data::CallbackExchangeFormatT /* callback*/) -> sim::data::IDataSubscriber* override
    {
        return nullptr;
    }
    auto CreateDataSubscriberInternal(const std::string& canonicalName, const std::string& linkName,
                                      const sim::data::DataExchangeFormat& dataExchangeFormat,
                                      sim::data::CallbackExchangeFormatT /*callback*/)
        -> sim::data::IDataSubscriber* override
    {
        return nullptr;
    }
    auto CreateRpcClient(const std::string& /*functionName*/, const ib::sim::rpc::RpcExchangeFormat /*exchangeFormat*/,
                         ib::sim::rpc::CallReturnHandler /*handler*/) -> ib::sim::rpc::IRpcClient* override
    {
        return nullptr;
    }
    auto CreateRpcServer(const std::string& functionName, const ib::sim::rpc::RpcExchangeFormat exchangeFormat,
                         ib::sim::rpc::CallProcessor handler) -> ib::sim::rpc::IRpcServer* override
    {
        return nullptr;
    }
    auto CreateRpcServerInternal(const std::string& functionName, const std::string& linkName,
                                 const sim::rpc::RpcExchangeFormat exchangeFormat, sim::rpc::CallProcessor handler,
                                 sim::rpc::IRpcServer* parent) -> ib::sim::rpc::RpcServerInternal* override
    {
        return nullptr;
    }

    auto GetParticipantController() -> sync::IParticipantController* override { return &mockParticipantController; }
    auto GetSystemMonitor() -> sync::ISystemMonitor* override { return &mockSystemMonitor; }
    auto GetSystemController() -> sync::ISystemController* override { return &mockSystemController; }

    auto GetLogger() -> logging::ILogger* override { return &logger; }

    void RegisterCanSimulator(sim::can::IIbToCanSimulator* ) override {}
    void RegisterEthSimulator(sim::eth::IIbToEthSimulator* ) override {}
    void RegisterFlexraySimulator(sim::fr::IIbToFrBusSimulator* ) override {}
    void RegisterLinSimulator(sim::lin::IIbToLinSimulator*) override {}

    void SendIbMessage(const IIbServiceEndpoint* /*from*/, sim::can::CanMessage&& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const sim::can::CanMessage& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const sim::can::CanTransmitAcknowledge& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const sim::can::CanControllerStatus& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const sim::can::CanConfigureBaudrate& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const sim::can::CanSetControllerMode& /*msg*/) override {}
                        
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, sim::eth::EthMessage&& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const sim::eth::EthMessage& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const sim::eth::EthTransmitAcknowledge& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const sim::eth::EthStatus& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const sim::eth::EthSetMode& /*msg*/) override {}
                        
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, sim::fr::FrMessage&& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const sim::fr::FrMessage& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, sim::fr::FrMessageAck&& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const sim::fr::FrMessageAck& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const sim::fr::FrSymbol& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const sim::fr::FrSymbolAck& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const sim::fr::CycleStart& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const sim::fr::HostCommand& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const sim::fr::ControllerConfig& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const sim::fr::TxBufferConfigUpdate& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const sim::fr::TxBufferUpdate& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const sim::fr::ControllerStatus& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const sim::fr::PocStatus& /*msg*/) override {}
                        
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const sim::lin::SendFrameRequest& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const sim::lin::SendFrameHeaderRequest& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const sim::lin::Transmission& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const sim::lin::FrameResponseUpdate& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const sim::lin::ControllerConfig& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const sim::lin::ControllerStatusUpdate& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const sim::lin::WakeupPulse& /*msg*/) override {}
                        
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const sim::io::AnalogIoMessage& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const sim::io::DigitalIoMessage& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, sim::io::PatternIoMessage&& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const sim::io::PatternIoMessage& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const sim::io::PwmIoMessage& /*msg*/) override {}
                        
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, sim::generic::GenericMessage&& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const sim::generic::GenericMessage& /*msg*/) override {}

    void SendIbMessage(const IIbServiceEndpoint* /*from*/, sim::data::DataMessage&& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const sim::data::DataMessage& /*msg*/) override {}
    virtual void SendIbMessage_proxy(const IIbServiceEndpoint* /*from*/, const sim::data::DataMessage& /*msg*/) {}
    void SendIbMessage(const ib::mw::IIbServiceEndpoint* /*from*/, const sim::data::PublisherAnnouncement& /*msg*/) override {}
    void SendIbMessage(const ib::mw::IIbServiceEndpoint* /*from*/, sim::data::PublisherAnnouncement&& /*msg*/) override {}

    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const sim::rpc::ClientAnnouncement& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, sim::rpc::ClientAnnouncement&& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const sim::rpc::ServerAcknowledge& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, sim::rpc::ServerAcknowledge&& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const sim::rpc::FunctionCall& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, sim::rpc::FunctionCall&& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const sim::rpc::FunctionCallResponse& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, sim::rpc::FunctionCallResponse&& /*msg*/) override {}

    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const sync::NextSimTask& /*msg*/) {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const sync::ParticipantStatus& /*msg*/) {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const sync::ParticipantCommand& /*msg*/) {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const sync::SystemCommand& /*msg*/) {}
                        
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, logging::LogMsg&& /*msg*/) {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const logging::LogMsg& /*msg*/) {}

    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const service::ServiceAnnouncement& /*msg*/) {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const service::ServiceDiscoveryEvent& /*msg*/) {}

    // targeted messaging

    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, sim::can::CanMessage&& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, const sim::can::CanMessage& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, const sim::can::CanTransmitAcknowledge& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, const sim::can::CanControllerStatus& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, const sim::can::CanConfigureBaudrate& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, const sim::can::CanSetControllerMode& /*msg*/) override {}

    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, sim::eth::EthMessage&& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, const sim::eth::EthMessage& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, const sim::eth::EthTransmitAcknowledge& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, const sim::eth::EthStatus& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, const sim::eth::EthSetMode& /*msg*/) override {}

    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, sim::fr::FrMessage&& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, const sim::fr::FrMessage& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, sim::fr::FrMessageAck&& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, const sim::fr::FrMessageAck& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, const sim::fr::FrSymbol& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, const sim::fr::FrSymbolAck& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, const sim::fr::CycleStart& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, const sim::fr::HostCommand& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, const sim::fr::ControllerConfig& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, const sim::fr::TxBufferConfigUpdate& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, const sim::fr::TxBufferUpdate& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, const sim::fr::ControllerStatus& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, const sim::fr::PocStatus& /*msg*/) override {}

    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, const sim::lin::SendFrameRequest& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, const sim::lin::SendFrameHeaderRequest& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, const sim::lin::Transmission& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, const sim::lin::FrameResponseUpdate& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, const sim::lin::ControllerConfig& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, const sim::lin::ControllerStatusUpdate& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, const sim::lin::WakeupPulse& /*msg*/) override {}

    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, const sim::io::AnalogIoMessage& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, const sim::io::DigitalIoMessage& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, sim::io::PatternIoMessage&& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, const sim::io::PatternIoMessage& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, const sim::io::PwmIoMessage& /*msg*/) override {}

    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, sim::generic::GenericMessage&& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, const sim::generic::GenericMessage& /*msg*/) override {}

    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, const sim::data::DataMessage& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, sim::data::DataMessage&& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, const sim::data::PublisherAnnouncement& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, sim::data::PublisherAnnouncement&& /*msg*/) override {}
    
	void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, const sim::rpc::ClientAnnouncement& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, sim::rpc::ClientAnnouncement&& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, const sim::rpc::ServerAcknowledge& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, sim::rpc::ServerAcknowledge&& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, const sim::rpc::FunctionCall& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, sim::rpc::FunctionCall&& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, const sim::rpc::FunctionCallResponse& /*msg*/) override {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, sim::rpc::FunctionCallResponse&& /*msg*/) override {}

    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, const sync::NextSimTask& /*msg*/) {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, const sync::ParticipantStatus& /*msg*/) {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, const sync::ParticipantCommand& /*msg*/) {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, const sync::SystemCommand& /*msg*/) {}

    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, logging::LogMsg&& /*msg*/) {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, const logging::LogMsg& /*msg*/) {}

    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, const service::ServiceAnnouncement& /*msg*/) {}
    void SendIbMessage(const IIbServiceEndpoint* /*from*/, const std::string& /*targetParticipantName*/, const service::ServiceDiscoveryEvent& /*msg*/) {}


    void OnAllMessagesDelivered(std::function<void()> /*callback*/) {}
    void FlushSendBuffers() {}
    void ExecuteDeferred(std::function<void()> callback) {}
    auto GetParticipantName() const -> const std::string& override { throw std::runtime_error("invalid call"); }
    auto GetConfig() const -> const ib::cfg::Config& override { return _config; }

    virtual auto GetTimeProvider() -> sync::ITimeProvider* { return &mockTimeProvider; }
    virtual void SendIbMessage_proxy(const IIbServiceEndpoint* /*from*/, const sim::generic::GenericMessage& /*msg*/) {} //helper for gtest workaround
    void joinIbDomain(uint32_t ) {}

    auto GetServiceDiscovery() -> service::IServiceDiscovery* override { return &mockServiceDiscovery; }

    cfg::Config _config;
    DummyLogger logger;
    MockTimeProvider mockTimeProvider;
    MockParticipantController mockParticipantController;
    MockSystemController mockSystemController;
    MockSystemMonitor mockSystemMonitor;
    MockServiceDiscovery mockServiceDiscovery;
};

// ================================================================================
//  Inline Implementations
// ================================================================================

} // namespace test
} // namespace mw
} // namespace ib
