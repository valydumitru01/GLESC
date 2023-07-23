#pragma once

#include "engine/core/exceptions/BaseException.h"

class RenderException : public BaseException {
public:
    explicit RenderException(const std::string &message) : BaseException("Rendering error:"+message) {}
};
