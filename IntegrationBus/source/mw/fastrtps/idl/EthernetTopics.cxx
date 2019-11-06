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
 * @file EthernetTopics.cpp
 * This source file contains the definition of the described types in the IDL file.
 *
 * This file was generated by the tool gen.
 */

#ifdef _WIN32
// Remove linker warning LNK4221 on Visual Studio
namespace { char dummy; }
#endif

#include "EthernetTopics.h"
#include <fastcdr/Cdr.h>

#include <fastcdr/exceptions/BadParamException.h>
using namespace eprosima::fastcdr::exception;

#include <utility>

ib::sim::eth::idl::EthTagControlInformation::EthTagControlInformation()
{
    m_pcp = 0;
    m_dei = 0;
    m_vid = 0;

}

ib::sim::eth::idl::EthTagControlInformation::~EthTagControlInformation()
{



}

ib::sim::eth::idl::EthTagControlInformation::EthTagControlInformation(const EthTagControlInformation &x)
{
    m_pcp = x.m_pcp;
    m_dei = x.m_dei;
    m_vid = x.m_vid;
}

ib::sim::eth::idl::EthTagControlInformation::EthTagControlInformation(EthTagControlInformation &&x)
{
    m_pcp = x.m_pcp;
    m_dei = x.m_dei;
    m_vid = x.m_vid;
}

ib::sim::eth::idl::EthTagControlInformation& ib::sim::eth::idl::EthTagControlInformation::operator=(const EthTagControlInformation &x)
{

    m_pcp = x.m_pcp;
    m_dei = x.m_dei;
    m_vid = x.m_vid;

    return *this;
}

ib::sim::eth::idl::EthTagControlInformation& ib::sim::eth::idl::EthTagControlInformation::operator=(EthTagControlInformation &&x)
{

    m_pcp = x.m_pcp;
    m_dei = x.m_dei;
    m_vid = x.m_vid;

    return *this;
}

size_t ib::sim::eth::idl::EthTagControlInformation::getMaxCdrSerializedSize(size_t current_alignment)
{
    size_t initial_alignment = current_alignment;


    current_alignment += 1 + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);


    current_alignment += 1 + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);


    current_alignment += 2 + eprosima::fastcdr::Cdr::alignment(current_alignment, 2);



    return current_alignment - initial_alignment;
}

size_t ib::sim::eth::idl::EthTagControlInformation::getCdrSerializedSize(const ib::sim::eth::idl::EthTagControlInformation& data, size_t current_alignment)
{
    (void)data;
    size_t initial_alignment = current_alignment;


    current_alignment += 1 + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);


    current_alignment += 1 + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);


    current_alignment += 2 + eprosima::fastcdr::Cdr::alignment(current_alignment, 2);



    return current_alignment - initial_alignment;
}

void ib::sim::eth::idl::EthTagControlInformation::serialize(eprosima::fastcdr::Cdr &scdr) const
{

    scdr << m_pcp;
    scdr << m_dei;
    scdr << m_vid;
}

void ib::sim::eth::idl::EthTagControlInformation::deserialize(eprosima::fastcdr::Cdr &dcdr)
{

    dcdr >> m_pcp;
    dcdr >> m_dei;
    dcdr >> m_vid;
}

/*!
 * @brief This function sets a value in member pcp
 * @param _pcp New value for member pcp
 */
void ib::sim::eth::idl::EthTagControlInformation::pcp(uint8_t _pcp)
{
m_pcp = _pcp;
}

/*!
 * @brief This function returns the value of member pcp
 * @return Value of member pcp
 */
uint8_t ib::sim::eth::idl::EthTagControlInformation::pcp() const
{
    return m_pcp;
}

/*!
 * @brief This function returns a reference to member pcp
 * @return Reference to member pcp
 */
uint8_t& ib::sim::eth::idl::EthTagControlInformation::pcp()
{
    return m_pcp;
}
/*!
 * @brief This function sets a value in member dei
 * @param _dei New value for member dei
 */
void ib::sim::eth::idl::EthTagControlInformation::dei(uint8_t _dei)
{
m_dei = _dei;
}

/*!
 * @brief This function returns the value of member dei
 * @return Value of member dei
 */
