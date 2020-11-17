#pragma once
#include <shaiya/hooks/command/Command.hpp>

#include <map>
#include <string>

/**
 * Handles the registration and execution of command commands.
 */
class CommandManager
{
public:
    /**
     * Initialises the commands.
     */
    static void init();

    /**
     * Registers a command
     * @param command   The command instance.
     */
    static void add(Command* command);

    /**
     * Handles the execution of a command.
     * @param text      The command text.
     * @param output    The output text.
     */
    static int execute(const char* text, char* output);

private:
    /**
     * A map of identifiers to their command instances.
     */
    static std::map<std::string, Command*> commands_;
};