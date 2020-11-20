#pragma once
#include <cstdint>

/**
 * A utility class used for sending packets to the database agent.
 */
class DbAgent
{
public:
    /**
     * A utility function used for sending a packet to the database agent.
     * @param packet    The packet structure.
     * @param length    The length of the packet.
     */
    static void sendPacket(void* packet, uint32_t length);
};