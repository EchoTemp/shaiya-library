#pragma once
#include <shaiya/models/VariableString.hpp>

/**
 * Represents an update to an item's lapis.
 */
#pragma pack(push, 1)
struct ItemLapisUpdate
{
    uint16_t opcode{ 0x0711 };
    uint32_t userId{ 0 };
    uint8_t bag{ 0 };
    uint8_t slot{ 0 };
    std::array<char, 6> lapis{};
    uint32_t money{};
};
#pragma pack(pop)