/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/core/logger/ILogger.h"
#include "engine/core/logger/concrete-loggers/FileLogger.h"

#include <fstream>

FileLogger::FileLogger() {
    // Open the log file in append mode
    logFile.open("log.txt", std::ios::app);
}


FileLogger::~FileLogger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}
void FileLogger::log(const std::string &text) {
    logFile << "[LOG] " << text << std::endl;
}

void FileLogger::error(const std::string &text) {
    logFile << "[ERROR] " << text << std::endl;
}

void FileLogger::warning(const std::string &text) {
    logFile << "[WARNING] " << text << std::endl;
}

void FileLogger::info(const std::string &text) {
    logFile << "[INFO] " << text << std::endl;
}

void FileLogger::infoBlue(const std::string &text) {
    logFile << "[INFO Blue] " << text << std::endl;
}

void FileLogger::infoPurple(const std::string &text) {
    logFile << "[INFO Purple] " << text << std::endl;
}

void FileLogger::importantInfo(const std::string &text) {
    logFile << "[IMPORTANT INFO] " << text << std::endl;
}

void FileLogger::importantInfoBlue(const std::string &text) {
    logFile << "[IMPORTANT INFO Blue] " << text << std::endl;
}

void FileLogger::importantInfoPurple(const std::string &text) {
    logFile << "[IMPORTANT INFO Purple] " << text << std::endl;
}

void FileLogger::success(const std::string &text) {
    logFile << "[SUCCESS] " << text << std::endl;
}
