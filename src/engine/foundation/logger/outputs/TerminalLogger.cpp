#include "color.hpp"
#include "engine/foundation/logger/concrete-loggers/TerminalLogger.h"

TerminalLogger::TerminalLogger() = default;

void TerminalLogger::log(const std::string &text){
    std::cout << text << std::endl;
}

void TerminalLogger::error(const std::string &text){
    std::cout << dye::black_on_red(text) << std::endl;
}

void TerminalLogger::warning(const std::string &text){
    std::cout << dye::black_on_yellow(text) << std::endl;
}

void TerminalLogger::info(const std::string &text){
    std::cout << dye::white(text) << std::endl;
}

void TerminalLogger::infoBlue(const std::string &text){
    std::cout << dye::light_blue(text) << std::endl;
}

void TerminalLogger::infoPurple(const std::string &text){
    std::cout << dye::light_purple(text) << std::endl;
}

void TerminalLogger::importantInfo(const std::string &text) {
    std::cout << dye::black_on_white(text) << std::endl;
}

void TerminalLogger::importantInfoBlue(const std::string &text) {
    std::cout << dye::black_on_blue(text) << std::endl;
}

void TerminalLogger::importantInfoPurple(const std::string &text) {
    std::cout << dye::black_on_purple(text) << std::endl;
}

void TerminalLogger::success(const std::string &text) {
    std::cout << dye::black_on_green(text) << std::endl;
}
