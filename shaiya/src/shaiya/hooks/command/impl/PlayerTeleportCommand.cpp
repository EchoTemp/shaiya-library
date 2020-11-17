#include <shaiya/World.hpp>
#include <shaiya/hooks/command/impl/PlayerTeleportCommand.hpp>

/**
 * Executes this command.
 * @param args  The command arguments.
 */
std::string PlayerTeleportCommand::execute(const std::vector<std::string>& args)
{
    // We need at least 4 arguments (charid, map, x, z)
    if (args.size() < 4)
        return "Invalid usage! Please use as /teleportchar charid map x z";

    auto charId = std::stoi(args.at(0));
    auto map    = std::stoi(args.at(1));
    auto x      = std::stof(args.at(2));
    auto z      = std::stof(args.at(3));

    auto* user = World::userForId(charId);
    if (user)
    {
        user->teleport(map, x, z);
        return "User successfully teleported.";
    }

    return "User not found.";
}

/**
 * The identifier of this command.
 * @return  The identifier
 */
const char* PlayerTeleportCommand::identifier() const
{
    return "teleportchar";
}