#include "engine/plat-independence/graphics-device-interface/concrete-gdi/opengl/OpenGLGDI.h"
#include "engine/foundation/logger/Logger.h"
#include "engine/foundation/exceptions/plat-indep/GDIInitException.h"
#include "engine/plat-independence/graphics-device-interface/concrete-gdi/opengl/OpenGLDebugger.h"
#include <string>
void OpenGLGDI::init(std::shared_ptr<WindowManager> window) {
    this->window = window;
    
    // Tells OpenGL which size is the viewport where things are displayed
    // Must be called after creating the context
    glViewport(0, 0, windowManager->getWidth(), windowManager->getHeight());
    
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


void OpenGLGDI::createContext() {
    // OpenGL context initialization over the SDL window, needed for using OpenGL functions
    if ((this->context = SDL_GL_CreateContext(window.get())) == nullptr)
        throw EngineException("Unable to create context: " + std::string(SDL_GetError()));
    else
        Logger::get().success("GL context created!");
    // Must be called after creating the context
    this->setViewport(0, 0, window->getWidth(), window->getHeight());
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


void OpenGLGDI::swapBuffers() {
    SDL_GL_SwapWindow(window.get());
}

void OpenGLGDI::setViewport(int x, int y, int width, int height) {

}

void OpenGLGDI::setViewport(int width, int height) {

}

void OpenGLGDI::setViewport() {

}
void OpenGLGDI::useShader(const std::string &shaderName) {

}
void OpenGLGDI::bindMesh(const std::string &meshName) {

}

int OpenGLGDI::loadTexture(const std::string &texturePath) {
    return 0;
}

void OpenGLGDI::bindTexture(int textureID) {

}

void OpenGLGDI::setGlAttribute(SDL_GLattr attrib, int val) {
    if (SDL_GL_SetAttribute(attrib, val) == -1)
        throw GDIException("Unable to set gl attribute: " + std::string(SDL_GetError()));
}

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
