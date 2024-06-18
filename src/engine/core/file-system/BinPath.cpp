/******************************************************************************
 * @file   BinPath.cpp
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/core/file-system/BinPath.h"
#ifdef __WINDOWS__
#include <windows.h>
#elif __MAC__
#include <mach-o/dyld.h>
#elif __LINUX__
#include <unistd.h>
#endif
#include <stdexcept>

std::string BinPath::getExecutablePath() {
    char buffer[1024];
#ifdef _WIN32
    DWORD size = GetModuleFileName(nullptr, buffer, sizeof(buffer));
    if (size == 0 || size == sizeof(buffer)) {
        throw std::runtime_error("Unable to get executable path on Windows.");
    }
#elif __APPLE__
     uint32_t size = sizeof(buffer);
     if (_NSGetExecutablePath(buffer, &size) != 0) {
      throw std::runtime_error("Unable to get executable path on macOS.");
     }
#elif __linux__
     ssize_t size = readlink("/proc/self/exe", buffer, sizeof(buffer));
     if (size == -1 || size == sizeof(buffer)) {
      throw std::runtime_error("Unable to get executable path on Linux.");
     }
#else
    throw std::runtime_error("Unsupported platform.");
#endif

    return {buffer, size};
}

std::string BinPath::getExecutableDirectory() {
    std::string execPath = getExecutablePath();
    size_t lastSlash = execPath.find_last_of("/\\");
    return execPath.substr(0, lastSlash);
}
