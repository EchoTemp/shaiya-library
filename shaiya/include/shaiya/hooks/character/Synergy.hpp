#pragma once

#include <array>
#include <string>
#include <shaiya/models/Craftname.hpp>

/**
 * The maximum number of items and bonuses in a synergy.
 */
constexpr const auto MAX_SET_SIZE = 13;

/**
 * Represents a synergy set.
 */
struct Synergy
{

    /**
     * The id of the synergy.
     */
    size_t id { 0 };

    /**
     * The name of the set
     */
    std::string name { "Undefined" };

    /**
     * The array of items that contribute to this set.
     */
    std::array<size_t, MAX_SET_SIZE> items { };

    /**
     * The craftname bonuses to apply.
     */
    std::array<Craftname, MAX_SET_SIZE> bonuses { };
};