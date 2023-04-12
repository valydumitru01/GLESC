#pragma once

#include <GL/gl.h>

#include "util/Console.h"
#include "exceptions/RenderException.h"

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
     * @brief Check for OpenGL errors and throw an exception if one is found.
     * @param file The file where the error occurred.
     * @param line The line where the error occurred.
     * @return The error code.
     */
    static GLenum glCheckErrorInLine(const char *file, int line);

private:
    /**
     * @brief Get the error string from the error code.
     * @param errorCode The error code.
     * @return The error string.
     */
    static std::string errorStringFromCode(GLenum errorCode);
};