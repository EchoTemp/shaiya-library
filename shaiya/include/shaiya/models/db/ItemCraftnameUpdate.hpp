#pragma once
#include <shaiya/models/VariableString.hpp>

/**
 * Represents an update to an item's craftname.
 */
#pragma pack(push, 1)
struct ItemCraftnameUpdate
{
    uint16_t opcode{ 0x0717 };
    uint32_t userId{ 0 };
    uint8_t bag{ 0 };
    uint8_t slot{ 0 };
    VariableString<21> craftname;
};
#pragma pack(pop)