#include <shaiya/World.hpp>

/**
 * Initialises the Shaiya game world mod by setting up various
 * function hooks to add our custom functionality.
 */
void World::init()
{
    // Initialise the hooks
    LOG(INFO) << "Initialising world hooks...";
    hook<HookType::World>();
    hook<HookType::Character>();
}