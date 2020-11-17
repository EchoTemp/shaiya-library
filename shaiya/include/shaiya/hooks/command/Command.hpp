#pragma once
#include <string>
#include <vector>

/**
 * Represents a command that may be executed by the ps_game console.
 */
class Command
{
public:
    /**
     * Executes this command.
     * @param args  The command arguments.
     * @return      The output text.
     */
    virtual std::string execute(const std::vector<std::string>& args) = 0;

    /**
     * The identifier of this command.
     * @return  The identifier
     */
    virtual const char* identifier() const = 0;
};