#pragma once

#include <string>
#include "GL/glew.h"

class OpenGLDebugger {
    /**
     * @brief Returns a string representation of the OpenGL error type
     * @details This function is used to convert the type parameter of the OpenGL debug callback to a string
     * @param type
     * @return
     */
    [[nodiscard]] static std::string errorStringFromType(GLenum type);
    
    /**
     * @brief Returns a string representation of the OpenGL error severity
     * @details This function is used to convert the severity parameter of the OpenGL debug callback to a string
     * @param severity
     * @return
     */
    [[nodiscard]] static std::string errorStringFromSeverity(GLenum severity);
    
    /**
     * @brief Returns a string representation of the OpenGL error source
     * @details This function is used to convert the source parameter of the OpenGL debug callback to a string
     * @param source
     * @return
     */
    [[nodiscard]] static std::string errorStringFromSource(GLenum source);
    
    /**
     * @brief The OpenGL debug callback
     * @details This callback is used to throw exceptions when an OpenGL error occurs
     * @param source
     * @param type
     * @param id
     * @param severity
     * @param length
     * @param message
     * @param userParam
     */
    static void
    glDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message,
                    const void *userParam);

public:
    /**
     * @brief Enables the OpenGL debug callback
     * @details This callback is used to throw exceptions when an OpenGL error occurs
     * @see https://www.khronos.org/opengl/wiki/Debug_Output
     */
    static void enableGlDebugCallback();
    
    /**
     * @brief Sets the SDL_GL_CONTEXT_DEBUG_FLAG attribute
     * @details This attribute is used to enable OpenGL debug context, which is required for the OpenGL debug callback.
     * This might reduce performance. It must be called before creating the OpenGL context.
     * @see https://wiki.libsdl.org/SDL_GLattr#SDL_GLattr
     */
    static void setSdlGlDebugContextAttribute();
};