uint8_t ib::sim::eth::idl::EthTagControlInformation::dei() const
{
    return m_dei;
}

/*!
 * @brief This function returns a reference to member dei
 * @return Reference to member dei
 */
uint8_t& ib::sim::eth::idl::EthTagControlInformation::dei()
{
    return m_dei;
}
/*!
 * @brief This function sets a value in member vid
 * @param _vid New value for member vid
 */
void ib::sim::eth::idl::EthTagControlInformation::vid(uint16_t _vid)
{
m_vid = _vid;
}

/*!
 * @brief This function returns the value of member vid
 * @return Value of member vid
 */
uint16_t ib::sim::eth::idl::EthTagControlInformation::vid() const
{
    return m_vid;
}

/*!
 * @brief This function returns a reference to member vid
 * @return Reference to member vid
 */
uint16_t& ib::sim::eth::idl::EthTagControlInformation::vid()
{
    return m_vid;
}

size_t ib::sim::eth::idl::EthTagControlInformation::getKeyMaxCdrSerializedSize(size_t current_alignment)
{
	size_t current_align = current_alignment;






    return current_align;
}

bool ib::sim::eth::idl::EthTagControlInformation::isKeyDefined()
{
   return false;
}

void ib::sim::eth::idl::EthTagControlInformation::serializeKey(eprosima::fastcdr::Cdr &scdr) const
{
	(void) scdr;
	 
	 
	 
}


ib::sim::eth::idl::EthMessage::EthMessage()
{

    m_transmitId = 0;
    m_timestampNs = 0;


}

ib::sim::eth::idl::EthMessage::~EthMessage()
{




}

ib::sim::eth::idl::EthMessage::EthMessage(const EthMessage &x)
{
    m_senderAddr = x.m_senderAddr;
    m_transmitId = x.m_transmitId;
    m_timestampNs = x.m_timestampNs;
    m_rawFrame = x.m_rawFrame;
}

ib::sim::eth::idl::EthMessage::EthMessage(EthMessage &&x)
{
    m_senderAddr = std::move(x.m_senderAddr);
    m_transmitId = x.m_transmitId;
    m_timestampNs = x.m_timestampNs;
    m_rawFrame = std::move(x.m_rawFrame);
}

ib::sim::eth::idl::EthMessage& ib::sim::eth::idl::EthMessage::operator=(const EthMessage &x)
{

    m_senderAddr = x.m_senderAddr;
    m_transmitId = x.m_transmitId;
    m_timestampNs = x.m_timestampNs;
    m_rawFrame = x.m_rawFrame;

    return *this;
}

ib::sim::eth::idl::EthMessage& ib::sim::eth::idl::EthMessage::operator=(EthMessage &&x)
{

    m_senderAddr = std::move(x.m_senderAddr);
    m_transmitId = x.m_transmitId;
    m_timestampNs = x.m_timestampNs;
    m_rawFrame = std::move(x.m_rawFrame);

    return *this;
}

size_t ib::sim::eth::idl::EthMessage::getMaxCdrSerializedSize(size_t current_alignment)
{
    size_t initial_alignment = current_alignment;


    current_alignment += ib::mw::idl::EndpointAddress::getMaxCdrSerializedSize(current_alignment);
    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);


    current_alignment += 8 + eprosima::fastcdr::Cdr::alignment(current_alignment, 8);


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);

    current_alignment += (100 * 1) + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);




    return current_alignment - initial_alignment;
}

size_t ib::sim::eth::idl::EthMessage::getCdrSerializedSize(const ib::sim::eth::idl::EthMessage& data, size_t current_alignment)
{
    (void)data;
    size_t initial_alignment = current_alignment;


    current_alignment += ib::mw::idl::EndpointAddress::getCdrSerializedSize(data.senderAddr(), current_alignment);
    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);


    current_alignment += 8 + eprosima::fastcdr::Cdr::alignment(current_alignment, 8);


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);

    current_alignment += (data.rawFrame().size() * 1) + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);




    return current_alignment - initial_alignment;
}

void ib::sim::eth::idl::EthMessage::serialize(eprosima::fastcdr::Cdr &scdr) const
{

    scdr << m_senderAddr;
    scdr << m_transmitId;
    scdr << m_timestampNs;
    scdr << m_rawFrame;
}

