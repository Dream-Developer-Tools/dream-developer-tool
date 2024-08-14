#ifndef LOGHELP_H
#define LOGHELP_H

#include <map>
#include <string>

enum LOG_LEVEL
{
    INFO,
    WARN,
    ERROR,
};

inline std::map<LOG_LEVEL, std::string> logLevelStrings = {
    {INFO, "I"},
    {WARN, "W"},
    {ERROR, "E"},
};

#endif //LOGHELP_H
