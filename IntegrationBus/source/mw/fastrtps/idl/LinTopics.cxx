// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*! 
 * @file LinTopics.cpp
 * This source file contains the definition of the described types in the IDL file.
 *
 * This file was generated by the tool gen.
 */

#ifdef _WIN32
// Remove linker warning LNK4221 on Visual Studio
namespace { char dummy; }
#endif

#include "LinTopics.h"
#include <fastcdr/Cdr.h>

#include <fastcdr/exceptions/BadParamException.h>
using namespace eprosima::fastcdr::exception;

#include <utility>





ib::sim::lin::idl::LinMessage::LinMessage()
{

    m_status = ib::sim::lin::idl::TxSuccess;

    m_timestamp = 0;

    m_linId = 0;

    m_payloadLength = 0;

    memset(&m_payload, 0, (8) * 1);
    m_checksumModel = ib::sim::lin::idl::Undefined;


}

ib::sim::lin::idl::LinMessage::~LinMessage()
{
}

ib::sim::lin::idl::LinMessage::LinMessage(const LinMessage &x)
{
    m_senderAddr = x.m_senderAddr;
    m_status = x.m_status;
    m_timestamp = x.m_timestamp;
    m_linId = x.m_linId;
    m_payloadLength = x.m_payloadLength;
    m_payload = x.m_payload;
    m_checksumModel = x.m_checksumModel;
}

ib::sim::lin::idl::LinMessage::LinMessage(LinMessage &&x)
{
    m_senderAddr = std::move(x.m_senderAddr);
    m_status = x.m_status;
    m_timestamp = x.m_timestamp;
    m_linId = x.m_linId;
    m_payloadLength = x.m_payloadLength;
    m_payload = std::move(x.m_payload);
    m_checksumModel = x.m_checksumModel;
}

ib::sim::lin::idl::LinMessage& ib::sim::lin::idl::LinMessage::operator=(const LinMessage &x)
{
    m_senderAddr = x.m_senderAddr;
    m_status = x.m_status;
    m_timestamp = x.m_timestamp;
    m_linId = x.m_linId;
    m_payloadLength = x.m_payloadLength;
    m_payload = x.m_payload;
    m_checksumModel = x.m_checksumModel;

    return *this;
}

ib::sim::lin::idl::LinMessage& ib::sim::lin::idl::LinMessage::operator=(LinMessage &&x)
{
    m_senderAddr = std::move(x.m_senderAddr);
    m_status = x.m_status;
    m_timestamp = x.m_timestamp;
    m_linId = x.m_linId;
    m_payloadLength = x.m_payloadLength;
    m_payload = std::move(x.m_payload);
    m_checksumModel = x.m_checksumModel;

    return *this;
}

size_t ib::sim::lin::idl::LinMessage::getMaxCdrSerializedSize(size_t current_alignment)
{
    size_t initial_alignment = current_alignment;

    current_alignment += ib::mw::idl::EndpointAddress::getMaxCdrSerializedSize(current_alignment);
    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);


    current_alignment += 8 + eprosima::fastcdr::Cdr::alignment(current_alignment, 8);


    current_alignment += 1 + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);


    current_alignment += 1 + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);


    current_alignment += ((8) * 1) + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);



    return current_alignment - initial_alignment;
}

size_t ib::sim::lin::idl::LinMessage::getCdrSerializedSize(const ib::sim::lin::idl::LinMessage& data, size_t current_alignment)
{
    (void)data;
    size_t initial_alignment = current_alignment;

    current_alignment += ib::mw::idl::EndpointAddress::getCdrSerializedSize(data.senderAddr(), current_alignment);
    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);


    current_alignment += 8 + eprosima::fastcdr::Cdr::alignment(current_alignment, 8);


    current_alignment += 1 + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);


    current_alignment += 1 + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);


    current_alignment += ((8) * 1) + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);

    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);



    return current_alignment - initial_alignment;
}

