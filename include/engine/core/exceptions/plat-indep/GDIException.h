#pragma once

#include "engine/core/exceptions/EngineException.h"

class GDIException : public EngineException {
public:
    explicit GDIException(const std::string &message) : EngineException("GDI error:"+message) {}
};
