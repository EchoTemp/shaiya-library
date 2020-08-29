#pragma once

#include <cstdint>

#include <shaiya/models/cups/List.hpp>
#include <shaiya/models/CUser.hpp>

/**
 * The maximum number of players that may be online at a given time.
 */
constexpr const auto MAX_PLAYER_CAPACITY = 2048;

/**
 * A custom data-type that is stored in the process memory. The purpose of this is to store
 * easily accessible data, for using in external applications.
 */
#pragma pack(push, 1)
struct Cups
{
    List<CUser, MAX_PLAYER_CAPACITY>* userList { new List<CUser, MAX_PLAYER_CAPACITY> };
};
#pragma pack(pop)