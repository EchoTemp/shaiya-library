#pragma once
#include <shaiya/hooks/character/CombinationType.hpp>

/**
 * Represents a combination of items.
 */
struct Combination
{
    CombinationType type;
    uint32_t first;
    uint32_t second;
    uint32_t third;
    uint32_t result;
};