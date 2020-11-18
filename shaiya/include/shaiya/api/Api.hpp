#pragma once
#include <cstdint>

/**
 * Represents a collection of functions that are designed to be remotely executed.
 */
namespace api
{
    /**
     * Finds a user by name and teleports them.
     * @param name  The name of the user.
     * @param map   The destination map.
     * @param x     The x coordinate.
     * @param z     The z coordinate.
     */
    void teleportUserByName(const char* name, uint16_t map, float x, float z);
}