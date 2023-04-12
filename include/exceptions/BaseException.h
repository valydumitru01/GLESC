#pragma once

#include <stdexcept>
#include "util/Console.h"

class BaseException : public std::runtime_error {
public:
    explicit BaseException(const std::string &message);
    
private:
};
