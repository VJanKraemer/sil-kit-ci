// Copyright (c) Vector Informatik GmbH. All rights reserved.

#pragma once

#include <iostream>
#include <thread>

#include "ib/IbMacros.hpp"
#include "ib/mw/IParticipant.hpp"
#include "ib/cfg/IParticipantConfiguration.hpp"

namespace ib {

/*! \brief Join the configured middleware domain as a participant.
*
* Become a participant based on the the given configuration options.
* The middleware used is selected by the active middleware configuration option.
*
* \param config Configuration of the participant
* \param participantName Name of the participant
* \param domainId ID of the domain
* \return Instance of the communication adapter
*
* \throw ib::configuration_error if the config has errors
* \throw std::runtime_error Parameter participantName does not name
* a valid participant in the config file.
* \throw std::exception The participant could not be created.
*/
IntegrationBusAPI auto CreateParticipant(std::shared_ptr<ib::cfg::IParticipantConfiguration> participantConfig,
                                         const std::string& participantName, const uint32_t domainId)

    -> std::unique_ptr<mw::IParticipant>;

IntegrationBusAPI auto CreateParticipant(std::shared_ptr<ib::cfg::IParticipantConfiguration> participantConfig,
                                         std::string participantName)
    -> std::unique_ptr<mw::IParticipant>;

IntegrationBusAPI auto CreateParticipant(std::shared_ptr<ib::cfg::IParticipantConfiguration> participantConfig,
                                         std::string participantName, std::string registryUri)
    -> std::unique_ptr<mw::IParticipant>;

} // namespace ib
