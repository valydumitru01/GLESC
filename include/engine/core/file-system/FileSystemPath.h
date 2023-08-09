/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once
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