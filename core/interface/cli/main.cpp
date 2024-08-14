
#include <iostream>
#include <Core.h>

// ARGV[0] is the command name, ARGV[1] is the plugin name, and anything past that are the arguments for the plugin
int main(int argc, char** argv) {
    argc--;
    if (argc == 0) {
        std::cout << "Usage: " << " <command> [plugin-name] [args]" << std::endl;
        std::cout << "For a list of commands, run: " << " help" << std::endl;
        return 1;
    }

    return runCoreCommand(argv[1], argc - 1, argv + 2, false).status;
}
