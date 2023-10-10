/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <stdexcept>
#include <string>

class BaseException : public std::runtime_error {
protected:
    [[nodiscard]] const char *what() const noexcept override;
    
    explicit BaseException(const std::string &message);
    
    
    
    std::string stacktrace;
    std::string fullMessage;
};

