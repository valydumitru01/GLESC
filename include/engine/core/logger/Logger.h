/**************************************************************************************************
 * @file   Logger.h
 * @author Valentin Dumitru
 * @date   2024-04-17
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

#pragma once

#include <string>
#include <memory>
#include <vector>
#include <functional>
#include <atomic>
#include <thread>
#include <mutex>
#include "ILogger.h"
#include "ConcurrentQueue.h"

namespace GLESC {
    class Logger : public ILogger {
    public:
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;

        static Logger& get();

        void addLogger(std::unique_ptr<ILogger> loggerParam);

        void executeOnAllInputs(void (ILogger::*func)(const std::string&), const std::string& text);

        void log(const std::string& text) override;
        void error(const std::string& text) override;
        void warning(const std::string& text) override;
        void nonImportantInfo(const std::string& text) override;
        void info(const std::string& text) override;
        void infoBlue(const std::string& text) override;
        void infoPurple(const std::string& text) override;
        void importantInfo(const std::string& text) override;
        void importantInfoBlue(const std::string& text) override;
        void importantInfoPurple(const std::string& text) override;
        void importantInfoWhite(const std::string& text) override;
        void success(const std::string& text) override;
        void importantSuccess(const std::string& text) override;

    private:
        Logger();
        ~Logger();

        void processQueue();

        std::vector<std::unique_ptr<ILogger>> loggers;
        ConcurrentQueue<std::function<void()>> queue_;
        std::thread worker_;
        std::atomic<bool> done_;
        std::mutex mutex_;
    };
}

using Logger = GLESC::Logger;