void ib::sim::lin::idl::LinMessage::serialize(eprosima::fastcdr::Cdr &scdr) const
{
    scdr << m_senderAddr;
    scdr << (uint32_t)m_status;
    scdr << m_timestamp;
    scdr << m_linId;
    scdr << m_payloadLength;
    scdr << m_payload;
    scdr << (uint32_t)m_checksumModel;
}

void ib::sim::lin::idl::LinMessage::deserialize(eprosima::fastcdr::Cdr &dcdr)
{
    dcdr >> m_senderAddr;
    {
        uint32_t enum_value = 0;
        dcdr >> enum_value;
        m_status = (ib::sim::lin::idl::MessageStatus)enum_value;
    }
    dcdr >> m_timestamp;
    dcdr >> m_linId;
    dcdr >> m_payloadLength;
    dcdr >> m_payload;
    {
        uint32_t enum_value = 0;
        dcdr >> enum_value;
        m_checksumModel = (ib::sim::lin::idl::ChecksumModel)enum_value;
    }
}

size_t ib::sim::lin::idl::LinMessage::getKeyMaxCdrSerializedSize(size_t current_alignment)
{
	size_t current_align = current_alignment;
            
     current_align += ib::mw::idl::EndpointAddress::getMaxCdrSerializedSize(current_align); 







    return current_align;
}

bool ib::sim::lin::idl::LinMessage::isKeyDefined()
{
    return true;
}

void ib::sim::lin::idl::LinMessage::serializeKey(eprosima::fastcdr::Cdr &scdr) const
{
	(void) scdr;
	 scdr << m_senderAddr;  
	 
	 
	 
	 
	 
	 
}
ib::sim::lin::idl::RxRequest::RxRequest()
{

    m_linId = 0;

    m_payloadLength = 0;

    m_checksumModel = ib::sim::lin::idl::Undefined;


}

ib::sim::lin::idl::RxRequest::~RxRequest()
{
}

ib::sim::lin::idl::RxRequest::RxRequest(const RxRequest &x)
{
    m_senderAddr = x.m_senderAddr;
    m_linId = x.m_linId;
    m_payloadLength = x.m_payloadLength;
    m_checksumModel = x.m_checksumModel;
}

ib::sim::lin::idl::RxRequest::RxRequest(RxRequest &&x)
{
    m_senderAddr = std::move(x.m_senderAddr);
    m_linId = x.m_linId;
    m_payloadLength = x.m_payloadLength;
    m_checksumModel = x.m_checksumModel;
}

ib::sim::lin::idl::RxRequest& ib::sim::lin::idl::RxRequest::operator=(const RxRequest &x)
{
    m_senderAddr = x.m_senderAddr;
    m_linId = x.m_linId;
    m_payloadLength = x.m_payloadLength;
    m_checksumModel = x.m_checksumModel;

    return *this;
}

ib::sim::lin::idl::RxRequest& ib::sim::lin::idl::RxRequest::operator=(RxRequest &&x)
{
    m_senderAddr = std::move(x.m_senderAddr);
    m_linId = x.m_linId;
    m_payloadLength = x.m_payloadLength;
    m_checksumModel = x.m_checksumModel;

    return *this;
}

size_t ib::sim::lin::idl::RxRequest::getMaxCdrSerializedSize(size_t current_alignment)
{
    size_t initial_alignment = current_alignment;

    current_alignment += ib::mw::idl::EndpointAddress::getMaxCdrSerializedSize(current_alignment);
    current_alignment += 1 + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);


    current_alignment += 1 + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);



    return current_alignment - initial_alignment;
}

size_t ib::sim::lin::idl::RxRequest::getCdrSerializedSize(const ib::sim::lin::idl::RxRequest& data, size_t current_alignment)
{
    (void)data;
    size_t initial_alignment = current_alignment;

    current_alignment += ib::mw::idl::EndpointAddress::getCdrSerializedSize(data.senderAddr(), current_alignment);
    current_alignment += 1 + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);


    current_alignment += 1 + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);



    return current_alignment - initial_alignment;
}

void ib::sim::lin::idl::RxRequest::serialize(eprosima::fastcdr::Cdr &scdr) const
{
    scdr << m_senderAddr;
    scdr << m_linId;
    scdr << m_payloadLength;
    scdr << (uint32_t)m_checksumModel;
}

