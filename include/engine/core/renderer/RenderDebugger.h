#pragma once

#include "GL/glew.h"
#include "GL/gl.h"

#include "engine/core/debug-profile/Console.h"
#include "foundation/exceptions/RenderException.h"

#define glCheckError() RenderDebugger::glCheckErrorInLine(__FILE__, __LINE__)
/**
 * @brief An unacceptable value is specified for an enumerated argument.
 * The offending function is ignored,
 * having no side effect other than to set the error flag.
 *
 */
#define INVALID_ENUM_ERROR_MESSAGE "INVALID_ENUM"

/**
 * @brief A numeric argument is out of range.
 * The offending function is ignored,
 * having no side effect other than to set the error flag.
 *
 */
#define INVALID_VALUE_ERROR_MESSAGE "INVALID_VALUE"
/**
 * @brief The specified operation is not allowed in the current state.
 * The offending function is ignored,
 *  having no side effect other than to set the error flag.
 *
 */
#define INVALID_OPERATION_ERROR_MESSAGE "INVALID_OPERATION"
/**
 * @brief This function would cause a stack overflow.
 * The offending function is ignored,
 * having no side effect other than to set the error flag.
 *
 */
#define STACK_OVERFLOW_ERROR_MESSAGE "STACK_OVERFLOW"
/**
 * @brief This function would cause a stack underflow.
 * The offending function is ignored,
 * having no side effect other than to set the error flag.
 *
 */
#define STACK_UNDERFLOW_ERROR_MESSAGE "STACK_UNDERFLOW"
/**
 * @brief There is not enough memory left to execute the function.
 * The state of OpenGL is undefined,
 * except for the state of the error flags, after this error is recorded.
 *
 */
#define OUT_OF_MEMORY_ERROR_MESSAGE "OUT_OF_MEMORY"
/**
 * @brief An unknown error has occurred.
 *
 */
#define UNKNOWN_ERROR_ERROR_MESSAGE "UNKNOWN_ERROR"

class RenderDebugger {
public:
    /**
     * @brief Check for OpenGL errors and throw an exception if one is found. Only for opengl lower than 4.3.
     * @param file The file where the error occurred.
     * @param line The line where the error occurred.
     * @return The error code.
     */
    static GLenum glCheckErrorInLine(const char *file, int line);
    
    /**
     * @brief Initialize the debug callback.
     * @note This function is only available if the OpenGL version is 4.3 or higher.
     */
    static void initDebugCallback();
private:
    /**
     * @brief Get the error string from the error code.
     * @param errorCode The error code.
     * @return The error string.
     */
    static std::string errorStringFromCode(GLenum errorCode);
    
    /**
     * @brief Get the error string from the source.
     * @param source The source of the error.
     * @return The error string.
     */
    static std::string errorStringFromSource(GLenum source);
    
    /**
     * @brief Get the error string from the type.
     * @param type The type of the error.
     * @return The error string.
     */
    static std::string errorStringFromType(GLenum type);
    
    /**
     * @brief Get the error string from the severity.
     * @param severity The severity of the error.
     * @return The error string.
     */
    static std::string errorStringFromSeverity(GLenum severity);
    
    /**
     * @brief The OpenGL debug callback function.
     * @param source The source of the debug message.
     * @param type The type of the debug message.
     * @param id The ID of the debug message.
     * @param severity The severity of the debug message.
     * @param length The length of the debug message.
     * @param message The debug message itself.
     * @param userParam User-defined parameter.
     */
    static void GLAPIENTRY glDebugCallback(GLenum source, GLenum type, GLuint id,
        GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
};