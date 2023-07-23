#pragma once

#include "engine/core/exceptions/EngineException.h"

class OpenException : public EngineException {
public:
    explicit OpenException(const std::string &message) : EngineException(message) {}
private:
};