void ib::sim::lin::idl::RxRequest::deserialize(eprosima::fastcdr::Cdr &dcdr)
{
    dcdr >> m_senderAddr;
    dcdr >> m_linId;
    dcdr >> m_payloadLength;
    {
        uint32_t enum_value = 0;
        dcdr >> enum_value;
        m_checksumModel = (ib::sim::lin::idl::ChecksumModel)enum_value;
    }
}

size_t ib::sim::lin::idl::RxRequest::getKeyMaxCdrSerializedSize(size_t current_alignment)
{
	size_t current_align = current_alignment;
            
     current_align += ib::mw::idl::EndpointAddress::getMaxCdrSerializedSize(current_align); 




    return current_align;
}

bool ib::sim::lin::idl::RxRequest::isKeyDefined()
{
    return true;
}

void ib::sim::lin::idl::RxRequest::serializeKey(eprosima::fastcdr::Cdr &scdr) const
{
	(void) scdr;
	 scdr << m_senderAddr;  
	 
	 
	 
}
ib::sim::lin::idl::TxAcknowledge::TxAcknowledge()
{

    m_timestamp = 0;

    m_linId = 0;

    m_status = ib::sim::lin::idl::TxSuccess;


}

ib::sim::lin::idl::TxAcknowledge::~TxAcknowledge()
{
}

ib::sim::lin::idl::TxAcknowledge::TxAcknowledge(const TxAcknowledge &x)
{
    m_senderAddr = x.m_senderAddr;
    m_timestamp = x.m_timestamp;
    m_linId = x.m_linId;
    m_status = x.m_status;
}

ib::sim::lin::idl::TxAcknowledge::TxAcknowledge(TxAcknowledge &&x)
{
    m_senderAddr = std::move(x.m_senderAddr);
    m_timestamp = x.m_timestamp;
    m_linId = x.m_linId;
    m_status = x.m_status;
}

ib::sim::lin::idl::TxAcknowledge& ib::sim::lin::idl::TxAcknowledge::operator=(const TxAcknowledge &x)
{
    m_senderAddr = x.m_senderAddr;
    m_timestamp = x.m_timestamp;
    m_linId = x.m_linId;
    m_status = x.m_status;

    return *this;
}

ib::sim::lin::idl::TxAcknowledge& ib::sim::lin::idl::TxAcknowledge::operator=(TxAcknowledge &&x)
{
    m_senderAddr = std::move(x.m_senderAddr);
    m_timestamp = x.m_timestamp;
    m_linId = x.m_linId;
    m_status = x.m_status;

    return *this;
}

size_t ib::sim::lin::idl::TxAcknowledge::getMaxCdrSerializedSize(size_t current_alignment)
{
    size_t initial_alignment = current_alignment;

    current_alignment += ib::mw::idl::EndpointAddress::getMaxCdrSerializedSize(current_alignment);
    current_alignment += 8 + eprosima::fastcdr::Cdr::alignment(current_alignment, 8);


    current_alignment += 1 + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);



    return current_alignment - initial_alignment;
}

size_t ib::sim::lin::idl::TxAcknowledge::getCdrSerializedSize(const ib::sim::lin::idl::TxAcknowledge& data, size_t current_alignment)
{
    (void)data;
    size_t initial_alignment = current_alignment;

    current_alignment += ib::mw::idl::EndpointAddress::getCdrSerializedSize(data.senderAddr(), current_alignment);
    current_alignment += 8 + eprosima::fastcdr::Cdr::alignment(current_alignment, 8);


    current_alignment += 1 + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);



    return current_alignment - initial_alignment;
}

void ib::sim::lin::idl::TxAcknowledge::serialize(eprosima::fastcdr::Cdr &scdr) const
{
    scdr << m_senderAddr;
    scdr << m_timestamp;
    scdr << m_linId;
    scdr << (uint32_t)m_status;
}

