#pragma once

#include "engine/foundation/exceptions/EngineException.h"

class OpenException : public EngineException{
public:
    explicit OpenException(const std::string &message) : EngineException("Open error:"+message) {}
private:
};
