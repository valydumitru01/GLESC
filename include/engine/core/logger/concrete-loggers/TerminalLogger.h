/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once
#include "engine/core/logger/ILogger.h"

class TerminalLogger : public ILogger
{
public:
    TerminalLogger();
    
    void log(const std::string &text) override;
    
    void error(const std::string &text) override;
    
    void warning(const std::string &text) override;
    
    void info(const std::string &text) override;
    
    void infoBlue(const std::string &text) override;
    
    void infoPurple(const std::string &text) override;

    void importantInfo(const std::string &text) override;

    void importantInfoBlue(const std::string &text) override;
    
    void importantInfoPurple(const std::string &text) override;
    
    void importantSuccess(const std::string &text) override;
    
    void success(const std::string &text) override;

};