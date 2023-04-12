#include "exceptions/RenderException.h"

RenderException::RenderException(const string &message)
        : BaseException(message) {}

const char *RenderException::what() const noexcept {
    Console::error(std::string(std::runtime_error::what()));
    return std::runtime_error::what();
}

