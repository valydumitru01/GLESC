#include "engine/core/graphics-device-interface/concrete-gdi/opengl/OpenGLGDI.h"
#include "engine/core/logger/Logger.h"
#include "engine/core/exceptions/plat-indep/GDIInitException.h"
#include "engine/core/graphics-device-interface/concrete-gdi/opengl/OpenGLDebugger.h"
#include <string>


OpenGLGDI::OpenGLGDI(WindowManager &windowManager) {
    // Tells OpenGL which size is the viewport where things are displayed
    // Must be called after creating the context
    this->setViewport(windowManager.getWidth(), windowManager.getHeight());
    
    GLuint err;
    glewExperimental = GL_TRUE;
    if ((err = glewInit()) != GLEW_OK)
        throw GDIInitException(
                "Unable to initialize GLEW: " + std::string(reinterpret_cast<const char *>(glewGetErrorString(err))));
    
    Logger::get().success("Glew Initialized!");
    
    
    // This makes our buffer swap synchronized with the monitor's vertical refresh
    // Parameters: 0 for immediate updates, 1 for updates synchronized with the vertical retrace, -1 for adaptive v-sync
    // More info: https://wiki.libsdl.org/SDL2/SDL_GL_SetSwapInterval
    if (SDL_GL_SetSwapInterval(1) == -1)
        throw EngineException(std::string("Unable activate v-sync (swap interval): ") + std::string(SDL_GetError()));
    
    // Enable depth test
    // Fragments will be discarded if they are behind
    // More info: https://www.khronos.org/opengl/wiki/Depth_Test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    // Enable back face culling
    // Important for performance
    // More info: https://www.khronos.org/opengl/wiki/Face_Culling
    glEnable(GL_CULL_FACE);
    // Cull back faces (default)
    // Important for performance and to avoid self-shadowing
    glCullFace(GL_BACK);
    // Set the front face to be counter-clockwise (default)
    glFrontFace(GL_CCW);
    
    // Enable blending
    // Important for transparency and other effects
    // More info: https://www.khronos.org/opengl/wiki/Blending
    glEnable(GL_BLEND);
    // Set blending function to alpha blending (default)
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // Set blending equation to add (default)
    glBlendEquation(GL_FUNC_ADD);
    
    // Enable opengl debug callback
    // Improves debugging outputs
    OpenGLDebugger::enableGlDebugCallback();
}

std::function<void(SDL_Window&, GDIint, GDIint, GDIint, GDIint )> OpenGLGDI::getCreateContextFunc() {
    return [this](SDL_Window& window, GDIint w, GDIint h, GDIint x, GDIint y) {
        return this->createContext(window, w, h, x, y);
    };
}

void OpenGLGDI::createContext(SDL_Window& window, GDIint w, GDIint h, GDIint x, GDIint y) {
    // OpenGL context initialization over the SDL windowManager, needed for using OpenGL functions
    if ((this->context = SDL_GL_CreateContext(&window)) == nullptr)
        throw EngineException("Unable to create context: " + std::string(SDL_GetError()));
    else
        Logger::get().success("GL context created!");
    // Must be called after creating the context
    this->setViewport(w, h, x, y);
}

void OpenGLGDI::setAttributes() {
    // Core functions of OpenGL a.k.a. full modern openGL functionality.
    // More info: https://wiki.libsdl.org/SDL_GLprofile
    setGlAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    // We're using OpenGL Version 4.3 (released in 2012).
    // Changing this numbers will change some functions available of OpenGL.
    // Choosing a relatively old version of OpenGl allow most computers to use it.
    int major = 4, minor = 3;
    setGlAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
    setGlAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);
    Logger::get().importantInfo("OpenGL Version: " + std::to_string(major) + "." + std::to_string(minor));
    // Stencil size of 4 bits is used
    // Could be increased later if needed
    // Increases performance the lower it is, less data stored in each pixel
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 4);
    // Enable debug context
    // Possible performance loss
    OpenGLDebugger::setSdlGlDebugContextAttribute();
}


std::function<void(SDL_Window*)> OpenGLGDI::getSwapBuffersFunc() {
    return {SDL_GL_SwapWindow};
}

void OpenGLGDI::setViewport(int x, int y, int width, int height) {
    glViewport(0, 0, width, height);
}

void OpenGLGDI::setViewport(int width, int height) {
    this->setViewport(0, 0, width, height);
}

void OpenGLGDI::setViewport() {

}

