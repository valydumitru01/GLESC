
#include "engine/plat-independence/graphics-device-interface/concrete-gdi/opengl/OpenGLDebugger.h"
#include "engine/foundation/exceptions/plat-indep/GDIException.h"
#include "SDL2/SDL.h"
#include "engine/foundation/logger/Logger.h"

void OpenGLDebugger::glDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                const GLchar *message, const void *userParam) {
    // ignore non-significant error/warning codes
    if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
        return;
    
    throw GDIException(
            "Debug message (" + std::to_string(id) + "): " + message + " | " + errorStringFromSource(source) + " | " +
            errorStringFromType(type) + " | " + errorStringFromSeverity(severity));
    
}

void OpenGLDebugger::enableGlDebugCallback() {
    #ifdef DEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(glDebugCallback, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    #endif
}

void OpenGLDebugger::setSdlGlDebugContextAttribute() {
    #ifdef DEBUG
    Logger::get().warning("ENTERING DEBUG MODE");
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
    #endif
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