void ib::sim::eth::idl::EthMessage::deserialize(eprosima::fastcdr::Cdr &dcdr)
{

    dcdr >> m_senderAddr;
    dcdr >> m_transmitId;
    dcdr >> m_timestampNs;
    dcdr >> m_rawFrame;
}

/*!
 * @brief This function copies the value in member senderAddr
 * @param _senderAddr New value to be copied in member senderAddr
 */
void ib::sim::eth::idl::EthMessage::senderAddr(const ib::mw::idl::EndpointAddress &_senderAddr)
{
m_senderAddr = _senderAddr;
}

/*!
 * @brief This function moves the value in member senderAddr
 * @param _senderAddr New value to be moved in member senderAddr
 */
void ib::sim::eth::idl::EthMessage::senderAddr(ib::mw::idl::EndpointAddress &&_senderAddr)
{
m_senderAddr = std::move(_senderAddr);
}

/*!
 * @brief This function returns a constant reference to member senderAddr
 * @return Constant reference to member senderAddr
 */
const ib::mw::idl::EndpointAddress& ib::sim::eth::idl::EthMessage::senderAddr() const
{
    return m_senderAddr;
}

/*!
 * @brief This function returns a reference to member senderAddr
 * @return Reference to member senderAddr
 */
ib::mw::idl::EndpointAddress& ib::sim::eth::idl::EthMessage::senderAddr()
{
    return m_senderAddr;
}
/*!
 * @brief This function sets a value in member transmitId
 * @param _transmitId New value for member transmitId
 */
void ib::sim::eth::idl::EthMessage::transmitId(uint32_t _transmitId)
{
m_transmitId = _transmitId;
}

/*!
 * @brief This function returns the value of member transmitId
 * @return Value of member transmitId
 */
uint32_t ib::sim::eth::idl::EthMessage::transmitId() const
{
    return m_transmitId;
}

/*!
 * @brief This function returns a reference to member transmitId
 * @return Reference to member transmitId
 */
uint32_t& ib::sim::eth::idl::EthMessage::transmitId()
{
    return m_transmitId;
}
/*!
 * @brief This function sets a value in member timestampNs
 * @param _timestampNs New value for member timestampNs
 */
void ib::sim::eth::idl::EthMessage::timestampNs(int64_t _timestampNs)
{
m_timestampNs = _timestampNs;
}

/*!
 * @brief This function returns the value of member timestampNs
 * @return Value of member timestampNs
 */
int64_t ib::sim::eth::idl::EthMessage::timestampNs() const
{
    return m_timestampNs;
}

/*!
 * @brief This function returns a reference to member timestampNs
 * @return Reference to member timestampNs
 */
int64_t& ib::sim::eth::idl::EthMessage::timestampNs()
{
    return m_timestampNs;
}
/*!
 * @brief This function copies the value in member rawFrame
 * @param _rawFrame New value to be copied in member rawFrame
 */
void ib::sim::eth::idl::EthMessage::rawFrame(const std::vector<uint8_t> &_rawFrame)
{
m_rawFrame = _rawFrame;
}

/*!
 * @brief This function moves the value in member rawFrame
 * @param _rawFrame New value to be moved in member rawFrame
 */
void ib::sim::eth::idl::EthMessage::rawFrame(std::vector<uint8_t> &&_rawFrame)
{
m_rawFrame = std::move(_rawFrame);
}

/*!
 * @brief This function returns a constant reference to member rawFrame
 * @return Constant reference to member rawFrame
 */
const std::vector<uint8_t>& ib::sim::eth::idl::EthMessage::rawFrame() const
{
    return m_rawFrame;
}

/*!
 * @brief This function returns a reference to member rawFrame
 * @return Reference to member rawFrame
 */
std::vector<uint8_t>& ib::sim::eth::idl::EthMessage::rawFrame()
{
    return m_rawFrame;
}

size_t ib::sim::eth::idl::EthMessage::getKeyMaxCdrSerializedSize(size_t current_alignment)
{
	size_t current_align = current_alignment;


     current_align += ib::mw::idl::EndpointAddress::getMaxCdrSerializedSize(current_align); 




    return current_align;
}

