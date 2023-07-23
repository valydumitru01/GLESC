#pragma once

#include <stdexcept>
#include <string>

class BaseException : public std::runtime_error {
protected:
    [[nodiscard]] const char *what() const noexcept override;
    
    explicit BaseException(const std::string &message);
    
    [[nodiscard]] static std::string addr2Line(const std::string &addr, const std::string &exePath) noexcept(false);
    
    std::string stacktrace;
    std::string fullMessage;
};

