#include <shaiya/DbAgent.hpp>
#include <shaiya/World.hpp>

/**
 * The database agent client.
 */
constexpr auto DbAgentConnection = 0x010A2628;

/**
 * A utility function used for sending a packet to the database agent.
 * @param packet    The packet structure.
 * @param length    The length of the packet.
 */
void DbAgent::sendPacket(void* packet, uint32_t length)
{
    World::sendPacket((CUser*)DbAgentConnection, packet, length);
}