bool ib::sim::eth::idl::EthMessage::isKeyDefined()
{
   return true;
}

void ib::sim::eth::idl::EthMessage::serializeKey(eprosima::fastcdr::Cdr &scdr) const
{
	(void) scdr;
	 scdr << m_senderAddr;  
	 
	 
	 
}


ib::sim::eth::idl::EthTransmitAcknowledge::EthTransmitAcknowledge()
{

    m_transmitId = 0;
    memset(&m_sourceMac, 0, (6) * 1);
    m_timestampNs = 0;
    m_status = ib::sim::eth::idl::Transmitted;

}

ib::sim::eth::idl::EthTransmitAcknowledge::~EthTransmitAcknowledge()
{





}

ib::sim::eth::idl::EthTransmitAcknowledge::EthTransmitAcknowledge(const EthTransmitAcknowledge &x)
{
    m_senderAddr = x.m_senderAddr;
    m_transmitId = x.m_transmitId;
    m_sourceMac = x.m_sourceMac;
    m_timestampNs = x.m_timestampNs;
    m_status = x.m_status;
}

ib::sim::eth::idl::EthTransmitAcknowledge::EthTransmitAcknowledge(EthTransmitAcknowledge &&x)
{
    m_senderAddr = std::move(x.m_senderAddr);
    m_transmitId = x.m_transmitId;
    m_sourceMac = std::move(x.m_sourceMac);
    m_timestampNs = x.m_timestampNs;
    m_status = x.m_status;
}

ib::sim::eth::idl::EthTransmitAcknowledge& ib::sim::eth::idl::EthTransmitAcknowledge::operator=(const EthTransmitAcknowledge &x)
{

    m_senderAddr = x.m_senderAddr;
    m_transmitId = x.m_transmitId;
    m_sourceMac = x.m_sourceMac;
    m_timestampNs = x.m_timestampNs;
    m_status = x.m_status;

    return *this;
}

ib::sim::eth::idl::EthTransmitAcknowledge& ib::sim::eth::idl::EthTransmitAcknowledge::operator=(EthTransmitAcknowledge &&x)
{

    m_senderAddr = std::move(x.m_senderAddr);
    m_transmitId = x.m_transmitId;
    m_sourceMac = std::move(x.m_sourceMac);
    m_timestampNs = x.m_timestampNs;
    m_status = x.m_status;

    return *this;
}

size_t ib::sim::eth::idl::EthTransmitAcknowledge::getMaxCdrSerializedSize(size_t current_alignment)
{
    size_t initial_alignment = current_alignment;


    current_alignment += ib::mw::idl::EndpointAddress::getMaxCdrSerializedSize(current_alignment);
    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);


    current_alignment += ((6) * 1) + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);


    current_alignment += 8 + eprosima::fastcdr::Cdr::alignment(current_alignment, 8);


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);



    return current_alignment - initial_alignment;
}

size_t ib::sim::eth::idl::EthTransmitAcknowledge::getCdrSerializedSize(const ib::sim::eth::idl::EthTransmitAcknowledge& data, size_t current_alignment)
{
    (void)data;
    size_t initial_alignment = current_alignment;


    current_alignment += ib::mw::idl::EndpointAddress::getCdrSerializedSize(data.senderAddr(), current_alignment);
    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);


    current_alignment += ((6) * 1) + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);

    current_alignment += 8 + eprosima::fastcdr::Cdr::alignment(current_alignment, 8);


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);



    return current_alignment - initial_alignment;
}

void ib::sim::eth::idl::EthTransmitAcknowledge::serialize(eprosima::fastcdr::Cdr &scdr) const
{

    scdr << m_senderAddr;
    scdr << m_transmitId;
    scdr << m_sourceMac;
    scdr << m_timestampNs;
    scdr << (uint32_t)m_status;
}

void ib::sim::eth::idl::EthTransmitAcknowledge::deserialize(eprosima::fastcdr::Cdr &dcdr)
{

    dcdr >> m_senderAddr;
    dcdr >> m_transmitId;
    dcdr >> m_sourceMac;
    dcdr >> m_timestampNs;
    {
        uint32_t enum_value = 0;
        dcdr >> enum_value;
        m_status = (ib::sim::eth::idl::EthTransmitStatus)enum_value;
    }

}

