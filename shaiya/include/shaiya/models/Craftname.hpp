#pragma once

#include <cstdint>

/**
 * Represents a craftname
 */
struct Craftname
{
    int32_t strength { 0 };
    int32_t dexterity { 0 };
    int32_t resistance { 0 };
    int32_t intelligence { 0 };
    int32_t wisdom { 0 };
    int32_t luck { 0 };
    int32_t hitpoints { 0 };
    int32_t mana { 0 };
    int32_t stamina { 0 };
};