#ifndef PACKAGEMANAGER_PLUGIN_H
#define PACKAGEMANAGER_PLUGIN_H

#ifdef _WIN32
#define EXTENSION ".dll"
#elif __APPLE__
#define EXTENSION ".dylib"
#else
#define EXTENSION ".so"
#endif

#include <functional>
#include <string>
#include <utility>

enum CORE_CALLS {
    REGISTER_CHILD, // Register a child plugin, ARGS: pluginName (string), RETURNS: void
    GET_CONFIG, // Request the value of a key in your config, AGRS: key (string) [for nested key1:key2:key3], RETURNS: value (string)
    SET_CONFIG, // Set the value of a key in your config, ARGS: key (string) [for nested key1:key2:key3], value (string), RETURNS: void
};

class Plugin {
    std::function<void()> callback; // Function to call the core
    std::string uuid; // Unique identifier for the plugin, can be used to execute a core call

public:
    virtual int runCommand(const std::string& pluginCalled, int argc, char** argv) = 0; // Core will call this to run a command for you or your child plugins
    virtual void registerPlugin() = 0; // Register the plugin with the core
    std::string name = "PLUGIN_NAME_HERE"; // The name of the plugin
    std::string pluginStack; // The stack of plugins that we are in

    Plugin(const std::function<void*()>& callback, std::string  uuid, std::string pluginStack) : callback(callback), uuid(std::move(uuid)), pluginStack(std::move(pluginStack)) {}
    virtual ~Plugin() = default;
};

#endif
