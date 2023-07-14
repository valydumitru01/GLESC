#pragma once

#include "BaseException.h"

class EngineException : public BaseException {
public:
    explicit EngineException(const std::string &message) : BaseException(message) {}
};
