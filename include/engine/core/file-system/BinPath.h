/******************************************************************************
 * @file   BinPath.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once
#include <string>

class BinPath {
public:
    static std::string getExecutablePath();
    static std::string getExecutableDirectory();
};