/*!
 * @brief This function copies the value in member senderAddr
 * @param _senderAddr New value to be copied in member senderAddr
 */
void ib::sim::eth::idl::EthTransmitAcknowledge::senderAddr(const ib::mw::idl::EndpointAddress &_senderAddr)
{
m_senderAddr = _senderAddr;
}

/*!
 * @brief This function moves the value in member senderAddr
 * @param _senderAddr New value to be moved in member senderAddr
 */
void ib::sim::eth::idl::EthTransmitAcknowledge::senderAddr(ib::mw::idl::EndpointAddress &&_senderAddr)
{
m_senderAddr = std::move(_senderAddr);
}

/*!
 * @brief This function returns a constant reference to member senderAddr
 * @return Constant reference to member senderAddr
 */
const ib::mw::idl::EndpointAddress& ib::sim::eth::idl::EthTransmitAcknowledge::senderAddr() const
{
    return m_senderAddr;
}

/*!
 * @brief This function returns a reference to member senderAddr
 * @return Reference to member senderAddr
 */
ib::mw::idl::EndpointAddress& ib::sim::eth::idl::EthTransmitAcknowledge::senderAddr()
{
    return m_senderAddr;
}
/*!
 * @brief This function sets a value in member transmitId
 * @param _transmitId New value for member transmitId
 */
void ib::sim::eth::idl::EthTransmitAcknowledge::transmitId(uint32_t _transmitId)
{
m_transmitId = _transmitId;
}

/*!
 * @brief This function returns the value of member transmitId
 * @return Value of member transmitId
 */
uint32_t ib::sim::eth::idl::EthTransmitAcknowledge::transmitId() const
{
    return m_transmitId;
}

/*!
 * @brief This function returns a reference to member transmitId
 * @return Reference to member transmitId
 */
uint32_t& ib::sim::eth::idl::EthTransmitAcknowledge::transmitId()
{
    return m_transmitId;
}
/*!
 * @brief This function copies the value in member sourceMac
 * @param _sourceMac New value to be copied in member sourceMac
 */
void ib::sim::eth::idl::EthTransmitAcknowledge::sourceMac(const std::array<uint8_t, 6> &_sourceMac)
{
m_sourceMac = _sourceMac;
}

/*!
 * @brief This function moves the value in member sourceMac
 * @param _sourceMac New value to be moved in member sourceMac
 */
void ib::sim::eth::idl::EthTransmitAcknowledge::sourceMac(std::array<uint8_t, 6> &&_sourceMac)
{
m_sourceMac = std::move(_sourceMac);
}

/*!
 * @brief This function returns a constant reference to member sourceMac
 * @return Constant reference to member sourceMac
 */
const std::array<uint8_t, 6>& ib::sim::eth::idl::EthTransmitAcknowledge::sourceMac() const
{
    return m_sourceMac;
}

/*!
 * @brief This function returns a reference to member sourceMac
 * @return Reference to member sourceMac
 */
std::array<uint8_t, 6>& ib::sim::eth::idl::EthTransmitAcknowledge::sourceMac()
{
    return m_sourceMac;
}
/*!
 * @brief This function sets a value in member timestampNs
 * @param _timestampNs New value for member timestampNs
 */
void ib::sim::eth::idl::EthTransmitAcknowledge::timestampNs(int64_t _timestampNs)
{
m_timestampNs = _timestampNs;
}

/*!
 * @brief This function returns the value of member timestampNs
 * @return Value of member timestampNs
 */
int64_t ib::sim::eth::idl::EthTransmitAcknowledge::timestampNs() const
{
    return m_timestampNs;
}

/*!
 * @brief This function returns a reference to member timestampNs
 * @return Reference to member timestampNs
 */
int64_t& ib::sim::eth::idl::EthTransmitAcknowledge::timestampNs()
{
    return m_timestampNs;
}
/*!
 * @brief This function sets a value in member status
 * @param _status New value for member status
 */
void ib::sim::eth::idl::EthTransmitAcknowledge::status(ib::sim::eth::idl::EthTransmitStatus _status)
{
m_status = _status;
}

/*!
 * @brief This function returns the value of member status
 * @return Value of member status
 */
