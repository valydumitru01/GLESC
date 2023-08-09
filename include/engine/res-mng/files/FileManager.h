/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once
#include <fstream>
#include <sstream>
class FileManager {
public:
    static std::string readFile(const std::string &path);
    static void writeFile(const std::string &path, const std::string &content);
private:
};
