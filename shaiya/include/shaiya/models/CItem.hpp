#pragma once
#include <shaiya/models/Model.hpp>
#include <shaiya/models/VariableString.hpp>

#include <array>

/**
 * Represents an item instance in the world.
 */
#pragma pack(push, 1)
struct CItem
{
    PAD(64);
    uint8_t type{};
    uint8_t typeId{};
    uint8_t quantity{};
    uint8_t unknown{};
    uint16_t endurance{};
    std::array<char, 6> lapis{};
    VariableString<21> craftname;

    CItem(const CItem& item)
    {
        this->type      = item.type;
        this->typeId    = item.typeId;
        this->quantity  = item.quantity;
        this->unknown   = item.unknown;
        this->endurance = item.endurance;
        this->lapis     = item.lapis;
        this->craftname = item.craftname;
    }

    [[nodiscard]] int itemId() const
    {
        return (type * 1000) + typeId;
    }
};
#pragma pack(pop)