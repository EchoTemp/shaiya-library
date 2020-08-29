#include <shaiya/World.hpp>

/**
 * Initialises the game world hooks.
 */
template <> void World::hook<HookType::World>()
{
    LOG(INFO) << "Init world hooks";
}