void OpenGLGDI::useShader(const std::string &shaderName) {

}


GDIuint
OpenGLGDI::createTexture(SDL_Surface &surface, TextureFilter::MinFilter minFilter, TextureFilter::MagFilter magFilter,
                         TextureFilter::WrapMode wrapS, TextureFilter::WrapMode wrapT) {
    GDIuint textureID;
    glGenTextures(1, &textureID);
    bindTexture(textureID);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFilterToGl <TextureFilter::MinFilter>(minFilter));
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFilterToGl <TextureFilter::MagFilter>(magFilter));
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureFilterToGl <TextureFilter::WrapMode>(wrapS));
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureFilterToGl <TextureFilter::WrapMode>(wrapT));
    
    
    GLenum format = (surface.format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
    // Generate the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface.w, surface.h, 0, format, GL_UNSIGNED_BYTE, surface.pixels);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    
    bindTexture(0);
    return textureID;
}

void OpenGLGDI::bindTexture(GDIuint textureID) {
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void OpenGLGDI::setGlAttribute(SDL_GLattr attrib, int val) {
    if (SDL_GL_SetAttribute(attrib, val) == -1)
        throw GDIException("Unable to set gl attribute: " + std::string(SDL_GetError()));
}


















// -------------------------------------------------------------------------
// --------------------------- Shader functions ----------------------------

GLint OpenGLGDI::getUniformLocation(GLint program, const std::string &name) {
    return glGetUniformLocation(program, name.c_str());
}

void OpenGLGDI::setUniform1Float(GLint location, GLfloat v0) {
    glUniform1f(location, v0);
}

void OpenGLGDI::setUniform1FloatVector(GLint location, GLsizei count, const GLfloat *value) {
    glUniform1fv(location, count, value);
}

void OpenGLGDI::setUniform1Int(GLint location, GLint v0) {
    glUniform1i(location, v0);
}

void OpenGLGDI::setUniform1IntVector(GLint location, GLsizei count, const GLint *value) {
    glUniform1iv(location, count, value);
}

void OpenGLGDI::setUniform2Float(GLint location, GLfloat v0, GLfloat v1) {
    glUniform2f(location, v0, v1);
}

void OpenGLGDI::setUniform2FloatVector(GLint location, GLsizei count, const GLfloat *value) {
    glUniform2fv(location, count, value);
}

void OpenGLGDI::setUniform2Int(GLint location, GLint v0, GLint v1) {
    glUniform2i(location, v0, v1);
}

void OpenGLGDI::setUniform2IntVector(GLint location, GLsizei count, const GLint *value) {
    glUniform2iv(location, count, value);
}

void OpenGLGDI::setUniform3Float(GLint location, GLfloat v0, GLfloat v1, GLfloat v2) {
    glUniform3f(location, v0, v1, v2);
}

void OpenGLGDI::setUniform3FloatVector(GLint location, GLsizei count, const GLfloat *value) {
    glUniform3fv(location, count, value);
}

void OpenGLGDI::setUniform3Int(GLint location, GLint v0, GLint v1, GLint v2) {
    glUniform3i(location, v0, v1, v2);
}

void OpenGLGDI::setUniform3IntVector(GLint location, GLsizei count, const GLint *value) {
    glUniform3iv(location, count, value);
}

void OpenGLGDI::setUniform4Float(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
    glUniform4f(location, v0, v1, v2, v3);
}

void OpenGLGDI::setUniform4FloatVector(GLint location, GLsizei count, const GLfloat *value) {
    glUniform4fv(location, count, value);
}

void OpenGLGDI::setUniform4Int(GLint location, GLint v0, GLint v1, GLint v2, GLint v3) {
    glUniform4i(location, v0, v1, v2, v3);
}

void OpenGLGDI::setUniform4IntVector(GLint location, GLsizei count, const GLint *value) {
    glUniform4iv(location, count, value);
}

void OpenGLGDI::setUniformMatrix2FloatVector(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {
    glUniformMatrix2fv(location, count, transpose, value);
}

void OpenGLGDI::setUniformMatrix3FloatVector(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {
    glUniformMatrix3fv(location, count, transpose, value);
}

void OpenGLGDI::setUniformMatrix4FloatVector(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {
    glUniformMatrix4fv(location, count, transpose, value);
}

void OpenGLGDI::useShaderProgram(int shaderProgram) {
    glUseProgram(shaderProgram);
}
