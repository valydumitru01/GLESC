/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/core/exceptions/BaseException.h"
#include <iostream>
#include <boost/stacktrace.hpp>
#include <sstream>
#include <algorithm>
BaseException::BaseException(const std::string &message) : runtime_error(message){
    const auto exePath = PROJECT_BINARY_DIR + std::string("/") + std::string(PROJECT_NAME)
            + std::string(".exe");
    const auto st = boost::stacktrace::stacktrace();
    
    for (auto i : st) {
        std::stringstream ss;
        ss << std::hex << i.address();
        std::string line = addr2Line(ss.str(), exePath);
        if (line.find("??") == std::string::npos) {
            stacktrace.append(line);
        }
        else{
            stacktrace.append("Function not found: " + ss.str() + "\n");
        }
    }
    fullMessage = std::string (std::runtime_error::what() + std::string("\n")) + std::string("stacktrace:\n")
            +std::string(stacktrace);
}


std::string BaseException::addr2Line(const std::string &addr, const std::string &exePath) {
    std::ostringstream command;
    command << "addr2line -f -C -e " << exePath << " " << addr;
    
    std::array <char, 128> buffer{};
    std::string result;
    std::unique_ptr <FILE, decltype(&pclose)> pipe(popen(command.str().c_str(), "r"), pclose);
    if (!pipe) {
        std::cerr << "popen() failed!" << std::endl;
        return {};
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

const char *BaseException::what() const noexcept {
    return fullMessage.c_str();
}
