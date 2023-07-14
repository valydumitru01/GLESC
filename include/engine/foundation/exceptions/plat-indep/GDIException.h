#pragma once

#include "engine/foundation/exceptions/EngineException.h"

class GDIException : public EngineException {
public:
    explicit GDIException(const std::string &message) : EngineException("GDI error:"+message) {}
};