ib::sim::eth::idl::EthTransmitStatus ib::sim::eth::idl::EthTransmitAcknowledge::status() const
{
    return m_status;
}

/*!
 * @brief This function returns a reference to member status
 * @return Reference to member status
 */
ib::sim::eth::idl::EthTransmitStatus& ib::sim::eth::idl::EthTransmitAcknowledge::status()
{
    return m_status;
}

size_t ib::sim::eth::idl::EthTransmitAcknowledge::getKeyMaxCdrSerializedSize(size_t current_alignment)
{
	size_t current_align = current_alignment;


     current_align += ib::mw::idl::EndpointAddress::getMaxCdrSerializedSize(current_align); 





    return current_align;
}

bool ib::sim::eth::idl::EthTransmitAcknowledge::isKeyDefined()
{
   return true;
}

void ib::sim::eth::idl::EthTransmitAcknowledge::serializeKey(eprosima::fastcdr::Cdr &scdr) const
{
	(void) scdr;
	 scdr << m_senderAddr;  
	 
	 
	 
	 
}


ib::sim::eth::idl::EthStatus::EthStatus()
{

    m_timestampNs = 0;
    m_state = ib::sim::eth::idl::Inactive;
    m_bitRate = 0;

}

ib::sim::eth::idl::EthStatus::~EthStatus()
{




}

ib::sim::eth::idl::EthStatus::EthStatus(const EthStatus &x)
{
    m_senderAddr = x.m_senderAddr;
    m_timestampNs = x.m_timestampNs;
    m_state = x.m_state;
    m_bitRate = x.m_bitRate;
}

ib::sim::eth::idl::EthStatus::EthStatus(EthStatus &&x)
{
    m_senderAddr = std::move(x.m_senderAddr);
    m_timestampNs = x.m_timestampNs;
    m_state = x.m_state;
    m_bitRate = x.m_bitRate;
}

ib::sim::eth::idl::EthStatus& ib::sim::eth::idl::EthStatus::operator=(const EthStatus &x)
{

    m_senderAddr = x.m_senderAddr;
    m_timestampNs = x.m_timestampNs;
    m_state = x.m_state;
    m_bitRate = x.m_bitRate;

    return *this;
}

ib::sim::eth::idl::EthStatus& ib::sim::eth::idl::EthStatus::operator=(EthStatus &&x)
{

    m_senderAddr = std::move(x.m_senderAddr);
    m_timestampNs = x.m_timestampNs;
    m_state = x.m_state;
    m_bitRate = x.m_bitRate;

    return *this;
}

size_t ib::sim::eth::idl::EthStatus::getMaxCdrSerializedSize(size_t current_alignment)
{
    size_t initial_alignment = current_alignment;


    current_alignment += ib::mw::idl::EndpointAddress::getMaxCdrSerializedSize(current_alignment);
    current_alignment += 8 + eprosima::fastcdr::Cdr::alignment(current_alignment, 8);


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);



    return current_alignment - initial_alignment;
}

size_t ib::sim::eth::idl::EthStatus::getCdrSerializedSize(const ib::sim::eth::idl::EthStatus& data, size_t current_alignment)
{
    (void)data;
    size_t initial_alignment = current_alignment;


    current_alignment += ib::mw::idl::EndpointAddress::getCdrSerializedSize(data.senderAddr(), current_alignment);
    current_alignment += 8 + eprosima::fastcdr::Cdr::alignment(current_alignment, 8);


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);



    return current_alignment - initial_alignment;
}

void ib::sim::eth::idl::EthStatus::serialize(eprosima::fastcdr::Cdr &scdr) const
{

    scdr << m_senderAddr;
    scdr << m_timestampNs;
    scdr << (uint32_t)m_state;
    scdr << m_bitRate;
}

void ib::sim::eth::idl::EthStatus::deserialize(eprosima::fastcdr::Cdr &dcdr)
{

    dcdr >> m_senderAddr;
    dcdr >> m_timestampNs;
    {
        uint32_t enum_value = 0;
        dcdr >> enum_value;
        m_state = (ib::sim::eth::idl::EthState)enum_value;
    }

    dcdr >> m_bitRate;
}

/*!
 * @brief This function copies the value in member senderAddr
 * @param _senderAddr New value to be copied in member senderAddr
 */
