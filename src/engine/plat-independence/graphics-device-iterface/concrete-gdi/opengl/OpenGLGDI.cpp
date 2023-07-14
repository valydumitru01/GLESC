#include "engine/plat-independence/graphics-device-interface/concrete-gdi/opengl/OpenGLGDI.h"
#include "engine/foundation/logger/Logger.h"
#include "engine/foundation/exceptions/plat-indep/GDIInitException.h"
#include "OpenGLDebugger.h"
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
