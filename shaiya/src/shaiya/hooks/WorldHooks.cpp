#include <shaiya/World.hpp>

/**
 * Initialises the game world hooks.
 */
template <> void World::hook<HookType::World>(const toml::table& config)
{
    LOG(INFO) << "Init world hooks";
}