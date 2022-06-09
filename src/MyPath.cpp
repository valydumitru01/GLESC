#include "MyPath.h"
using namespace MyPath;



#if defined(_WIN32)

std::string MyPath::getExecutablePath() {
   char rawPathName[MAX_PATH];
   GetModuleFileNameA(NULL, rawPathName, MAX_PATH);
   return std::string(rawPathName);
}

std::string MyPath::getExecutableDir() {
    std::string executablePath = getExecutablePath();
    char* exePath = new char[executablePath.length()];
    strcpy(exePath, executablePath.c_str());
    
    std::string directory = std::string(exePath);
    delete[] exePath;

    return directory;
}

std::string MyPath::getImageDir(std::string str){
    std::string directory = getExecutableDir();
    directory.replace(directory.find("bin\\game.exe"), 12, "assets\\"+str);
    return directory;
}


#endif

#ifdef __linux__

std::string MyPath::getExecutablePath() {
   char rawPathName[PATH_MAX];
   realpath(PROC_SELF_EXE, rawPathName);
   return  std::string(rawPathName);
}

std::string MyPath::getExecutableDir() {
    std::string executablePath = getExecutablePath();
    char *executablePathStr = new char[executablePath.length() + 1];
    strcpy(executablePathStr, executablePath.c_str());
    char* executableDir = dirname(executablePathStr);
    delete [] executablePathStr;
    return std::string(executableDir);
}

std::string MyPath::getImagesDir(str::string str){
    std::string directory = getExecutableDir();
    directory.replace(directory.find("bin/game.exe"), 12, "assets/"+str);
    return directory;
}


#endif

char* MyPath::getCharFromStdString(std::string str){
    return const_cast<char*>(str.c_str());
}


