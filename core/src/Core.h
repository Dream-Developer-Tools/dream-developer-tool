#ifndef CORE_H
#define CORE_H

#define VERSION "0.1.0"

#include <Plugin.h>
#include <string>

inline bool guiMode = false;

extern "C" ReturnData runCoreCommand(std::string pluginCalled, uint8_t argc, char** argv, uint8_t gui);



#endif //CORE_H