void ib::sim::lin::idl::TxAcknowledge::deserialize(eprosima::fastcdr::Cdr &dcdr)
{
    dcdr >> m_senderAddr;
    dcdr >> m_timestamp;
    dcdr >> m_linId;
    {
        uint32_t enum_value = 0;
        dcdr >> enum_value;
        m_status = (ib::sim::lin::idl::MessageStatus)enum_value;
    }
}

size_t ib::sim::lin::idl::TxAcknowledge::getKeyMaxCdrSerializedSize(size_t current_alignment)
{
	size_t current_align = current_alignment;
            
     current_align += ib::mw::idl::EndpointAddress::getMaxCdrSerializedSize(current_align); 




    return current_align;
}

bool ib::sim::lin::idl::TxAcknowledge::isKeyDefined()
{
    return true;
}

void ib::sim::lin::idl::TxAcknowledge::serializeKey(eprosima::fastcdr::Cdr &scdr) const
{
	(void) scdr;
	 scdr << m_senderAddr;  
	 
	 
	 
}

ib::sim::lin::idl::ControllerConfig::ControllerConfig()
{

    m_controllerMode = ib::sim::lin::idl::Inactive;

    m_baudrate = 0;


}

ib::sim::lin::idl::ControllerConfig::~ControllerConfig()
{
}

ib::sim::lin::idl::ControllerConfig::ControllerConfig(const ControllerConfig &x)
{
    m_senderAddr = x.m_senderAddr;
    m_controllerMode = x.m_controllerMode;
    m_baudrate = x.m_baudrate;
}

ib::sim::lin::idl::ControllerConfig::ControllerConfig(ControllerConfig &&x)
{
    m_senderAddr = std::move(x.m_senderAddr);
    m_controllerMode = x.m_controllerMode;
    m_baudrate = x.m_baudrate;
}

ib::sim::lin::idl::ControllerConfig& ib::sim::lin::idl::ControllerConfig::operator=(const ControllerConfig &x)
{
    m_senderAddr = x.m_senderAddr;
    m_controllerMode = x.m_controllerMode;
    m_baudrate = x.m_baudrate;

    return *this;
}

ib::sim::lin::idl::ControllerConfig& ib::sim::lin::idl::ControllerConfig::operator=(ControllerConfig &&x)
{
    m_senderAddr = std::move(x.m_senderAddr);
    m_controllerMode = x.m_controllerMode;
    m_baudrate = x.m_baudrate;

    return *this;
}

size_t ib::sim::lin::idl::ControllerConfig::getMaxCdrSerializedSize(size_t current_alignment)
{
    size_t initial_alignment = current_alignment;

    current_alignment += ib::mw::idl::EndpointAddress::getMaxCdrSerializedSize(current_alignment);
    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);



    return current_alignment - initial_alignment;
}

size_t ib::sim::lin::idl::ControllerConfig::getCdrSerializedSize(const ib::sim::lin::idl::ControllerConfig& data, size_t current_alignment)
{
    (void)data;
    size_t initial_alignment = current_alignment;

    current_alignment += ib::mw::idl::EndpointAddress::getCdrSerializedSize(data.senderAddr(), current_alignment);
    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);



    return current_alignment - initial_alignment;
}

void ib::sim::lin::idl::ControllerConfig::serialize(eprosima::fastcdr::Cdr &scdr) const
{
    scdr << m_senderAddr;
    scdr << (uint32_t)m_controllerMode;
    scdr << m_baudrate;
}

void ib::sim::lin::idl::ControllerConfig::deserialize(eprosima::fastcdr::Cdr &dcdr)
{
    dcdr >> m_senderAddr;
    {
        uint32_t enum_value = 0;
        dcdr >> enum_value;
        m_controllerMode = (ib::sim::lin::idl::ControllerMode)enum_value;
    }
    dcdr >> m_baudrate;
}

size_t ib::sim::lin::idl::ControllerConfig::getKeyMaxCdrSerializedSize(size_t current_alignment)
{
	size_t current_align = current_alignment;
            
     current_align += ib::mw::idl::EndpointAddress::getMaxCdrSerializedSize(current_align); 



    return current_align;
}

