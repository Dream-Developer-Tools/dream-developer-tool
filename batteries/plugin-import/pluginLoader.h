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
    std::string path;
    [[nodiscard]] void* getFunction(const std::string& name) const;

#ifdef _WIN32
    HMODULE m_handle;
#elif defined(__linux__)
    void* m_handle;
#endif
public:
    explicit PluginLoader(const std::string& path);
    ~PluginLoader();

    [[nodiscard]] Plugin* loadPlugin(const std::string& pluginName) const;
};

inline PluginLoader::PluginLoader(const std::string& path) : path(path)
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

static std::string generateUUID()
{
    static std::random_device              rd;
    static std::mt19937                    gen(rd());
    static std::uniform_int_distribution<> dis(0, 15);
    static std::uniform_int_distribution<> dis2(8, 11);

    std::stringstream ss;
    int i;
    ss << std::hex;
    for (i = 0; i < 8; i++) {
        ss << dis(gen);
    }
    ss << "-";
    for (i = 0; i < 4; i++) {
        ss << dis(gen);
    }
    ss << "-4";
    for (i = 0; i < 3; i++) {
        ss << dis(gen);
    }
    ss << "-";
    ss << dis2(gen);
    for (i = 0; i < 3; i++) {
        ss << dis(gen);
    }
    ss << "-";
    for (i = 0; i < 12; i++) {
        ss << dis(gen);
    };
    return ss.str();
}

inline Plugin* PluginLoader::loadPlugin(const std::string& pluginName) const
{
    // ReSharper disable once CppCStyleCast
    const auto pluginFunction = (Plugin* (*)(const std::function<void*()>& callback, const std::string& uuid, std::string pluginStack))getFunction("createPlugin");
    if (pluginFunction == nullptr)
    {
        std::cerr << "Failed to load plugin: " << path.substr(path.find_last_of('/'), path.length()) << std::endl;
        return nullptr;
    }
    return pluginFunction(std::function<void*()>(nullptr), generateUUID(), pluginName);
}

#endif //PLUGINLOADER_H