void ib::sim::eth::idl::EthStatus::senderAddr(const ib::mw::idl::EndpointAddress &_senderAddr)
{
m_senderAddr = _senderAddr;
}

/*!
 * @brief This function moves the value in member senderAddr
 * @param _senderAddr New value to be moved in member senderAddr
 */
void ib::sim::eth::idl::EthStatus::senderAddr(ib::mw::idl::EndpointAddress &&_senderAddr)
{
m_senderAddr = std::move(_senderAddr);
}

/*!
 * @brief This function returns a constant reference to member senderAddr
 * @return Constant reference to member senderAddr
 */
const ib::mw::idl::EndpointAddress& ib::sim::eth::idl::EthStatus::senderAddr() const
{
    return m_senderAddr;
}

/*!
 * @brief This function returns a reference to member senderAddr
 * @return Reference to member senderAddr
 */
ib::mw::idl::EndpointAddress& ib::sim::eth::idl::EthStatus::senderAddr()
{
    return m_senderAddr;
}
/*!
 * @brief This function sets a value in member timestampNs
 * @param _timestampNs New value for member timestampNs
 */
void ib::sim::eth::idl::EthStatus::timestampNs(int64_t _timestampNs)
{
m_timestampNs = _timestampNs;
}

/*!
 * @brief This function returns the value of member timestampNs
 * @return Value of member timestampNs
 */
int64_t ib::sim::eth::idl::EthStatus::timestampNs() const
{
    return m_timestampNs;
}

/*!
 * @brief This function returns a reference to member timestampNs
 * @return Reference to member timestampNs
 */
int64_t& ib::sim::eth::idl::EthStatus::timestampNs()
{
    return m_timestampNs;
}
/*!
 * @brief This function sets a value in member state
 * @param _state New value for member state
 */
void ib::sim::eth::idl::EthStatus::state(ib::sim::eth::idl::EthState _state)
{
m_state = _state;
}

/*!
 * @brief This function returns the value of member state
 * @return Value of member state
 */
ib::sim::eth::idl::EthState ib::sim::eth::idl::EthStatus::state() const
{
    return m_state;
}

/*!
 * @brief This function returns a reference to member state
 * @return Reference to member state
 */
ib::sim::eth::idl::EthState& ib::sim::eth::idl::EthStatus::state()
{
    return m_state;
}
/*!
 * @brief This function sets a value in member bitRate
 * @param _bitRate New value for member bitRate
 */
void ib::sim::eth::idl::EthStatus::bitRate(uint32_t _bitRate)
{
m_bitRate = _bitRate;
}

/*!
 * @brief This function returns the value of member bitRate
 * @return Value of member bitRate
 */
uint32_t ib::sim::eth::idl::EthStatus::bitRate() const
{
    return m_bitRate;
}

/*!
 * @brief This function returns a reference to member bitRate
 * @return Reference to member bitRate
 */
uint32_t& ib::sim::eth::idl::EthStatus::bitRate()
{
    return m_bitRate;
}

size_t ib::sim::eth::idl::EthStatus::getKeyMaxCdrSerializedSize(size_t current_alignment)
{
	size_t current_align = current_alignment;


     current_align += ib::mw::idl::EndpointAddress::getMaxCdrSerializedSize(current_align); 




    return current_align;
}

bool ib::sim::eth::idl::EthStatus::isKeyDefined()
{
   return true;
}

void ib::sim::eth::idl::EthStatus::serializeKey(eprosima::fastcdr::Cdr &scdr) const
{
	(void) scdr;
	 scdr << m_senderAddr;  
	 
	 
	 
}


ib::sim::eth::idl::EthSetMode::EthSetMode()
{

    m_mode = ib::sim::eth::idl::ModeInactive;

}

ib::sim::eth::idl::EthSetMode::~EthSetMode()
{


}

ib::sim::eth::idl::EthSetMode::EthSetMode(const EthSetMode &x)
{
    m_senderAddr = x.m_senderAddr;
    m_mode = x.m_mode;
}

ib::sim::eth::idl::EthSetMode::EthSetMode(EthSetMode &&x)
{
    m_senderAddr = std::move(x.m_senderAddr);
    m_mode = x.m_mode;
}

