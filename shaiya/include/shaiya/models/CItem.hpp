#pragma once
#include <shaiya/models/Model.hpp>
#include <array>

/**
 * Represents an item instance in the world.
 */
#pragma pack(push, 1)
struct CItem
{
    PAD(64);
    uint8_t type;
    uint8_t typeId;
};
#pragma pack(pop)