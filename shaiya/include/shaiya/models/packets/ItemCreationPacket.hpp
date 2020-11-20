#pragma once

#include <shaiya/models/NexonBoolean.hpp>

#include <array>
#include <cstdint>

/**
 * A packet that represents the request to create an item.
 */
#pragma pack(push, 1)
struct ItemCreationRequest
{
    uint16_t opcode{ 0x0807 };
    std::array<unsigned char, 3> bags{};
    std::array<unsigned char, 3> slots{};
};
#pragma pack(pop)

/**
 * A packet that represents the result of an item creation.
 */
#pragma pack(push, 1)
struct ItemCreationUpdate
{
    uint16_t opcode{ 0x0807 };
    NexonBoolean success{ true };
    uint8_t bag{};
    uint8_t slot{};
    uint8_t type{};
    uint8_t typeId{};
    uint16_t endurance{};
    std::array<char, 6> lapis{};
    uint8_t quantity{};
    VariableString<21> craftname;
};
#pragma pack(pop)