bool ib::sim::lin::idl::ControllerConfig::isKeyDefined()
{
    return true;
}

void ib::sim::lin::idl::ControllerConfig::serializeKey(eprosima::fastcdr::Cdr &scdr) const
{
	(void) scdr;
	 scdr << m_senderAddr;  
	 
	 
}
ib::sim::lin::idl::SlaveResponseConfig::SlaveResponseConfig()
{

    m_responseMode = ib::sim::lin::idl::Unused;

    m_checksumModel = ib::sim::lin::idl::Undefined;

    m_payloadLength = 0;


}

ib::sim::lin::idl::SlaveResponseConfig::~SlaveResponseConfig()
{
}

ib::sim::lin::idl::SlaveResponseConfig::SlaveResponseConfig(const SlaveResponseConfig &x)
{
    m_senderAddr = x.m_senderAddr;
    m_responseMode = x.m_responseMode;
    m_checksumModel = x.m_checksumModel;
    m_payloadLength = x.m_payloadLength;
}

ib::sim::lin::idl::SlaveResponseConfig::SlaveResponseConfig(SlaveResponseConfig &&x)
{
    m_senderAddr = std::move(x.m_senderAddr);
    m_responseMode = x.m_responseMode;
    m_checksumModel = x.m_checksumModel;
    m_payloadLength = x.m_payloadLength;
}

ib::sim::lin::idl::SlaveResponseConfig& ib::sim::lin::idl::SlaveResponseConfig::operator=(const SlaveResponseConfig &x)
{
    m_senderAddr = x.m_senderAddr;
    m_responseMode = x.m_responseMode;
    m_checksumModel = x.m_checksumModel;
    m_payloadLength = x.m_payloadLength;

    return *this;
}

ib::sim::lin::idl::SlaveResponseConfig& ib::sim::lin::idl::SlaveResponseConfig::operator=(SlaveResponseConfig &&x)
{
    m_senderAddr = std::move(x.m_senderAddr);
    m_responseMode = x.m_responseMode;
    m_checksumModel = x.m_checksumModel;
    m_payloadLength = x.m_payloadLength;

    return *this;
}

size_t ib::sim::lin::idl::SlaveResponseConfig::getMaxCdrSerializedSize(size_t current_alignment)
{
    size_t initial_alignment = current_alignment;

    current_alignment += ib::mw::idl::EndpointAddress::getMaxCdrSerializedSize(current_alignment);
    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);


    current_alignment += 1 + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);



    return current_alignment - initial_alignment;
}

size_t ib::sim::lin::idl::SlaveResponseConfig::getCdrSerializedSize(const ib::sim::lin::idl::SlaveResponseConfig& data, size_t current_alignment)
{
    (void)data;
    size_t initial_alignment = current_alignment;

    current_alignment += ib::mw::idl::EndpointAddress::getCdrSerializedSize(data.senderAddr(), current_alignment);
    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);


    current_alignment += 1 + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);



    return current_alignment - initial_alignment;
}

void ib::sim::lin::idl::SlaveResponseConfig::serialize(eprosima::fastcdr::Cdr &scdr) const
{
    scdr << m_senderAddr;
    scdr << (uint32_t)m_responseMode;
    scdr << (uint32_t)m_checksumModel;
    scdr << m_payloadLength;
}

void ib::sim::lin::idl::SlaveResponseConfig::deserialize(eprosima::fastcdr::Cdr &dcdr)
{
    dcdr >> m_senderAddr;
    {
        uint32_t enum_value = 0;
        dcdr >> enum_value;
        m_responseMode = (ib::sim::lin::idl::ResponseMode)enum_value;
    }
    {
        uint32_t enum_value = 0;
        dcdr >> enum_value;
        m_checksumModel = (ib::sim::lin::idl::ChecksumModel)enum_value;
    }
    dcdr >> m_payloadLength;
}

size_t ib::sim::lin::idl::SlaveResponseConfig::getKeyMaxCdrSerializedSize(size_t current_alignment)
{
	size_t current_align = current_alignment;
            
     current_align += ib::mw::idl::EndpointAddress::getMaxCdrSerializedSize(current_align); 




    return current_align;
}

