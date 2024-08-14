#include "Core.h"

#include <iostream>
#include <map>
#include <ostream>
#include <Plugin.h>
#include <whereami.h>
#include <pluginLoader.h>
#include <filesystem>
#include "./plugin-manager/PluginManager.h"
#include "./calls/CoreCalls.h"
#include "Helpers.h"
#include "calls/Requests.h"

CoreReturnData* coreCallback(CORE_CALL coreCall, const std::string& uuid, std::string args)
{
    if (!isPluginRegistered(uuid))
    {
        return nullptr;
    }
    // split args into a list of arguments
    std::vector<std::string> argList = splitString(args, " ");
    if (coreCall == REGISTER_CHILD)
    {
        if (argList.size() != 1)
        {
            return nullptr;
        }
        return new CoreReturnData{registerPluginUUID(argList[0])};
    }
    if (coreCall == REGISTERED) {
        if (argList.size() < 3)
        {
            return nullptr;
        }
        // the name of the plugin is first and starts with a ' and ends with a ' so we know where it starts and ends
        const std::string name = args.substr(args.find('\'') + 1, args.find_last_of('\'') - 1);
        // remove the plugin name from the args
        args = args.substr(args.find_last_of('\'') + 1);
        finalizePlugin(uuid, name, args.substr(0, args.find_last_of(' ')), args.substr(args.find_last_of(' ') + 1));
        return nullptr;
    }
    if (coreCall == LOG)
    {
        if (argList.size() < 2)
        {
            return nullptr;
        }
        // find the key that contains argList[0] which is the log level
        LOG_LEVEL level = INFO;
        for (const auto& [key, value] : logLevelStrings)
        {
            if (value == argList[0])
            {
                level = key;
                break;
            }
        }
        // the rest of the args is the message make that into a string
        createLog(level, args.substr(args.find(' ') + 1));
        return nullptr;
    }
    if (coreCall == REQUEST)
    {
        if (argList.size() < 2)
        {
            return nullptr;
        }
        createLog(INFO, "Requesting: " + argList[1]);
        if (argList[0] == "GET")
        {
            const std::string val = Requests::get(argList[1]).text;
            return new CoreReturnData{val};
        }
    }
    if (coreCall == GUI_MODE)
    {
        auto* ret = new CoreReturnData{""};
        ret->boolData = guiMode;
        return ret;
    }
    return nullptr;
}

std::vector<SPlugin> registerAllPlugins()
{
    // loop through all the plugins in the plugins directory
    // get the executable path with the help of whereami
    std::string exeDir = whereami().substr(0, whereami().find_last_of('/'));
    // loop through all the dirs in the plugins directory
    for (const auto& entry : std::filesystem::__cxx11::directory_iterator(exeDir + "/plugins"))
    {
        // get the name of the plugin
        std::string pluginName = entry.path().filename().string();

        // Create the passable object of the callback function to core
        CORE_CALLBACK callback = std::bind(coreCallback, std::placeholders::_1, std::placeholders::_2,
                                           std::placeholders::_3);

        // load the plugin
        auto* loader = new PluginLoader(entry.path().string() + "/lib" + pluginName + ".so", callback);
        int re = loader->loadPlugin(pluginName, registerPluginUUID(pluginName));
        if (re != 0)
        {
            createLog(ERROR, "Failed to load plugin: " + pluginName);
        }
    }
    finalizePlugins();
    return getPlugins();
}




ReturnData runCoreCommand(std::string pluginCalled, int argc, char** argv, bool gui)
{
    guiMode = gui;
    if (pluginCalled == "core" || pluginCalled == "c")
    {
        std::string command = argv[0];
        if (command == "version" || command == "v")
        {
            std::cout << "Version: " << VERSION << std::endl;
        }
        else if (command == "list" || command == "l")
        {
            std::vector<SPlugin> plugins = registerAllPlugins();
            std::string ret = "";
            if (!guiMode)
            {
                createLog(INFO, "Plugins");
            }
            for (const auto& plugin : plugins)
            {
                if (!guiMode)
                {
                    createLog(INFO, plugin.name + " - " + plugin.pluginStack + " - " + plugin.version);
                }
                ret += plugin.name + "|" + plugin.pluginStack + "|" + plugin.version + ",";
            }
            if (!guiMode)
            {
                createLog(INFO, "End of plugins");
            }
            return ReturnData{ret, SUCCESS};
        }
        else
        {
            return ReturnData{"UC", UNKNOWN_COMMAND};
        }
        return ReturnData{"", SUCCESS};
    }
    // get the executable path with the help of whereami
    std::string exeDir = whereami().substr(0, whereami().find_last_of('/'));

    // get the next plugin called which is in this format: plugin1:plugin2
    std::string nextPlugin = pluginCalled.substr(0, pluginCalled.find(':'));
    pluginCalled = pluginCalled.substr(pluginCalled.find(':') + 1);

    // Create the passable object of the callback function to core
    CORE_CALLBACK callback = std::bind(coreCallback, std::placeholders::_1, std::placeholders::_2,
                                       std::placeholders::_3);

    // load the plugin
    auto* pluginLoader = new PluginLoader(exeDir + "/plugins/" + nextPlugin + "/lib" + nextPlugin + ".so", callback);
    if (pluginLoader->loadPlugin(nextPlugin,  registerPluginUUID(nextPlugin)) != 0)
    {
        return ReturnData{"", UNKNOWN_COMMAND};
    }

    // run the command
    try
    {
        return pluginLoader->runCommand(pluginCalled, argc, argv);
    } catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return ReturnData{"", UNKNOWN_COMMAND};
    }

}
