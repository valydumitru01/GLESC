/******************************************************************************
 * @file   Example.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#pragma once

#include <string>

namespace GLESC {
    [[nodiscard]] std::string addr2Line(const std::string &addr,
                                              const std::string &exePath);
    
    [[nodiscard]] std::string generateStackTrace();
}