bool ib::sim::lin::idl::SlaveResponseConfig::isKeyDefined()
{
    return true;
}

void ib::sim::lin::idl::SlaveResponseConfig::serializeKey(eprosima::fastcdr::Cdr &scdr) const
{
	(void) scdr;
	 scdr << m_senderAddr;  
	 
	 
	 
}
ib::sim::lin::idl::SlaveConfiguration::SlaveConfiguration()
{



}

ib::sim::lin::idl::SlaveConfiguration::~SlaveConfiguration()
{
}

ib::sim::lin::idl::SlaveConfiguration::SlaveConfiguration(const SlaveConfiguration &x)
{
    m_senderAddr = x.m_senderAddr;
    m_responseConfigs = x.m_responseConfigs;
}

ib::sim::lin::idl::SlaveConfiguration::SlaveConfiguration(SlaveConfiguration &&x)
{
    m_senderAddr = std::move(x.m_senderAddr);
    m_responseConfigs = std::move(x.m_responseConfigs);
}

ib::sim::lin::idl::SlaveConfiguration& ib::sim::lin::idl::SlaveConfiguration::operator=(const SlaveConfiguration &x)
{
    m_senderAddr = x.m_senderAddr;
    m_responseConfigs = x.m_responseConfigs;

    return *this;
}

ib::sim::lin::idl::SlaveConfiguration& ib::sim::lin::idl::SlaveConfiguration::operator=(SlaveConfiguration &&x)
{
    m_senderAddr = std::move(x.m_senderAddr);
    m_responseConfigs = std::move(x.m_responseConfigs);

    return *this;
}

size_t ib::sim::lin::idl::SlaveConfiguration::getMaxCdrSerializedSize(size_t current_alignment)
{
    size_t initial_alignment = current_alignment;

    current_alignment += ib::mw::idl::EndpointAddress::getMaxCdrSerializedSize(current_alignment);
    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);


    for(size_t a = 0; a < 100; ++a)
    {
        current_alignment += ib::sim::lin::idl::SlaveResponseConfig::getMaxCdrSerializedSize(current_alignment);}


    return current_alignment - initial_alignment;
}

size_t ib::sim::lin::idl::SlaveConfiguration::getCdrSerializedSize(const ib::sim::lin::idl::SlaveConfiguration& data, size_t current_alignment)
{
    (void)data;
    size_t initial_alignment = current_alignment;

    current_alignment += ib::mw::idl::EndpointAddress::getCdrSerializedSize(data.senderAddr(), current_alignment);
    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);


    for(size_t a = 0; a < data.responseConfigs().size(); ++a)
    {
        current_alignment += ib::sim::lin::idl::SlaveResponseConfig::getCdrSerializedSize(data.responseConfigs().at(a), current_alignment);}


    return current_alignment - initial_alignment;
}

void ib::sim::lin::idl::SlaveConfiguration::serialize(eprosima::fastcdr::Cdr &scdr) const
{
    scdr << m_senderAddr;
    scdr << m_responseConfigs;
}

void ib::sim::lin::idl::SlaveConfiguration::deserialize(eprosima::fastcdr::Cdr &dcdr)
{
    dcdr >> m_senderAddr;
    dcdr >> m_responseConfigs;
}

size_t ib::sim::lin::idl::SlaveConfiguration::getKeyMaxCdrSerializedSize(size_t current_alignment)
{
	size_t current_align = current_alignment;
            
     current_align += ib::mw::idl::EndpointAddress::getMaxCdrSerializedSize(current_align); 


    return current_align;
}

bool ib::sim::lin::idl::SlaveConfiguration::isKeyDefined()
{
    return true;
}

void ib::sim::lin::idl::SlaveConfiguration::serializeKey(eprosima::fastcdr::Cdr &scdr) const
{
	(void) scdr;
	 scdr << m_senderAddr;  
	 
}
ib::sim::lin::idl::SlaveResponse::SlaveResponse()
{

    m_linId = 0;

    m_payloadLength = 0;

    memset(&m_payload, 0, (8) * 1);
    m_checksumModel = ib::sim::lin::idl::Undefined;


}

