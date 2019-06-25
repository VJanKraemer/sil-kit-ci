// Copyright (c) Vector Informatik GmbH. All rights reserved.

#pragma once

#include "MessageBuffer.hpp"

#include "ib/sim/eth/EthDatatypes.hpp"

namespace ib {
namespace sim {
namespace eth {

inline ib::mw::MessageBuffer& operator<<(ib::mw::MessageBuffer& buffer, const EthMessage& msg)
{
    buffer << msg.transmitId
           << msg.timestamp;

    for (const auto& value : msg.ethFrame.GetSourceMac()) {
        buffer << value;
    }

    for (const auto& value : msg.ethFrame.GetDestinationMac()) {
        buffer << value;
    }

    buffer << msg.ethFrame.GetVlanTag().pcp
           << msg.ethFrame.GetVlanTag().dei
           << msg.ethFrame.GetVlanTag().vid
           << reinterpret_cast<const char*>(msg.ethFrame.GetPayload().data());

    return buffer;
}
inline ib::mw::MessageBuffer& operator>>(ib::mw::MessageBuffer& buffer, EthMessage& msg)
{
    std::array<uint8_t, 6> sourceMac, destinationMac;
    uint8_t pcp, dei;
    uint16_t vid;
    std::vector<uint8_t> payload;

    buffer >> msg.transmitId
           >> msg.timestamp;

    for (size_t i = 0; i < 6; i++) {
        buffer >> sourceMac[i];
    }

    for (size_t i = 0; i < 6; i++) {
        buffer >> destinationMac[i];
    }

    buffer >> pcp
           >> dei
           >> vid
           >> payload;

    msg.ethFrame.SetSourceMac(sourceMac);
    msg.ethFrame.SetDestinationMac(destinationMac);

    eth::EthTagControlInformation tci;
    tci.pcp = pcp;
    tci.dei = dei;
    tci.vid = vid;

    msg.ethFrame.SetVlanTag(tci);
    msg.ethFrame.SetPayload(payload);

    return buffer;
}

inline ib::mw::MessageBuffer& operator<<(ib::mw::MessageBuffer& buffer, const EthTransmitAcknowledge& ack)
{
    buffer << ack.transmitId
           << ack.timestamp
           << ack.status;
    return buffer;
}
inline ib::mw::MessageBuffer& operator>>(ib::mw::MessageBuffer& buffer, EthTransmitAcknowledge& ack)
{
    buffer >> ack.transmitId
           >> ack.timestamp
           >> ack.status;
    return buffer;
}

inline ib::mw::MessageBuffer& operator<<(ib::mw::MessageBuffer& buffer, const EthStatus& msg)
{
    buffer << msg.timestamp
        << msg.state
        << msg.bitRate;
    return buffer;
}
inline ib::mw::MessageBuffer& operator>>(ib::mw::MessageBuffer& buffer, EthStatus& msg)
{
    buffer >> msg.timestamp
        >> msg.state
        >> msg.bitRate;
    return buffer;
}

inline ib::mw::MessageBuffer& operator<<(ib::mw::MessageBuffer& buffer, const EthSetMode& msg)
{
    buffer << msg.mode;
    return buffer;
}
inline ib::mw::MessageBuffer& operator>>(ib::mw::MessageBuffer& buffer, EthSetMode& msg)
{
    buffer >> msg.mode;
    return buffer;
}


} // namespace eth    
} // namespace sim
} // namespace ib
