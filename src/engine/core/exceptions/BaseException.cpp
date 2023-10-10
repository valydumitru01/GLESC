/******************************************************************************
 * @file   Example.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/core/exceptions/BaseException.h"
#include "engine/core/debugger/Stacktrace.h"
#include <algorithm>
#include <array>

BaseException::BaseException(const std::string &message) :
        runtime_error(message) {
    stacktrace = GLESC::generateStackTrace();
    fullMessage = std::string(std::runtime_error::what() + std::string("\n")) +
                  std::string("stacktrace:\n")
                  + std::string(stacktrace);
}


const char *BaseException::what() const noexcept {
    return fullMessage.c_str();
}
