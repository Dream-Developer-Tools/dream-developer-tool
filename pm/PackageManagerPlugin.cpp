#include "PackageManagerPlugin.h"
#include <memory>
#include <iostream>
#include <utility>

int PackageManagerPlugin::runCommand(const std::string& pluginCalled, int argc, char **argv) {
    if (pluginCalled == "pm")
    {
        std::string command = argv[0];
        if (command == "version" || command == "v")
        {
            std::cout << "Version: " << "AAAAAA" << std::endl;
            return 0;
        }
        else
        {
            std::cout << "Unknown command" << std::endl;
            return 1;
        }
    }



    return 0;
}

extern "C" Plugin* createPlugin(const std::function<void*()>& callback, const std::string& uuid, std::string pluginStack) {
    return new PackageManagerPlugin(callback, uuid, std::move(pluginStack));
}