// Copyright (c) Vector Informatik GmbH. All rights reserved.

#pragma once

#include <sstream>

#include "IVAsioPeer.hpp"
#include <type_traits>

#include "IMessageReceiver.hpp"
#include "IServiceEndpoint.hpp"
#include "traits/SilKitMsgTraits.hpp"

#include "SerializedMessage.hpp"

namespace SilKit {
namespace Core {

//auxiliary class for conditional compilation using silkit message traits
template<typename MsgT, std::size_t MsgHistSize>
struct MessageHistory {};
// MessageHistory<.., 0>: message history is disabled
template<typename MsgT> struct MessageHistory<MsgT, 0>
{
    void SetHistoryLength(size_t) {}
    void Save(const IServiceEndpoint*, const MsgT& ) {}
    void NotifyPeer(IVAsioPeer*, EndpointId) {}
};
// MessageHistory<.., 1>: save last message and notify peers about it
template<typename MsgT> struct MessageHistory<MsgT, 1>
{
    void SetHistoryLength(size_t historyLength)
    {
        _hasHistory = historyLength != 0;
    }

    void Save(const IServiceEndpoint* from , const MsgT& msg)
    {
        if (!_hasHistory)
            return;

        _from = from->GetServiceDescriptor().to_endpointAddress();
        _last = msg;
        _hasValue = true;
    }
    void NotifyPeer(IVAsioPeer* peer, EndpointId remoteIdx)
    {
        if (!_hasValue || !_hasHistory)
            return;

        auto buffer = SerializedMessage(_last, _from, remoteIdx);
        peer->SendSilKitMsg(std::move(buffer));
    }
private:
    MsgT _last;
    EndpointAddress _from;
    bool _hasValue{false};
    bool _hasHistory{true};
};


struct RemoteReceiver {
    IVAsioPeer* peer;
    EndpointId remoteIdx;
};

template <class MsgT>
class VAsioTransmitter 
    : public IMessageReceiver<MsgT>
    , public IServiceEndpoint
{
    using History = MessageHistory<MsgT, SilKitMsgTraits<MsgT>::HistSize()>;
    History _hist;
public:
    // ----------------------------------------
    // Public methods
    void AddRemoteReceiver(IVAsioPeer* peer, EndpointId remoteIdx)
    {
        RemoteReceiver remoteReceiver;
        remoteReceiver.peer = peer;
        remoteReceiver.remoteIdx = remoteIdx;

        if (_remoteReceivers.end() != std::find(_remoteReceivers.begin(), _remoteReceivers.end(), remoteReceiver))
            return;


        _serviceDescriptor.SetParticipantName(peer->GetInfo().participantName);
        _remoteReceivers.push_back(remoteReceiver);
        _hist.NotifyPeer(peer, remoteIdx);
    }

    void SendMessageToTarget(const IServiceEndpoint* from, const std::string& targetParticipantName, const MsgT& msg)
    {
        // TODO  what do we do with the history for targeted messaging?
        _hist.Save(from, msg);
        auto&& receiverIter = std::find_if(_remoteReceivers.begin(), _remoteReceivers.end(), [targetParticipantName](auto&& receiver) 
            {
                return receiver.peer->GetInfo().participantName == targetParticipantName;
            });
        if (receiverIter == _remoteReceivers.end())
        {
            std::stringstream ss;
            ss << "Error: Attempt to send targeted message to participant '"
                << targetParticipantName
                << "', which is not a valid remote receiver.";
            throw std::runtime_error{ss.str()};
        }
        auto buffer = SerializedMessage(msg, to_endpointAddress(from->GetServiceDescriptor()), receiverIter->remoteIdx);
        receiverIter->peer->SendSilKitMsg(std::move(buffer));
    }

    void SetHistoryLength(size_t historyLength)
    {
        _hist.SetHistoryLength(historyLength);
    }

public:
    // ----------------------------------------
    // Public interface methods
    void ReceiveSilKitMessage(const IServiceEndpoint* from, const MsgT& msg) override
    {
        _hist.Save(from, msg);
        for (auto& receiver : _remoteReceivers)
        {
            auto buffer = SerializedMessage(msg, to_endpointAddress(from->GetServiceDescriptor()), receiver.remoteIdx);
            receiver.peer->SendSilKitMsg(std::move(buffer));
        }
    }

    // IServiceEndpoint
    void SetServiceDescriptor(const ServiceDescriptor& serviceDescriptor) override
    {
        _serviceDescriptor = serviceDescriptor;
    }
    auto GetServiceDescriptor() const -> const ServiceDescriptor& override
    {
        return _serviceDescriptor;
    }
private:
    // ----------------------------------------
    // private members
    std::vector<RemoteReceiver> _remoteReceivers;
    ServiceDescriptor _serviceDescriptor;
};

// ================================================================================
//  Inline Implementations
// ================================================================================
inline bool operator==(const RemoteReceiver& lhs, const RemoteReceiver& rhs)
{
    return lhs.peer == rhs.peer
        && lhs.remoteIdx == rhs.remoteIdx;
}

} // namespace Core
} // namespace SilKit