/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#ifndef NDEBUG_GAPI // Don't compile this file if NDEBUG_GAPI is defined
#include <string>
#include <GL/glew.h>
#include "engine/core/low-level-renderer/graphic-api/concrete-apis/debugger/GAPIDebugger.h"
#include "engine/core/debugger/Debugger.h"


#define GL_ENABLE_DEBUG_CALLBACK() \
    OpenGLDebugger::enableGlDebugCallback()
#define GL_SET_DEBUG_CONTEXT_ATTRIBUTE() \
    OpenGLDebugger::setSdlGlDebugContextAttribute()

class OpenGLDebugger {
public:
    /**
     * @brief Enables the OpenGL debug callback
     * @details This callback is used to throw exceptions when an OpenGL error occurs
     * @see https://www.khronos.org/opengl/wiki/Debug_Output
     */
    static inline void enableGlDebugCallback() {
        // Enable OpenGL debug callback
        glEnable(GL_DEBUG_OUTPUT);
        // This ensures that the callback function is called right after an error has occurred.
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        // Set the callback function
        glDebugMessageCallback(glDebugCallback, nullptr);
        // Enable all OpenGL debug messages
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }
    
    /**
     * @brief Sets the SDL_GL_CONTEXT_DEBUG_FLAG attribute
     * @details This attribute is used to enable OpenGL debug context, which is required for
     * the OpenGL debug callback.
     * This might reduce performance. It must be called before creating the OpenGL context.
     * @see https://wiki.libsdl.org/SDL_GLattr#SDL_GLattr
     */
    static inline void setSdlGlDebugContextAttribute() {
        // Enable OpenGL debug context
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
    }

private:
    /**
     * @brief Returns a string representation of the OpenGL error type
     * @details This function is used to convert the type parameter of the OpenGL debug callback
     * to a string
     * @param type
     * @return
     */
    [[nodiscard]] static std::string errorStringFromType(GLenum type);
    
    /**
     * @brief Returns a string representation of the OpenGL error severity
     * @details This function is used to convert the severity parameter of the OpenGL debug
     * callback to a string
     * @param severity
     * @return
     */
    [[nodiscard]] static std::string errorStringFromSeverity(GLenum severity);
    
    /**
     * @brief Returns a string representation of the OpenGL error source
     * @details This function is used to convert the source parameter of the OpenGL debug callback
     * to a string
     * @param source
     * @return
     */
    [[nodiscard]] static std::string errorStringFromSource(GLenum source);
    
    /**
     * @brief The OpenGL debug callback
     * @details This callback is used to throw exceptions when an OpenGL error occurs
     * @param source
     * @param type
     * @param errorCode
     * @param severity
     * @param length
     * @param message
     * @param userParam
     */
    static void
    glDebugCallback(GLenum source, GLenum type, GLuint errorCode, GLenum severity, GLsizei length,
                    const GLchar *message, const void *userParam);
}; // class OpenGLDebugger
#endif