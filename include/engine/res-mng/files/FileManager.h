/**************************************************************************************************
 * @file   FileManager.h
 * @author Valentin Dumitru
 * @date   2024-04-17
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

#pragma once
#include <string>
/**
 * @brief Static class that handles file operations
 */
class FileManager {
public:
    /**
     * @brief Read a file from the disk
     * @param path The path to the file
     * @return The content of the file
     */
    static std::string readFile(const std::string &path);
    /**
     * @brief Write a file to the disk
     * @param path The path to the file
     * @param content The content of the file
     */
    static void writeFile(const std::string &path, const std::string &content);
private:
};
