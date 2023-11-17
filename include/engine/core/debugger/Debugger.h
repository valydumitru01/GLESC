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


#ifndef NDEBUG
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include "engine/core/logger/Logger.h"

#define SDLCall(call)                                                 \
    do {                                                              \
        call;                                                         \
        const char* error = SDL_GetError();                           \
        if (*error != '\0') {                                         \
            Logger::get().error("Error when calling SDL function: "   \
                #call " " + std::string(error)); \
            SDL_ClearError();                                         \
        }                                                             \
    } while (0)
#else
    #define SDLCall(call) call
#endif