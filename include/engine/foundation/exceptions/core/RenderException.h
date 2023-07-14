#pragma once

#include "engine/foundation/exceptions/BaseException.h"

class RenderException : public BaseException {
public:
    explicit RenderException(const std::string &message) : BaseException("Rendering error:"+message) {}
};