ib::sim::lin::idl::SlaveResponse::~SlaveResponse()
{
}

ib::sim::lin::idl::SlaveResponse::SlaveResponse(const SlaveResponse &x)
{
    m_senderAddr = x.m_senderAddr;
    m_linId = x.m_linId;
    m_payloadLength = x.m_payloadLength;
    m_payload = x.m_payload;
    m_checksumModel = x.m_checksumModel;
}

ib::sim::lin::idl::SlaveResponse::SlaveResponse(SlaveResponse &&x)
{
    m_senderAddr = std::move(x.m_senderAddr);
    m_linId = x.m_linId;
    m_payloadLength = x.m_payloadLength;
    m_payload = std::move(x.m_payload);
    m_checksumModel = x.m_checksumModel;
}

ib::sim::lin::idl::SlaveResponse& ib::sim::lin::idl::SlaveResponse::operator=(const SlaveResponse &x)
{
    m_senderAddr = x.m_senderAddr;
    m_linId = x.m_linId;
    m_payloadLength = x.m_payloadLength;
    m_payload = x.m_payload;
    m_checksumModel = x.m_checksumModel;

    return *this;
}

ib::sim::lin::idl::SlaveResponse& ib::sim::lin::idl::SlaveResponse::operator=(SlaveResponse &&x)
{
    m_senderAddr = std::move(x.m_senderAddr);
    m_linId = x.m_linId;
    m_payloadLength = x.m_payloadLength;
    m_payload = std::move(x.m_payload);
    m_checksumModel = x.m_checksumModel;

    return *this;
}

size_t ib::sim::lin::idl::SlaveResponse::getMaxCdrSerializedSize(size_t current_alignment)
{
    size_t initial_alignment = current_alignment;

    current_alignment += ib::mw::idl::EndpointAddress::getMaxCdrSerializedSize(current_alignment);
    current_alignment += 1 + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);


    current_alignment += 1 + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);


    current_alignment += ((8) * 1) + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);



    return current_alignment - initial_alignment;
}

size_t ib::sim::lin::idl::SlaveResponse::getCdrSerializedSize(const ib::sim::lin::idl::SlaveResponse& data, size_t current_alignment)
{
    (void)data;
    size_t initial_alignment = current_alignment;

    current_alignment += ib::mw::idl::EndpointAddress::getCdrSerializedSize(data.senderAddr(), current_alignment);
    current_alignment += 1 + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);


    current_alignment += 1 + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);


    current_alignment += ((8) * 1) + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);

    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);



    return current_alignment - initial_alignment;
}

void ib::sim::lin::idl::SlaveResponse::serialize(eprosima::fastcdr::Cdr &scdr) const
{
    scdr << m_senderAddr;
    scdr << m_linId;
    scdr << m_payloadLength;
    scdr << m_payload;
    scdr << (uint32_t)m_checksumModel;
}

void ib::sim::lin::idl::SlaveResponse::deserialize(eprosima::fastcdr::Cdr &dcdr)
{
    dcdr >> m_senderAddr;
    dcdr >> m_linId;
    dcdr >> m_payloadLength;
    dcdr >> m_payload;
    {
        uint32_t enum_value = 0;
        dcdr >> enum_value;
        m_checksumModel = (ib::sim::lin::idl::ChecksumModel)enum_value;
    }
}

size_t ib::sim::lin::idl::SlaveResponse::getKeyMaxCdrSerializedSize(size_t current_alignment)
{
	size_t current_align = current_alignment;
            
     current_align += ib::mw::idl::EndpointAddress::getMaxCdrSerializedSize(current_align); 





    return current_align;
}

bool ib::sim::lin::idl::SlaveResponse::isKeyDefined()
{
    return true;
}

void ib::sim::lin::idl::SlaveResponse::serializeKey(eprosima::fastcdr::Cdr &scdr) const
{
	(void) scdr;
	 scdr << m_senderAddr;  
	 
	 
	 
	 
}



