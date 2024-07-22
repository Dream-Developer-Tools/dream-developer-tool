#ifndef WHEREAMI_H_EXT
#define WHEREAMI_H_EXT

#ifdef __cplusplus
#include <string.h>
#include <whereami_internal.h>

std::string whereami()
{
	int length = wai_getExecutablePath(NULL, 0, NULL);
    char* path = (char*)malloc(length + 1);
    wai_getExecutablePath(path, length, NULL);
    std::string executablePath = path;
    free(path);
	return executablePath;
}
#endif

#endif //WHEREAMI_H
