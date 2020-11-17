#pragma once
#include <shaiya/hooks/command/Command.hpp>

/**
 * Handles the teleportation of a player.
 */
class PlayerTeleportCommand: public Command
{
public:
    /**
     * Executes this command.
     * @param args  The command arguments.
     * @return      The output text.
     */
    std::string execute(const std::vector<std::string>& args) override;

    /**
     * The identifier of this command.
     * @return  The identifier
     */
    const char* identifier() const override;
};