#include "renderer/RenderDebugger.h"
#include "Util/Console.h"

GLenum RenderDebugger::glCheckErrorInLine(const char *file, int line) {
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR) {
        std::string error;
        switch (errorCode) {
            case GL_INVALID_ENUM:
                error = INVALID_ENUM_ERROR_MESSAGE;
                break;
            case GL_INVALID_VALUE:
                error = INVALID_VALUE_ERROR_MESSAGE;
                break;
            case GL_INVALID_OPERATION:
                error = INVALID_OPERATION_ERROR_MESSAGE;
                break;
            case GL_STACK_OVERFLOW:
                error = STACK_OVERFLOW_ERROR_MESSAGE;
                break;
            case GL_STACK_UNDERFLOW:
                error = STACK_UNDERFLOW_ERROR_MESSAGE;
                break;
            case GL_OUT_OF_MEMORY:
                error = OUT_OF_MEMORY_ERROR_MESSAGE;
                break;
            default:
                error = UNKNOWN_ERROR_MESSAGE;
                break;
        }
        Console::error(error + string(" | ") + string(file) + string(" (") + to_string(line) + string(")"));
    }
    return errorCode;
}
