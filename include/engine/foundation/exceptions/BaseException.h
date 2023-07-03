#pragma once

#include <stdexcept>
#include <boost/stacktrace.hpp>
#include <sstream>
#include "engine/core/debug-profile/Console.h"

class BaseException : public std::runtime_error {
public:
    explicit BaseException(const std::string &message);
    [[nodiscard]] const char *what() const noexcept override;
    static std::string addr2Line(const std::string& addr, const std::string& exePath);
protected:
    std::string stacktrace;
    std::string fullMessage;
};

