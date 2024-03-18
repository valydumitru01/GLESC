/******************************************************************************
 * @file   Example.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "engine/core/debugger/Debugger.h"
#include "engine/core/logger/Logger.h"

#ifndef NLOGGING

#define GAPI_PRINT_CODE(CONTENT) \
    LOG_BASIC(Logger::get().info("GAPI status:"); \
        CONTENT                  \
        )

#define PRINT_GAPI_INIT(name, version) \
    GAPI_PRINT_CODE(printGAPIInit(name, version););

// Macro to log the function name and its parameters
#define GAPI_FUNCTION_LOG(FUNCTION_NAME, ...) \
    Logger::get().infoBlue("Entering GAPI function: " + \
            FUNCTION_CALL_STR(FUNCTION_NAME, __VA_ARGS__));

#define GAPI_FUNCTION_NO_ARGS_LOG(FUNCTION_NAME) \
    Logger::get().info("Entering " + std::string(FUNCTION_NAME));

#define GAPI_FUNCTION_IMPLEMENTATION_LOG(FUNCTION_NAME, ...) \
    Logger::get().infoBlue("\tExecuting " +           \
            FUNCTION_CALL_STR(FUNCTION_NAME, __VA_ARGS__));

inline void printGAPIInit(const std::string& GAPIName, const std::string& GAPIVersion){
   Logger::get().importantSuccess(
           "Initializing Graphic Application Programming Interface (GAPI)");
   Logger::get().success("\t" + GAPIName + " version " + GAPIVersion);
}
#endif