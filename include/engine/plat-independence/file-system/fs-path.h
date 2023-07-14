#ifdef __WINDOWS__
#include <windows.h>
#include <io.h>
#define access _access_s
#endif

#ifdef __LINUX__
#include <cstring>
#endif

#include <string>

namespace MyPath {
    std::string getExecutablePath();

    std::string getExecutableDir();

    char *getImageDir(std::string str);
}