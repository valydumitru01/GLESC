
#include "engine/core/exceptions/BaseException.h"
#include "engine/core/debugger/Stacktrace.h"

BaseException::BaseException(const std::string &message) :
        runtime_error(message) {
    stacktrace = GLESC::generateStackTrace();
    fullMessage = std::string(std::runtime_error::what() + std::string("\n")) +
                  std::string("stacktrace:\n")
                  + std::string(stacktrace);
}


const char *BaseException::what() const noexcept {
    return fullMessage.c_str();
}
