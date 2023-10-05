/******************************************************************************
 * @file   Example.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/core/file-system/FileSystemPath.h"

using namespace MyPath;

#ifdef __LINUX__
std::string MyPath::getExecutablePath() {

return "../bin/game.exe";
}

std::string MyPath::getExecutableDir() {
    return "../bin/game.exe";
}

char* MyPath::getImageDir(std::string str){
    std::string directory = "/home/valentin/Desktop/GameProjectTest/assets/"+str;
    char *cstr = new char[directory.length() + 1];
    strcpy(cstr, directory.c_str());
    return cstr;
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

char* MyPath::getImageDir(std::string str){
    std::string directory = getExecutableDir();
    directory.replace(directory.find("bin\\game.exe"), 12, "assets\\"+str);
    return const_cast<char*>(directory.c_str());;
}
#else

#endif

