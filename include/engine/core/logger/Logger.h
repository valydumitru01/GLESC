/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <string>
#include <memory>
#include <vector>
#include "ILogger.h"

namespace GLESC {
    class Logger : public ILogger {
    public:
        /**
         * @brief Copy constructor is deleted
         * @details Copy constructor is deleted because we don't want to have multiple instances of Logger
         * @param logger
         */
        Logger(const Logger &) = delete;
        
        /**
         * @brief Assignment operator is deleted
         * @details Assignment operator is deleted because we don't want to have multiple instances of Logger
         * @return Logger&
         */
        Logger &operator=(const Logger &) = delete;
        
        /**
         * @brief Executes given function on all loggers
         * @param func
         * @param text
         */
        void
        executeOnAllInputs(void (ILogger::*func)(const std::string &), const std::string &text);
        
        /**
         * @brief Get the Logger object
         * @details Get the Logger object. This is a singleton.
         * @return Logger&
         */
        static Logger &get();
        
        void addLogger(std::unique_ptr<ILogger> loggerParam);
        
        void log(const std::string &text) override;
        
        void error(const std::string &text) override;
        
        void warning(const std::string &text) override;

        void nonImportantInfo(const std::string &text) override;

        void info(const std::string &text) override;
        
        void infoBlue(const std::string &text) override;
        
        void infoPurple(const std::string &text) override;
        
        void importantInfo(const std::string &text) override;
        
        void importantInfoBlue(const std::string &text) override;
        
        void importantInfoPurple(const std::string &text) override;

        void importantInfoWhite(const std::string &text) override;
        
        void importantSuccess(const std::string &text) override;
        
        void success(const std::string &text) override;
    
    private:
        Logger();
        
        std::vector<std::unique_ptr<ILogger>> loggers;
    };
    
}
using Logger = GLESC::Logger ;