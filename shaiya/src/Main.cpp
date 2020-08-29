#define EXPORT extern "C" __declspec(dllexport)

#include <shaiya/World.hpp>

INITIALIZE_EASYLOGGINGPP

/**
 * Initialises the Shaiya server mod.
 */
EXPORT void init()
{
    // Create a logging configuration
    using namespace el;
    Configurations conf;

    // Configure the name and log formatting
    conf.setGlobally(ConfigurationType::Format, "[%datetime{%d/%M/%Y %h:%m:%s,%g}] [%fbase:%line] [%level]: %msg");
    conf.setGlobally(ConfigurationType::Filename, "Log/Shaiya.log");

    // Reconfigure the logs
    Loggers::reconfigureAllLoggers(conf);

    // Initialise the game world
    World::init();
}