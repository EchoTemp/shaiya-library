#include <shaiya/World.hpp>
#include <shaiya/utils/toml.hpp>

#include <iomanip>

/**
 * A vector of functions that gets executed when the user is registered to the game world.
 */
std::vector<std::function<void(CUser*)>> World::userRegisteredFunctors;

/**
 * A vector of functions that gets executed when the user is removed from the game world.
 */
std::vector<std::function<void(CUser*)>> World::userDeregisteredFunctors;

/**
 * The address for the SConnection::Send function
 */
constexpr const auto SConnectionSendAddress = 0x4ED0E0;

/**
 * The function definition for the SConnection::Send function
 */
typedef void(__thiscall* SConnectionSendFunc)(CUser*, void*, int);

/**
 * The SConnection::Send function
 */
SConnectionSendFunc sConnectionSend = (SConnectionSendFunc)SConnectionSendAddress;

/**
 * Initialises the Shaiya game world mod by setting up various
 * function hooks to add our custom functionality.
 * @param config    The configuration table
 */
void World::init(const toml::table& config)
{
    // Initialise the custom memory block
    LOG(INFO) << "Populating memory at 0x" << std::uppercase << std::hex << CUPS_MEMORY_BLOCK;
    *((int*)CUPS_MEMORY_BLOCK) = (int)new Cups();

    // Initialise the hooks
    LOG(INFO) << "Initialising hooks...";
    hook<HookType::World>(config);
    hook<HookType::Character>(config);
}

/**
 * Register the user to the game world.
 * @param user  The user to register
 */
void World::registerUser(CUser* user)
{
    auto* list = cups()->userList;
    list->count++;

    // Store the user in the array
    for (auto i = 0; i < MAX_PLAYER_CAPACITY; i++)
    {
        // Store the user at a free index, and store the index in the hg variable
        // as it's not used by Shaiya, and allows us to very quickly register them.
        if (list->elements[i] == nullptr)
        {
            user->hg          = i;
            list->elements[i] = user;
            break;
        }
    }

    // Execute the registration functions
    for (auto&& func: userRegisteredFunctors)
        func(user);
}

/**
 * Deregisters the user from the game world.
 * @param user  The user to deregister.
 */
void World::deregisterUser(CUser* user)
{
    // Remove the user from the player list
    auto* list = cups()->userList;
    list->count--;
    list->elements[user->hg] = nullptr;
    user->hg                 = 0;

    // Execute the deregistration functions
    for (auto&& func: userDeregisteredFunctors)
        func(user);
}

/**
 * Semds a packet to the user.
 * @param user      The user instance
 * @param packet    The packet payload
 * @param length    The length of the packet
 */
void World::sendPacket(CUser* user, void* packet, uint32_t length)
{
    sConnectionSend(user, packet, length);
}

/**
 * Gets a user for this character id.
 * @param id    The character id.
 * @return      The user instance.
 */
CUser* World::userForId(uint32_t id)
{
    auto* list = cups()->userList;
    for (auto&& user: list->elements)
    {
        if (user && user->charId == id)
            return user;
    }
    return nullptr;
}