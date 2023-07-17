#pragma once

#include "engine/foundation/exceptions/EngineException.h"

class ResourceException : public EngineException {
public:
    explicit ResourceException(const std::string &message) : EngineException(
            "ResourceException" + message) {}

private:
};
