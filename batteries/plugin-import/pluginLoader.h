#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#ifdef _WIN32
#include <windows.h>
#elif defined(__linux__)
#include <dlfcn.h>
#endif
#include <random>
#include <sstream>
#include <string>
#include <iostream>

class PluginLoader
{
    CORE_CALLBACK& callback;
    std::string path;
    [[nodiscard]] void* getFunction(const std::string& name) const;

#ifdef _WIN32
    HMODULE m_handle;
#elif defined(__linux__)
    void* m_handle;
#endif
public:
    explicit PluginLoader(const std::string& path, CORE_CALLBACK& callback);
    ~PluginLoader();

    [[nodiscard]] int loadPlugin(const std::string& pluginStack, const std::string& uuid) const;
    ReturnData runCommand(const std::string& pluginCalled, int argc, char** argv) const;
};

inline PluginLoader::PluginLoader(const std::string& path, CORE_CALLBACK& callback) : callback(callback), path(path)
{

#ifdef _WIN32
    m_handle = LoadLibrary(path.c_str());
    if (m_handle == NULL)
    {
        std::cerr << "Failed to load library: " << path << std::endl;
    }
#elif defined(__linux__)
    m_handle = dlopen(path.c_str(), RTLD_LAZY);
    if (m_handle == nullptr)
    {
        std::cerr << "Failed to load library: " << dlerror() << std::endl;
    }
#endif
}

inline PluginLoader::~PluginLoader()
{
#ifdef _WIN32
    FreeLibrary(m_handle);
#elif defined(__linux__)
    dlclose(m_handle);
#endif
}

inline void* PluginLoader::getFunction(const std::string& name) const
{
#ifdef _WIN32
    return GetProcAddress(m_handle, name.c_str());
#elif defined(__linux__)
    return dlsym(m_handle, name.c_str());
#endif
}

inline int PluginLoader::loadPlugin(const std::string& pluginStack, const std::string& uuid) const
{
    const auto pluginFunction = (int (*)(CORE_CALLBACK& callbackPar, const std::string& uuidPar, std::string pluginStackPar))getFunction("createPlugin");
    if (pluginFunction == nullptr)
    {
        std::cerr << "Failed to load plugin: " << path.substr(path.find_last_of('/'), path.length()) << std::endl;
        return 1;
    }
    return pluginFunction(callback, uuid, pluginStack);
}

inline ReturnData PluginLoader::runCommand(const std::string& pluginCalled, int argc, char** argv) const
{
    const auto runCommandFunction = (ReturnData (*)(const std::string& pluginCalledPar, int argcPar, char** argvPar))getFunction("runCommand");
    if (runCommandFunction == nullptr)
    {
        std::cerr << "Failed to load plugin: " << path.substr(path.find_last_of('/'), path.length()) << std::endl;
        return ReturnData{"UC", UNKNOWN_COMMAND};
    }
    return runCommandFunction(pluginCalled, argc, argv);
}

#endif //PLUGINLOADER_H
