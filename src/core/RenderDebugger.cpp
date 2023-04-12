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