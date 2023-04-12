#pragma once

#include "exceptions/BaseException.h"

class RenderException : public BaseException {
public:
    explicit RenderException(const std::string &message);
    
    [[nodiscard]] const char *what() const noexcept override;
};
