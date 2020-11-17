#pragma once

#include <logging/log.hpp>
#include <shaiya/HookType.hpp>
#include <shaiya/models/cups/Cups.hpp>
#include <shaiya/utils/toml.hpp>

#include <vector>

/**
 * The memory address that we used to store our custom memory chunk.
 */
constexpr const auto CUPS_MEMORY_BLOCK = 0xA00000;

/**
 * A utility class used for interacting with the Shaiya world.
 */
class World
{
public:
    /**
     * Initialises the Shaiya server mod.
     * @param config    The configuration table
     */
    static void init(const toml::table& config);

    /**
     * Gets executed when a user is registered to the game world.
     * @param user  The user instance.
     */
    static void registerUser(CUser* user);

    /**
     * Gets executed when a user leaves the game world.
     * @param user  The user instance.
     */
    static void deregisterUser(CUser* user);

    /**
     * Adds a function that should get executed when a user enters the game world.
     * @param function  The function instance.
     */
    static void onUserRegistered(const std::function<void(CUser*)>& function)
    {
        userRegisteredFunctors.push_back(function);
    }

    /**
     * Adds a function that should get executed when a user leaves the game world.
     * @param function  The function instance.
     */
    static void onUserDeregistered(const std::function<void(CUser*)>& function)
    {
        userDeregisteredFunctors.push_back(function);
    }

    /**
     * A utility function used for sending a packet to a user.
     * @param user      The user to send the packet to.
     * @param packet    The packet structure.
     * @param length    The length of the packet.
     */
    static void sendPacket(CUser* user, void* packet, uint32_t length);

    /**
     * Gets a user for this character id.
     * @param id    The character id.
     * @return      The user instance.
     */
    static CUser* userForId(uint32_t id);

    /**
     * Gets the custom memory block.
     * @return  The memory block.
     */
    static Cups* cups()
    {
        return reinterpret_cast<Cups*>(*(int*)CUPS_MEMORY_BLOCK);
    }

private:
    /**
     * Begins a memory injection.
     * @tparam type The hook type.
     */
    template<HookType type>
    static void hook(const toml::table& config);

    /**
     * A vector of functions that gets executed when the user is registered to the game world.
     */
    static std::vector<std::function<void(CUser*)>> userRegisteredFunctors;

    /**
     * A vector of functions that gets executed when the user is removed from the game world.
     */
    static std::vector<std::function<void(CUser*)>> userDeregisteredFunctors;
};