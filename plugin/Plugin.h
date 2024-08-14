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
#include <iostream>
#include <string>
#include <utility>
#include <helpers/LogHelp.h>
#include <helpers/CoreCall.h>
#include <helpers/CommandHelp.h>

namespace PluginAPI
{
    struct Plugin final
    {
        std::string name = "PLUGIN_NAME_HERE"; // The name of the plugin
        std::string pluginStack; // The stack of plugins that we are in
        std::string version = "PLUGIN_VERSION_HERE"; // The version of the plugin
        CORE_CALLBACK callback; // Function to call the core
        std::string uuid; // Unique identifier for the plugin, can be used to execute a core call

        Plugin(const CORE_CALLBACK& callback, std::string uuid, const std::string& name, const std::string& version, const std::string& pluginStack) : callback(callback),
            uuid(std::move(uuid)), pluginStack(pluginStack), name(name)
        {
            callback(REGISTERED, this->uuid, "'" + name + "'" + pluginStack + " " + version);
        }
    };

    extern "C" ReturnData runCommand(const std::string& pluginCalled, int argc, char** argv);
    void registerPlugin();

    extern "C" int createPlugin(const CORE_CALLBACK& callback, const std::string& uuid, const std::string& pluginStack);
}

#endif
