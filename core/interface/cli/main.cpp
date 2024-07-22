
#include <iostream>
#include <core.h>


int main(int argc, char** argv) {
    argc--;
    argv++;
    if (argc == 0) {
        std::cout << "Usage: " << " <command> [args]" << std::endl;
        std::cout << "For a list of commands, run: " << " help" << std::endl;
        return 1;
    }


    const std::string command = argv[0];
    char** newArgv = argv + 1;



    return runCommand(command, argc - 1, newArgv);
}
