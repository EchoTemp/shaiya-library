#pragma once

#include <array>

/**
 * A basic array container.
 */
#pragma pack(push, 1)
template<typename T, uint16_t Capacity>
struct List
{
    uint16_t count { 0 };
    uint16_t capacity { Capacity };
    std::array<T*, Capacity> elements { nullptr };
};
#pragma pack(pop)