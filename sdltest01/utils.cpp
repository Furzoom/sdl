#include "utils.h"
#include <iostream>

/*
* Get the resource path for resources located in res/subDir
* It's assumed the project directory is structured like:
* bin/
*   the executable
* res/
*   sub/
*   xx.xx
*
* Paths returned will be res/sub/
*/
std::string getResourcePath(const std::string &subDir)
{
#ifdef _WIN32
    const char PATH_SEP = '\\';
#else
    const char PATH_SEP = '/';
#endif // _WIN_32
    static std::string baseRes;
    if (baseRes.empty())
    {
        char *basePath = SDL_GetBasePath();
        if (basePath)
        {
            baseRes = basePath;
            SDL_free(basePath);
        }
        else
        {
            std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
            return "";
        }
        size_t pos = baseRes.rfind("bin");
        baseRes = baseRes.substr(0, pos) + "res" + PATH_SEP;
    }
    return subDir.empty() ? baseRes : baseRes + subDir + PATH_SEP;
}

