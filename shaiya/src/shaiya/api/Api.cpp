#include <shaiya/World.hpp>
#include <shaiya/api/Api.hpp>
#include <shaiya/models/CUser.hpp>

/**
 * Finds a user by name and teleports them.
 * @param name  The name of the user.
 * @param map   The destination map.
 * @param x     The x coordinate.
 * @param z     The z coordinate.
 */
void api::teleportUserByName(const char* name, uint16_t map, float x, float z)
{
    auto users = World::getUser([name](CUser* user) { return user->name == name; });

    for (auto&& user: users)
        user->teleport(map, x, z);
}