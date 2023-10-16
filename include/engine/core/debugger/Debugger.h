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

#include <string>
#include "engine/core/logger/Logger.h"


#ifdef NLOGGING
    #define DEBUG_CODE(initialMessage, CONTENT) \
            do { } while (0)
#else
    #define LOG(initialMessage, CONTENT) \
            do{                                     \
           GLESC::Logger::get().info(initialMessage);     \
            CONTENT                                 \
            } while(0)
    #define LOG_BASIC(CONTENT) \
            do{                                     \
            CONTENT                                 \
            } while(0)

#endif


#ifndef NDEBUG_GAPI
    #define GAPI_DEBUG_CODE(CONTENT) \
                do {                                     \
                CONTENT                                  \
                } while (0)
#else
    #define GAPI_DEBUG_CODE(CONTENT) \
            do { } while (0)
#endif