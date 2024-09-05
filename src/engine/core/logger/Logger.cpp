
#include "engine/core/logger/Logger.h"
#include "engine/core/logger/concrete-loggers/FileLogger.h"
#include "engine/core/logger/concrete-loggers/TerminalLogger.h"

using namespace GLESC;

Logger::Logger() : done_(false), worker_(&Logger::processQueue, this) {
#ifndef NLOGGING
    addLogger(std::make_unique<TerminalLogger>());
#endif
    //addLogger(std::make_unique<FileLogger>());
}

Logger::~Logger() {
    done_ = true;
    queue_.push([] {
    }); // Push an empty task to wake up the thread
    worker_.join();
}

Logger& Logger::get() {
    static Logger instance;
    return instance;
}

void Logger::addLogger(std::unique_ptr<ILogger> loggerParam) {
    std::lock_guard<std::mutex> lock(mutex_);
    loggers.push_back(std::move(loggerParam));
}

void Logger::executeOnAllInputs(void (ILogger::*func)(const std::string&), const std::string& text) {
    /*
    queue_.push([this, func, text] {
        std::lock_guard<std::mutex> lock(mutex_);
        for (auto& logger : loggers) {
            (logger.get()->*func)(text);
        }
    });
    */
}

void Logger::log(const std::string& text) {
    executeOnAllInputs(&ILogger::log, text);
}

void Logger::error(const std::string& text) {
    executeOnAllInputs(&ILogger::error, text);
}

void Logger::warning(const std::string& text) {
    executeOnAllInputs(&ILogger::warning, text);
}

void Logger::nonImportantInfo(const std::string& text) {
    executeOnAllInputs(&ILogger::nonImportantInfo, text);
}

void Logger::info(const std::string& text) {
    executeOnAllInputs(&ILogger::info, text);
}

void Logger::infoBlue(const std::string& text) {
    executeOnAllInputs(&ILogger::infoBlue, text);
}

void Logger::infoPurple(const std::string& text) {
    executeOnAllInputs(&ILogger::infoPurple, text);
}

void Logger::importantInfo(const std::string& text) {
    executeOnAllInputs(&ILogger::importantInfo, text);
}

void Logger::importantInfoBlue(const std::string& text) {
    executeOnAllInputs(&ILogger::importantInfoBlue, text);
}

void Logger::importantInfoPurple(const std::string& text) {
    executeOnAllInputs(&ILogger::importantInfoPurple, text);
}

void Logger::importantInfoWhite(const std::string& text) {
    executeOnAllInputs(&ILogger::importantInfoWhite, text);
}

void Logger::success(const std::string& text) {
    executeOnAllInputs(&ILogger::success, text);
}

void Logger::importantSuccess(const std::string& text) {
    executeOnAllInputs(&ILogger::importantSuccess, text);
}

void Logger::processQueue() {
    while (!done_) {
        std::function<void()> task;
        if (queue_.pop(task) && task) {
            task();
        }
    }
}
