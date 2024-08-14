#ifndef CORE_H
#define CORE_H

#define VERSION "0.1.0"

#include <Plugin.h>
#include <string>

inline bool guiMode = false;

ReturnData runCoreCommand(std::string pluginCalled, int argc, char** argv, bool gui);



#endif //CORE_H
