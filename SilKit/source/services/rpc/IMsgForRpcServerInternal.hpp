// Copyright (c) Vector Informatik GmbH. All rights reserved.

#pragma once

#include "IReceiver.hpp"
#include "ISender.hpp"

#include "silkit/services/rpc/fwd_decl.hpp"

namespace SilKit {
namespace Services {
namespace Rpc {

//! \brief IMsgForRpcServer interface used by the Participant
class IMsgForRpcServerInternal
    : public Core::IReceiver<FunctionCall>
    , public Core::ISender<FunctionCallResponse>
{
public:
    virtual ~IMsgForRpcServerInternal() noexcept = default;
};

} // namespace Rpc
} // namespace Services
} // namespace SilKit
