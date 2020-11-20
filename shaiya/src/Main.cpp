#define EXPORT extern "C" __declspec(dllexport)

#include <shaiya/World.hpp>
#include <shaiya/utils/toml.hpp>

INITIALIZE_EASYLOGGINGPP

/**
 * Initialises the Shaiya server mod.
 */
EXPORT void init()
{
    // Parse the TOML configuration file
    auto config = toml::parse_file("Data/Cups.toml");

    // The logging configuration
    auto logging = config["logging"];

    // Create a logging configuration
    using namespace el;
    Configurations conf;

    // Configure the name and log formatting
    conf.setGlobally(ConfigurationType::Format,
                     logging["format"].value_or("[%datetime{%d/%M/%Y %h:%m:%s,%g}] [%fbase:%line] [%level]: %msg"));
    conf.setGlobally(ConfigurationType::Filename, logging["filename"].value_or("Log/Shaiya.log"));
    conf.setGlobally(ConfigurationType::Enabled, logging["enabled"].value_or(false) ? "true" : "false");

    // Reconfigure the logs
    Loggers::reconfigureAllLoggers(conf);

    // Initialise the game world
    World::init(config);
}