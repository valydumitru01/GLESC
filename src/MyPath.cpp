#include "MyPath.h"
using namespace MyPath;

#ifdef __LINUX__
    std::string MyPath::getExecutablePath() {
    
    return "../bin/game.exe";
    }

    std::string MyPath::getExecutableDir() {
        return "../bin/game.exe";
    }

    std::string MyPath::getImageDir(std::string str){
        return "/home/valentin/Desktop/GameProjectTest/assets/"+str;
    }


#elif __WINDOWS__
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
#else

#endif

#ifdef __LINUX__
    char* MyPath::getCharFromStdString(std::string str){
        return "/home/valentin/Desktop/GameProjectTest/assets/";
    }
#elif __WINDOWS__
    char* MyPath::getCharFromStdString(std::string str){
        return const_cast<char*>(str.c_str());
    }
#endif

