/******************************************************************************
 * @file   GAPIDebugger.h
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

#define GAPI_PRINT_CODE(CONTENT) do {} while (false)
#define PRINT_GAPI_INIT(name, version) do {} while (false)
#define GAPI_FUNCTION_LOG(FUNCTION_NAME, ...) do {} while (false)
#define GAPI_FUNCTION_NO_ARGS_LOG(FUNCTION_NAME) do {} while (false)
#define GAPI_FUNCTION_IMPLEMENTATION_LOG(FUNCTION_NAME, ...) do {} while (false)
#define GAPI_PRINT_BUFFER_DATA(TYPE, DATA, SIZE) do {} while (false)

#ifndef NDEBUG_GAPI

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
    Logger::get().infoBlue("Entering " + std::string(FUNCTION_NAME));

#define GAPI_FUNCTION_IMPLEMENTATION_LOG(FUNCTION_NAME, ...) \
    Logger::get().infoBlue("\tExecuting " +           \
            FUNCTION_CALL_STR(FUNCTION_NAME, __VA_ARGS__));

#define GAPI_PRINT_BUFFER_DATA(TYPE, DATA, SIZE) \
    printBufferData<TYPE>(DATA, SIZE)
template<typename BufferType>
void printBufferData(const GLESC::GAPI::Void *data, GLESC::GAPI::Size size) {
    const BufferType *typedData = static_cast<const BufferType *>(data);
    size_t count = size / sizeof(BufferType); // Calculate how many elements are in the buffer

    // Determine the maximum width needed for alignment
    BufferType max_value = *std::max_element(typedData, typedData + count);
    int max_width = std::to_string(max_value).length();

    for (size_t i = 0; i < count; ++i) {
        // Use std::setw to set the width and std::setfill to fill with spaces
        std::cout << std::setw(max_width) << std::setfill(' ') << typedData[i] << " ";
        if (i % 8 == 7) std::cout << std::endl; // Print 8 elements per line for readability
    }
    std::cout << std::endl;
}

inline void printGAPIInit(const std::string& GAPIName, const std::string& GAPIVersion){
   Logger::get().importantSuccess(
           "Initializing Graphic Application Programming Interface (GAPI)");
   Logger::get().success("\t" + GAPIName + " version " + GAPIVersion);
}
#endif