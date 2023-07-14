#pragma once
#include <stdexcept>

class BaseException : public std::runtime_error {
protected:
    [[nodiscard]] const char *what() const noexcept override;
    explicit BaseException(const std::string &message);
    static std::string addr2Line(const std::string& addr, const std::string& exePath) noexcept(false);
    std::string stacktrace;
    std::string fullMessage;
};

