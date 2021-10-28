#pragma once
#include <limits.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

    typedef int32_t ib_InterfaceIdentifier;

    // CAN
#define     ib_InterfaceIdentifier_CanFrame               ((int32_t)  1002001)
#define     ib_InterfaceIdentifier_CanTransmitAcknowledge ((int32_t)  1003001)
#define     ib_InterfaceIdentifier_CanFrame_Meta          ((int32_t)  1004001)

// Ethernet
#define     ib_InterfaceIdentifier_EthernetFrame               ((int32_t)  2002001)
#define     ib_InterfaceIdentifier_EthernetTransmitAcknowledge ((int32_t)  2003001)
#define     ib_InterfaceIdentifier_EthernetFrame_Meta          ((int32_t)  2004001)

#ifdef __cplusplus
}
#endif
