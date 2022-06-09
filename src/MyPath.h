#ifdef __LINUX__
    #include <limits.h>
    #include <libgen.h>
    #include <unistd.h>

    #if defined(__sun)
        #define PROC_SELF_EXE "/proc/self/path/a.out"
    #else
        #define PROC_SELF_EXE "/proc/self/exe"
    #endif

#elif __WINDOWS__
    #include <windows.h>
    #include <Shlwapi.h>
    #include <io.h> 

    #define access _access_s
#endif




#include <string>

namespace MyPath {
  std::string getExecutablePath();
  std::string getExecutableDir();
  std::string getImageDir(std::string str);
  char* getCharFromStdString(std::string str);
}