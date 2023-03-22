#include "core/Debugger.h"
#include "Util/Console.h"

GLenum Debugger::glCheckError_(const char *file, int line) {
	GLenum errorCode;
	while ((errorCode = glGetError()) != GL_NO_ERROR) {
		std::string error;
		switch (errorCode) {

			case GL_INVALID_ENUM:
				/**
				 * @brief An unacceptable value is specified for an enumerated argument.
				 * The offending function is ignored,
				 * having no side effect other than to set the error flag.
				 *
				 */
				error = "INVALID_ENUM";
				break;
			case GL_INVALID_VALUE:
				/**
				 * @brief A numeric argument is out of range.
				 * The offending function is ignored,
				 * having no side effect other than to set the error flag.
				 *
				 */
				error = "INVALID_VALUE";
				break;
			case GL_INVALID_OPERATION:
				/**
				 * @brief The specified operation is not allowed in the current state.
				 * The offending function is ignored,
				 *  having no side effect other than to set the error flag.
				 *
				 */
				error = "INVALID_OPERATION";
				break;
			case GL_STACK_OVERFLOW:
				/**
				 * @brief This function would cause a stack overflow.
				 * The offending function is ignored,
				 * having no side effect other than to set the error flag.
				 *
				 */
				error = "STACK_OVERFLOW";
				break;
			case GL_STACK_UNDERFLOW:
				/**
				 * @brief This function would cause a stack underflow.
				 * The offending function is ignored,
				 * having no side effect other than to set the error flag.
				 *
				 */
				error = "STACK_UNDERFLOW";
				break;
			case GL_OUT_OF_MEMORY:
				/**
				 * @brief There is not enough memory left to execute the function.
				 * The state of OpenGL is undefined,
				 * except for the state of the error flags, after this error is recorded.
				 *
				 */
				error = "OUT_OF_MEMORY";
				break;
		}
		Console::error(error + string(" | ") + string(file) + string(" (") + to_string(line) + string(")"));
	}
	return errorCode;
}
