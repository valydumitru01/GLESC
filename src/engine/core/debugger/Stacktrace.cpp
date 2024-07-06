
#include "engine/core/debugger/Stacktrace.h"
#include <sstream>
#include <array>
#include <iostream>
#include <boost/stacktrace.hpp>
#include <memory>


[[nodiscard]] std::string GLESC::addr2Line(const std::string &addr,
                                           const std::string &exePath) {
    std::ostringstream command;
    command << "addr2line -f -C -e " << exePath << " " << addr;
    std::array<char, 128> buffer{};
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)>
            pipe(popen(command.str().c_str(), "r"), pclose);
    if (!pipe) {
        std::cerr << "popen() failed!" << std::endl;
        return {};
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}


[[nodiscard]] std::string GLESC::generateStackTrace() {
    const auto exePath = PROJECT_BINARY_DIR + std::string("/") +
                         std::string(PROJECT_NAME) + std::string(".exe");
    std::string stacktrace;
    const auto st = boost::stacktrace::stacktrace();
    
    for (const auto &frame : st) {
        std::stringstream ss;
        ss << std::hex << frame.address();
        std::string line = GLESC::addr2Line(ss.str(), exePath);
        if (line.find("??") == std::string::npos) {
            stacktrace.append(line);
        } else {
            stacktrace.append("Function not found: " + ss.str() + "\n");
        }
    }
    
    return stacktrace;
}

