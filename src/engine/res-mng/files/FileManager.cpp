/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/res-mng/files/FileManager.h"
#include "engine/core/exceptions/resources/OpenException.h"

std::string FileManager::readFile(const std::string &path) {
    std::ifstream inFile(path);
    if (!inFile) {
        throw OpenException("Unable to open file for reading: " + path);
    }
    
    std::stringstream buffer;
    buffer << inFile.rdbuf();
    
    // No need to close the file - the destructor will do it automatically.
    return buffer.str();
}

void FileManager::writeFile(const std::string &path, const std::string &content) {
    std::ofstream outFile(path);
    if (!outFile) {
        throw OpenException("Unable to open file for writing: " + path);
    }
    
    // No need to close the file - the destructor will do it automatically.
    outFile << content;
}