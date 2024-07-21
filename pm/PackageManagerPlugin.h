#ifndef DDT_PACKAGEMANAGERPLUGIN_H
#define DDT_PACKAGEMANAGERPLUGIN_H

#include <plugin.h>


class PackageManagerPlugin : public Plugin
{
public:
    PackageManagerPlugin(const std::function<void*()>& callback, const std::string& uuid, std::string pluginStack) : Plugin(callback, uuid, pluginStack) {}
    int runCommand(const std::string& pluginCalled, int argc, char** argv) final;
    void registerPlugin() final {}
    std::string name = "Package Manager";
};


#endif
