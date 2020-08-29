#pragma once

#include <cstdint>

/**
 * The packet that informs the user of their Aeria Points.
 */
#pragma pack(push, 1)
struct AccountPoints
{
    uint16_t opcode { 0x2601 };
    uint32_t points { 0 };
};
#pragma pack(pop)