#ifndef CORECALLS_H
#define CORECALLS_H

#include <Plugin.h>

inline void createLog(LOG_LEVEL level, const std::string& msg) {
    switch (level) {
        case INFO:
            // the special characters are for coloring the output, in this case blue
            std::cout << "\033[34m\033[1m[INFO] " << msg << "\033[0m\033[34m" << std::endl;
            break;
        case WARN:
            // the special characters are for coloring the output, in this case yellow
            std::cout << "\033[33m\033[1m[WARN] " << msg << "\033[0m\033[33m" << std::endl;
            break;
        case ERROR:
            // the special characters are for coloring the output, in this case red
            std::cerr << "\033[31m\033[1m[ERROR] " << msg << "\033[0m\033[31m" << std::endl;
            break;
    }
    // call flush to make sure the output is printed
    std::cout.flush();
    std::cerr.flush();
}


#endif //CORECALLS_H
