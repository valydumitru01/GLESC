#pragma once

#include "BaseException.h"

class RenderException : public BaseException {
public:
    explicit RenderException(const std::string &message);
};
