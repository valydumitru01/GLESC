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
#define LOG(initialMessage, CODE) \
            do{                                     \
           GLESC::Logger::get().info(initialMessage);     \
            CODE                                 \
            } while(0)
#define LOG_BASIC(CODE) \
            do{                                     \
            CODE                                 \
            } while(0)

#endif


#ifndef NDEBUG

#include "engine/core/logger/Logger.h"
#include "Stringer.h"
#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include <iterator>
#include <sstream>
#include <type_traits>
#include <cstring>
#include <algorithm>

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



    template<typename T>
    std::string argsToString(const char* names, T value) {
        std::ostringstream arg;
        const char* nameEnd = std::strchr(names, ',');
        std::string name(names, nameEnd ? nameEnd - names : std::strlen(names));
        
        arg << name << ": " << GLESC::toString(value);
        std::string result = arg.str();
        
        // Replace '\n' with a space (or any other character/string)
        std::replace(result.begin(), result.end(), '\n', ' ');
        
        if (nameEnd && *nameEnd == ',') {
            nameEnd++; // Skip the comma
            while (*nameEnd == ' ') nameEnd++; // Skip any whitespace after the comma
            return result + ", " + argsToString(nameEnd, std::forward<T>(value));
        } else {
            return result;
        }
    }
    
    template<typename T, typename... Args>
    std::string argsToString(const char* names, T value, Args... args) {
        std::ostringstream arg;
        const char* nameEnd = strchr(names, ',');
        std::string name(names, nameEnd ? nameEnd - names : strlen(names));
        
        arg << name << ": " << GLESC::toString(value);
        
        if (nameEnd && *nameEnd == ',') {
            nameEnd++; // Skip the comma
            while (*nameEnd == ' ') nameEnd++; // Skip any whitespace after the comma
            // Recursively process the remaining arguments
            return arg.str() + ", " + argsToString(nameEnd, args...);
        } else {
            return arg.str();
        }
    }
#else
    #define SDLCall(call) call
#endif