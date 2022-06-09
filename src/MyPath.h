#ifdef __WINDOWS__
    #include <windows.h>
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