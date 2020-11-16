#pragma once

#include <cstdint>
#include <array>

/**
 * The packet that informs the user of their Aeria Points.
 */
#pragma pack(push, 1)
struct ItemCreationPacket
{
    uint16_t opcode { 0x0807 };
    std::array<unsigned char, 3> bags{};
    std::array<unsigned char, 3> slots{};
};
#pragma pack(pop)