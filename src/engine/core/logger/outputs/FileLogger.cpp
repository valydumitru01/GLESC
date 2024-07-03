/******************************************************************************
 * @file   FileLogger.cpp
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include <fstream>

#include "engine/core/logger/concrete-loggers/FileLogger.h"

#include "engine/core/asserts/Asserts.h"

FileLogger::FileLogger() {
    clearFileContent();
    // Open the log file in append mode
    logFile.open(LOG_FILE, std::ios::app);
    D_ASSERT_TRUE(logFile.is_open(), "Log file couldn't be opened.");
}

void FileLogger::clearFileContent() {
    // Open the file in truncation mode to clear its contents
    logFile.open(LOG_FILE, std::ios::trunc);
    logFile.close();
}


FileLogger::~FileLogger() {
    logFile.close();
}

void FileLogger::log(const std::string& text) {
    logFile << "[LOG] " << text << std::endl;
}

void FileLogger::error(const std::string& text) {
    logFile << "[ERROR] " << text << std::endl;
}

void FileLogger::warning(const std::string& text) {
    logFile << "[WARNING] " << text << std::endl;
}

void FileLogger::nonImportantInfo(const std::string& text) {
    logFile << "[NON IMPORTANT INFO] " << text << std::endl;
}

void FileLogger::info(const std::string& text) {
    logFile << "[INFO] " << text << std::endl;
}

void FileLogger::infoBlue(const std::string& text) {
    logFile << "[INFO Blue] " << text << std::endl;
}

void FileLogger::infoPurple(const std::string& text) {
    logFile << "[INFO Purple] " << text << std::endl;
}

void FileLogger::importantInfo(const std::string& text) {
    logFile << "[IMPORTANT INFO] " << text << std::endl;
}

void FileLogger::importantInfoBlue(const std::string& text) {
    logFile << "[IMPORTANT INFO Blue] " << text << std::endl;
}

void FileLogger::importantInfoPurple(const std::string& text) {
    logFile << "[IMPORTANT INFO Purple] " << text << std::endl;
}

void FileLogger::importantInfoWhite(const std::string& text) {
    logFile << "[IMPORTANT INFO White] " << text << std::endl;
}

void FileLogger::importantSuccess(const std::string& text) {
    logFile << "[IMPORTANT SUCCESS] " << text << std::endl;
}

void FileLogger::success(const std::string& text) {
    logFile << "[SUCCESS] " << text << std::endl;
}
