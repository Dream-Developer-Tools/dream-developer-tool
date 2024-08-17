
#include <iostream>
#include <Core.h>

#ifdef _WIN32
#include <windows.h>
#elif defined(__linux__)
#include <dlfcn.h>
#include "../../../batteries/whereami/include/whereami.h"

#endif

#ifdef _WIN32
HMODULE m_handle;
#elif defined(__linux__)
void* m_handle;
#endif

void* getFunction(const std::string& name)
{
#ifdef _WIN32
    return GetProcAddress(m_handle, name.c_str());
#elif defined(__linux__)
    return dlsym(m_handle, name.c_str());
#endif
}

// ARGV[0] is the command name, ARGV[1] is the plugin name, and anything past that are the arguments for the plugin
int main(int argc, char** argv) {
    argc--;
    if (argc == 0) {
        std::cout << "Usage: " << " <command> [plugin-name] [args]" << std::endl;
        std::cout << "For a list of commands, run: " << " help" << std::endl;
        return 1;
    }

    // find out in what directory the executable is located
    std::string exeDir = whereami().substr(0, whereami().find_last_of('/'));
    std::string path = exeDir + "/libddt-core.so";

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
    auto run = (ReturnData (*)(std::string plugin, int argc, char** argv, bool guiMode))getFunction("runCoreCommand");



    return run(argv[1], argc - 1, argv + 2, false).status;
}
