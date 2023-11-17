/******************************************************************************
 * @file   Example.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#ifndef NDEBUG_GAPI // Don't compile this file if NDEBUG_GAPI is defined

#include <set>
#include <SDL2/SDL.h>
#include "engine/core/low-level-renderer/graphic-api/concrete-apis/opengl/OpenGLDebugger.h"
#include "engine/core/low-level-renderer/asserts/GAPIAsserts.h"

void OpenGLDebugger::glDebugCallback(GLenum source, GLenum type, GLuint errorCode,
                                     GLenum severity, GLsizei length,
                                     const GLchar *message, const void *userParam) {
    // ignore non-significant error/warning codes
    const std::set<GLuint> nonSignificantErrorCodes = {131169, 131185, 131218, 131204};
    if (nonSignificantErrorCodes.find(errorCode) != nonSignificantErrorCodes.end()) {
        return;
    }
    ASSERT_GL_CALL_IS_CORRECT(false,
                              "Debug message (" + std::to_string(errorCode) + "): \n Message:" + message +
                              "\n | " + errorStringFromSource(source) +
                              "\n | " + errorStringFromType(type) +
                              "\n | " + errorStringFromSeverity(severity));
    
}

std::string OpenGLDebugger::errorStringFromSource(GLenum source) {
    
    std::string sourceString;
    
    sourceString += "Source: ";
    
    switch (source) {
        case GL_DEBUG_SOURCE_API:
            return sourceString + "API";
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            return sourceString + "Window System";
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            return sourceString + "Shader Compiler";
        case GL_DEBUG_SOURCE_THIRD_PARTY:
            return sourceString + "Third Party";
        case GL_DEBUG_SOURCE_APPLICATION:
            return sourceString + "Application";
        case GL_DEBUG_SOURCE_OTHER:
            return sourceString + "Other";
        default:
            return sourceString + "Unknown";
    }
}

std::string OpenGLDebugger::errorStringFromType(GLenum type) {
    std::string typeString;
    
    typeString += "Type: ";
    
    switch (type) {
        case GL_DEBUG_TYPE_ERROR:
            return typeString + "Error";
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            return typeString + "Deprecated Behaviour";
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            return typeString + "Undefined Behaviour";
        case GL_DEBUG_TYPE_PORTABILITY:
            return typeString + "Portability";
        case GL_DEBUG_TYPE_PERFORMANCE:
            return typeString + "Performance";
        case GL_DEBUG_TYPE_MARKER:
            return typeString + "Marker";
        case GL_DEBUG_TYPE_PUSH_GROUP:
            return typeString + "push Group";
        case GL_DEBUG_TYPE_POP_GROUP:
            return typeString + "Pop Group";
        case GL_DEBUG_TYPE_OTHER:
            return typeString + "Other";
        default:
            return typeString + "Unknown";
    }
}

std::string OpenGLDebugger::errorStringFromSeverity(GLenum severity) {
    std::string severityString;
    
    severityString += "Severity: ";
    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:
            return severityString + "High";
        case GL_DEBUG_SEVERITY_MEDIUM:
            return severityString + "Medium";
        case GL_DEBUG_SEVERITY_LOW:
            return severityString + "Low";
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            return severityString + "Notification";
        default:
            return severityString + "Unknown";
    }
}

#endif
