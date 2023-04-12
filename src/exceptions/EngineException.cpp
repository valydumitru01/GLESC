#include "exceptions/EngineException.h"

EngineException::EngineException(const string &message)
        : BaseException(message) {}

const char *EngineException::what() const noexcept {
    Console::error(std::string(std::runtime_error::what()));
    return std::runtime_error::what();
}

