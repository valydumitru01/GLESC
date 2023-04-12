#include <utility>

#include "renderer/Renderer.h"

Renderer::Renderer(std::shared_ptr <WindowManager> &windowManager) : projection(), view(), windowManager(std::move(windowManager)),
                                                                     textureManager(),
                                                                     context(nullptr) {
    initGlContext();
    initGLEW();
    
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
    
    shaderManager = make_unique <ShaderManager>();
}


ShaderManager &Renderer::getShaderManager() {
    return *shaderManager;
}

shared_ptr <WindowManager> &Renderer::getWindowManager() {
    return windowManager;
}

TextureManager &Renderer::getTextureManager() {
    return textureManager;
}

void Renderer::initGLEW() {
    GLuint err;
    glewExperimental = GL_TRUE;
    if ((err = glewInit()) != GLEW_OK)
        throw EngineException(
                "Unable to initialize GLEW: " + std::string(reinterpret_cast<const char *>(glewGetErrorString(err))));
    
    Console::success("Glew Initialized!");
    
    // This makes our buffer swap synchronized with the monitor's vertical refresh
    // Parameters: 0 for immediate updates, 1 for updates synchronized with the vertical retrace, -1 for adaptive v-sync
    // More info: https://wiki.libsdl.org/SDL2/SDL_GL_SetSwapInterval
    if (SDL_GL_SetSwapInterval(1) == -1)
        throw EngineException(string("Unable activate v-sync (swap interval): ") + string(SDL_GetError()));
}

void Renderer::initGlContext() {
    
    
    // OpenGL context initialization over the SDL window, needed for using OpenGL functions
    if ((context = SDL_GL_CreateContext(windowManager->getWindow())) == nullptr)
        throw EngineException("Unable to create context: " + string(SDL_GetError()));
    else
        Console::success("GL context created!");
    
    // Tells OpenGL which size is the viewport where things are displayed
    // Must be called after creating the context
    glViewport(0, 0, windowManager->getWidth(), windowManager->getHeight());
}


Renderer::~Renderer() {
    SDL_GL_DeleteContext(context);
}


SDL_GLContext &Renderer::getContext() {
    return context;
}

void Renderer::setProjectionMatrix(glm::mat4 &projectionParam) {
    this->projection = projectionParam;
}

void Renderer::setViewMatrix(glm::mat4 &viewParam) {
    this->view = viewParam;
}
