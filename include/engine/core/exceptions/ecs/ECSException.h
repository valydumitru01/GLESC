#pragma once
#include "engine/core/exceptions/EngineException.h"
class ECSException : public EngineException {
public:
    explicit ECSException(const std::string &message) : EngineException("ECS error:"+message) {}
};
