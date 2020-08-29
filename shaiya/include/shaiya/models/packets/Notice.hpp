#pragma once

#include <array>

/**
 * Represents a game notice packet.
 */
#pragma pack(push, 1)
struct Notice
{
    uint16_t opcode { 0xF90B };
    uint8_t length { 0 };
    std::array<char, 128> message { };
};
#pragma pack(pop)