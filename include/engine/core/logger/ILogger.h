/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once
#include <string>

class ILogger {
public:
    virtual ~ILogger() = default;
    /**
     * @brief Display log messages
     * Background and text default
     * @param text
     */
    virtual void log(const std::string& text) = 0;
    /**
     * @brief Display error messages
     * Background -- Red
     * Text       -- Black Bold
     *
     * @param text printed text
     */
    virtual void error(const std::string& text) = 0;

    /**
     * @brief Display warning messages
     * Background -- Black
     * Text       -- Yellow
     *
     * @param text printed text
     */
    virtual void warning(const std::string& text) = 0;

    /**
     * @brief Display non important information
     * Background -- Black
     * Text       -- Grey
     *
     * @param text printed text
     */
    virtual void nonImportantInfo(const std::string& text) = 0;

    /**
     * @brief Display basic information
     * Background -- Black
     * Text       -- White
     *
     * @param text printed text
     */
    virtual void info(const std::string& text) = 0;


    /**
     * @brief Display basic information
     * Background -- Black
     * Text       -- Light Blue
     *
     * @param text printed text
     */
    virtual void infoBlue(const std::string& text) = 0;

    /**
     * @brief Display basic information
     * Background -- Black
     * Text       -- Light Purple
     *
     * @param text printed text
     */

    virtual void infoPurple(const std::string& text) = 0;
    /**
     * @brief Display important information
     * Background -- White
     * Text       -- Black
     *
     * @param text printed text
     */
    virtual void importantInfo(const std::string& text) = 0;
    /**
     * @brief Display important information
     * Background -- Light Blue
     * Text       -- Black
     *
     * @param text printed text
     */

    virtual void importantInfoBlue(const std::string& text) = 0;

    /**
     * @brief Display important information
     * Background -- Light Purple
     * Text       -- Black
     *
     * @param text printed text
     */
    virtual void importantInfoPurple(const std::string& text) = 0;

    /**
     * @brief Display important information
     * Background -- White
     * Text       -- Black
     *
     * @param text printed text
     */
    virtual void importantInfoWhite(const std::string& text) = 0;

    /**
     * @brief Display important success information
     * @param text
     */
    virtual void importantSuccess(const std::string& text) = 0;

    /**
     * @brief Display success information
     * Background -- Green
     * Text       -- White Bold
     *
     * @param text printed text
     */
    virtual void success(const std::string& text) = 0;
};
