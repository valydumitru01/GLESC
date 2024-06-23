/******************************************************************************
 * @file   Stacktrace.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief A set of functions for generating and printing stack traces.
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#pragma once

#include <string>

namespace GLESC {
    /**
     * @brief Function to get the address of the function from the address of the function.
     * @param addr - the address of the function.
     * @param exePath - the path to the executable.
     * @return the address of the function.
     */
    [[nodiscard]] std::string addr2Line(const std::string &addr,
                                              const std::string &exePath);
    /**
     * @brief Function to generate a stack trace.
     * @return the stack trace.
     */
    [[nodiscard]] std::string generateStackTrace();
    /**
     * @brief Function to print a stack trace.
     * @return the stack trace.
     */
    [[nodiscard]] std::string printStackTrace();
}