#include <logging/log.hpp>
#include <shaiya/hooks/command/CommandManager.hpp>
#include <shaiya/hooks/command/impl/PlayerTeleportCommand.hpp>

#include <algorithm>
#include <sstream>

/**
 * Initialise the command map.
 */
std::map<std::string, Command*> CommandManager::commands_;

/**
 * The constructor which initialises the commands
 */
void CommandManager::init()
{
    add(new PlayerTeleportCommand());
}

/**
 * Registers a command
 * @param command   The command instance.
 */
void CommandManager::add(Command* command)
{
    commands_[command->identifier()] = command;
}

/**
 * Handles the execution of a command.
 * @param text      The command text.
 * @param output    The output text.
 */
int CommandManager::execute(const char* text, char* output)
{
    std::string command(text);

    std::istringstream stream(command);
    std::vector<std::string> args = { std::istream_iterator<std::string>(stream), {} };

    // Erase the first argument, as it's our identifier
    auto identifier = (*args.begin()).substr(1);
    std::transform(identifier.begin(), identifier.end(), identifier.begin(), [](auto ch) { return std::tolower(ch); });
    args.erase(args.begin());

    // If the command exists
    if (commands_.contains(identifier))
    {
        try
        {
            auto* cmd       = commands_[identifier];
            auto outputText = cmd->execute(args);
            output          = "Hey";
            return 1;
        }
        catch (const std::exception& e)
        {
            LOG(INFO) << e.what();
            return 0;
        }
    }
    return 0;
}