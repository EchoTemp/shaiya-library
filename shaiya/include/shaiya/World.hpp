#pragma once

#include <shaiya/HookType.hpp>
#include <logging/log.hpp>

/**
 * A utility class used for interacting with the Shaiya world.
 */
class World
{
public:

    /**
     * Initialises the Shaiya server mod.
     */
    static void init();

private:

    /**
     * Begins a memory injection.
     * @tparam type The hook type.
     */
    template<HookType type>
    static void hook();

};