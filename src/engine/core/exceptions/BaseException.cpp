/******************************************************************************
 * @file   BaseException.cpp
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief The base exception that all other exceptions inherit from.
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/core/exceptions/BaseException.h"
#include "engine/core/debugger/Stacktrace.h"

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
