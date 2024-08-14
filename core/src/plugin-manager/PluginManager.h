#ifndef UUIDMANAGER_H
#define UUIDMANAGER_H

#include <string>
#include <map>

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

struct SPlugin
{
    std::string name;
    std::string pluginStack;
    std::string version;
    std::string shortName;
};

inline std::map<std::string, std::string> uuids = {}; // uuid, shortName

inline std::map<std::string, SPlugin> plugins = {}; // uuid, plugin

inline std::string registerPluginUUID(const std::string& name)
{
    const std::string uuid = generateUUID();
    uuids[uuid] = name;
    return uuid;
}

inline bool isPluginRegistered(const std::string& uuid)
{
    return uuids.find(uuid) != uuids.end();
}

inline bool finalizePlugin(const std::string& uuid, const std::string& name, const std::string& pluginStack, const std::string& version)
{
    if (!isPluginRegistered(uuid))
    {
        return false;
    }
    plugins[uuid] = SPlugin{name, pluginStack, version, uuids[uuid]};
    return true;
}

inline bool isPluginFinalized(const std::string& uuid)
{
    return plugins.find(uuid) != plugins.end();
}

inline void finalizePlugins()
{
    const std::map<std::string, std::string> uuidsCopy = uuids;
    for (const auto& [uuid, shortName] : uuidsCopy)
    {
        if (!isPluginFinalized(uuid))
        {
            uuids.erase(uuid);
        }
    }
}

inline std::vector<SPlugin> getPlugins()
{
    std::vector<SPlugin> ret;
    for (const auto& [uuid, plugin] : plugins)
    {
        ret.push_back(plugin);
    }
    return ret;
}

#endif //UUIDMANAGER_H
