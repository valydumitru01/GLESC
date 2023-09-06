/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "engine/core/debugger/Debugger.h"
#include "engine/core/logger/Logger.h"

#define GAPI_DEBUG_CODE(CONTENT) \
    DEBUG_CODE_BASIC(Logger::get().info("GAPI status:"); CONTENT)

#define PRINT_GAPI_INIT(name, version) \
    GAPI_DEBUG_CODE(printGAPIInit(name, version);)
    
inline void printGAPIInit(const std::string& GAPIName, const std::string& GAPIVersion){
    Logger::get().importantSuccess("Initializing Graphic Application Programming Interface");
    Logger::get().success("\t" + GAPIName + " version " + GAPIVersion);
}