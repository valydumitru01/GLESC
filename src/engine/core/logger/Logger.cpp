/******************************************************************************
 * @file   Example.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/core/logger/Logger.h"

//Include loggers
#include "engine/core/logger/concrete-loggers/TerminalLogger.h"
#include "engine/core/logger/concrete-loggers/FileLogger.h"
using namespace GLESC;
Logger::Logger() {
#ifndef NLOGGING
    addLogger(std::make_unique<TerminalLogger>());
#endif
    addLogger(std::make_unique<FileLogger>());
}

Logger&Logger::get() {
    static Logger logger = Logger();
    return logger;
}

void Logger::addLogger(std::unique_ptr<ILogger> loggerParam) {
    loggers.push_back(std::move(loggerParam));
}

void Logger::executeOnAllInputs(void (ILogger::*func)(const std::string&), const std::string &text) {
    for (auto& input : loggers) {
        (input.get()->*func)(text);
    }
}

void Logger::log(const std::string &text){
    executeOnAllInputs(&ILogger::log, text);
}

void Logger::error(const std::string &text){
    executeOnAllInputs(&ILogger::error, text);
}

void Logger::warning(const std::string &text){
    executeOnAllInputs(&ILogger::warning, text);
}

void Logger::nonImportantInfo(const std::string &text){
    executeOnAllInputs(&ILogger::nonImportantInfo, text);
}

void Logger::info(const std::string &text){
    executeOnAllInputs(&ILogger::info, text);
}

void Logger::infoBlue(const std::string &text){
    executeOnAllInputs(&ILogger::infoBlue, text);
}

void Logger::infoPurple(const std::string &text){
    executeOnAllInputs(&ILogger::infoPurple, text);
}

void Logger::importantInfo(const std::string &text){
    executeOnAllInputs(&ILogger::importantInfo, text);
}

void Logger::importantInfoBlue(const std::string &text){
    executeOnAllInputs(&ILogger::importantInfoBlue, text);
}

void Logger::importantInfoPurple(const std::string &text){
    executeOnAllInputs(&ILogger::importantInfoPurple, text);
}

void Logger::importantInfoWhite(const std::string &text){
    executeOnAllInputs(&ILogger::importantInfoWhite, text);
}

void Logger::success(const std::string &text){
    executeOnAllInputs(&ILogger::success, text);
}

void Logger::importantSuccess(const std::string &text) {
    executeOnAllInputs(&ILogger::importantSuccess, text);
}
