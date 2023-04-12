#pragma once
#include "exceptions/BaseException.h"


class EngineException  :public BaseException{
public:
    explicit EngineException(const std::string &message);
    [[nodiscard]] const char *what() const noexcept override;
};