ib::sim::eth::idl::EthSetMode& ib::sim::eth::idl::EthSetMode::operator=(const EthSetMode &x)
{

    m_senderAddr = x.m_senderAddr;
    m_mode = x.m_mode;

    return *this;
}

ib::sim::eth::idl::EthSetMode& ib::sim::eth::idl::EthSetMode::operator=(EthSetMode &&x)
{

    m_senderAddr = std::move(x.m_senderAddr);
    m_mode = x.m_mode;

    return *this;
}

size_t ib::sim::eth::idl::EthSetMode::getMaxCdrSerializedSize(size_t current_alignment)
{
    size_t initial_alignment = current_alignment;


    current_alignment += ib::mw::idl::EndpointAddress::getMaxCdrSerializedSize(current_alignment);
    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);



    return current_alignment - initial_alignment;
}

size_t ib::sim::eth::idl::EthSetMode::getCdrSerializedSize(const ib::sim::eth::idl::EthSetMode& data, size_t current_alignment)
{
    (void)data;
    size_t initial_alignment = current_alignment;


    current_alignment += ib::mw::idl::EndpointAddress::getCdrSerializedSize(data.senderAddr(), current_alignment);
    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);



    return current_alignment - initial_alignment;
}

void ib::sim::eth::idl::EthSetMode::serialize(eprosima::fastcdr::Cdr &scdr) const
{

    scdr << m_senderAddr;
    scdr << (uint32_t)m_mode;
}

void ib::sim::eth::idl::EthSetMode::deserialize(eprosima::fastcdr::Cdr &dcdr)
{

    dcdr >> m_senderAddr;
    {
        uint32_t enum_value = 0;
        dcdr >> enum_value;
        m_mode = (ib::sim::eth::idl::EthMode)enum_value;
    }

}

/*!
 * @brief This function copies the value in member senderAddr
 * @param _senderAddr New value to be copied in member senderAddr
 */
void ib::sim::eth::idl::EthSetMode::senderAddr(const ib::mw::idl::EndpointAddress &_senderAddr)
{
m_senderAddr = _senderAddr;
}

/*!
 * @brief This function moves the value in member senderAddr
 * @param _senderAddr New value to be moved in member senderAddr
 */
void ib::sim::eth::idl::EthSetMode::senderAddr(ib::mw::idl::EndpointAddress &&_senderAddr)
{
m_senderAddr = std::move(_senderAddr);
}

/*!
 * @brief This function returns a constant reference to member senderAddr
 * @return Constant reference to member senderAddr
 */
const ib::mw::idl::EndpointAddress& ib::sim::eth::idl::EthSetMode::senderAddr() const
{
    return m_senderAddr;
}

/*!
 * @brief This function returns a reference to member senderAddr
 * @return Reference to member senderAddr
 */
ib::mw::idl::EndpointAddress& ib::sim::eth::idl::EthSetMode::senderAddr()
{
    return m_senderAddr;
}
/*!
 * @brief This function sets a value in member mode
 * @param _mode New value for member mode
 */
void ib::sim::eth::idl::EthSetMode::mode(ib::sim::eth::idl::EthMode _mode)
{
m_mode = _mode;
}

/*!
 * @brief This function returns the value of member mode
 * @return Value of member mode
 */
ib::sim::eth::idl::EthMode ib::sim::eth::idl::EthSetMode::mode() const
{
    return m_mode;
}

/*!
 * @brief This function returns a reference to member mode
 * @return Reference to member mode
 */
ib::sim::eth::idl::EthMode& ib::sim::eth::idl::EthSetMode::mode()
{
    return m_mode;
}

size_t ib::sim::eth::idl::EthSetMode::getKeyMaxCdrSerializedSize(size_t current_alignment)
{
	size_t current_align = current_alignment;


     current_align += ib::mw::idl::EndpointAddress::getMaxCdrSerializedSize(current_align); 


    return current_align;
}

bool ib::sim::eth::idl::EthSetMode::isKeyDefined()
{
   return true;
}

void ib::sim::eth::idl::EthSetMode::serializeKey(eprosima::fastcdr::Cdr &scdr) const
{
	(void) scdr;
	 scdr << m_senderAddr;  
	 
}




