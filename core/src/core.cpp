#include "core.h"

#include <iostream>
#include <map>
#include <ostream>
#include <plugin.h>
#include <whereami.h>
#include <pluginLoader.h>

#include "cpr/interceptor.h"

std::map<std::string, std::string> pluginMap;

void registerAllPlugins()
{
    // loop through all the plugins in the plugins directory
    // get the executable path with the help of whereami
    std::string exeDir = whereami().substr(0, whereami().find_last_of('/'));
    // loop through all the dirs in the plugins directory
    for (const auto& entry : std::filesystem::directory_iterator(exeDir + "/plugins"))
    {
        // get the name of the plugin
        std::string pluginName = entry.path().filename().string();
        // load the plugin
        Plugin* pluginInstance = PluginLoader(entry.path().string() + "/lib" + pluginName + ".so").loadPlugin(pluginName);
        pluginMap[pluginName] = pluginInstance->pluginStack;
        std::cout << pluginName << " - " << pluginInstance->pluginStack << std::endl;
    }
}

int runCommand(std::string pluginCalled, int argc, char** argv)
{
    if (pluginCalled == "core" || pluginCalled == "c")
    {
        std::string command = argv[0];
        if (command == "version" || command == "v")
        {
            std::cout << "Version: " << VERSION << std::endl;
        }
        else if (command == "list" || command == "l")
        {
            registerAllPlugins();
        }
        else
        {
            std::cout << "Unknown command" << std::endl;
        }
        return 0;
    }
    // get the executable path with the help of whereami
    std::string exeDir = whereami().substr(0, whereami().find_last_of('/'));

    // get the next plugin called which is in this format: plugin1:plugin2
    std::string nextPlugin = pluginCalled.substr(0, pluginCalled.find(':'));
    pluginCalled = pluginCalled.substr(pluginCalled.find(':') + 1);
    Plugin* plugin = PluginLoader( exeDir + "/plugins/" + nextPlugin + "/lib" + nextPlugin + ".so").loadPlugin(nextPlugin);
    return plugin->runCommand(pluginCalled, argc, argv);
}

