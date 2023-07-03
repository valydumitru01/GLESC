#include "renderer/RenderDebugger.h"

GLenum RenderDebugger::glCheckErrorInLine(const char *file, int line) {
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR) {
        std::string error = errorStringFromCode(errorCode);
        throw RenderException(
                "Error code " + std::to_string(errorCode) + ": " + error + " | " + file + "(" + std::to_string(line) +
                ")");
    }
    return errorCode;
}

std::string RenderDebugger::errorStringFromCode(GLenum errorCode) {
    switch (errorCode) {
        case GL_INVALID_ENUM:
            return INVALID_ENUM_ERROR_MESSAGE;
        case GL_INVALID_VALUE:
            return INVALID_VALUE_ERROR_MESSAGE;
        case GL_INVALID_OPERATION:
            return INVALID_OPERATION_ERROR_MESSAGE;
        case GL_STACK_OVERFLOW:
            return STACK_OVERFLOW_ERROR_MESSAGE;
        case GL_STACK_UNDERFLOW:
            return STACK_UNDERFLOW_ERROR_MESSAGE;
        case GL_OUT_OF_MEMORY:
            return OUT_OF_MEMORY_ERROR_MESSAGE;
        default:
            return UNKNOWN_ERROR_ERROR_MESSAGE;
    }
}

std::string RenderDebugger::errorStringFromSource(GLenum source) {
    
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

std::string RenderDebugger::errorStringFromType(GLenum type) {
    std::string typeString;
    
    typeString += "Type: ";
    
    switch (type){
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
            return typeString + "Push Group";
        case GL_DEBUG_TYPE_POP_GROUP:
            return typeString + "Pop Group";
        case GL_DEBUG_TYPE_OTHER:
            return typeString + "Other";
        default:
            return typeString + "Unknown";
    }
}

std::string RenderDebugger::errorStringFromSeverity(GLenum severity) {
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

void RenderDebugger::initDebugCallback() {
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(glDebugCallback, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    Logger::get().warning("Debug callback initialized");
}

void RenderDebugger::glDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                     const GLchar *message, const void *userParam) {
    // ignore non-significant error/warning codes
    if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
        return;
    
    throw RenderException(
            "Debug message (" + std::to_string(id) + "): " + message + " | " + errorStringFromSource(source) + " | " +
            errorStringFromType(type) + " | " + errorStringFromSeverity(severity));
    
}
