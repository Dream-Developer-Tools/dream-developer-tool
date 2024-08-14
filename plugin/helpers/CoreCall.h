#ifndef CORECALL_H
#define CORECALL_H

struct CoreReturnData
{
    union
    {
        std::string stringData;
        int intData;
        bool boolData;
    };
};

enum CORE_CALL
{
    // Register a child plugin, ARGS: pluginName (string), pluginStack (string) RETURNS: plugin-manager (string)
    REGISTER_CHILD,
    // Plugin confirms it has correctly initialized, ARGS: name (string), pluginStack (string), version (string) RETURNS: void
    REGISTERED,
    // Request the value of a key in your config, AGRS: key (string) [for nested key1:key2:key3], RETURNS: value (string)
    GET_CONFIG,
    // Set the value of a key in your config, ARGS: key (string) [for nested key1:key2:key3], value (string), RETURNS: void
    SET_CONFIG,
    // Log a message, ARGS: message (string), level (LOG_LEVEL), RETURNS: void
    LOG,
    // Make a request to a URL, ARGS: method (string), url (string), body (string), RETURNS: response (string)
    REQUEST,
    // Check if we're in GUI mode, ARGS: void, RETURNS: guiMode (bool)
    GUI_MODE,
};

typedef std::function<CoreReturnData*(CORE_CALL, const std::string&, const std::string&)> CORE_CALLBACK;


#endif //CORECALL_H
