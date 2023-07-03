#include <utility>

#include "renderer/Renderer.h"

Renderer::Renderer(std::shared_ptr <WindowManager> &windowManager)
        : textureManager(), context(nullptr), projection(), view() {
    
    int width = windowManager->getWidth();
    int height = windowManager->getHeight();
    
    this->windowManager = std::move(windowManager);
    
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
    
    RenderDebugger::initDebugCallback();
    
    // Set the projection matrix
    projection = glm::perspective(glm::radians(45.0f), (float) width / (float) height, 0.1f, 100.0f);
    
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

glm::mat4 Renderer::getProjection() const {
    return projection;
}

glm::mat4 Renderer::getView() const {
    return view;
}

void Renderer::setView(const glm::mat4 &viewParam) {
    Renderer::view = viewParam;
}

void Renderer::setProjection(const glm::mat4 &projectionParam) {
    Renderer::projection = projectionParam;
}

glm::mat4
Renderer::makeProjectionMatrix(float fov, float nearPlane, float farPlane, float viewWidth, float viewHeight) {
    if (viewHeight == 0)
        throw EngineException("Unable to make projection matrix: viewHeight is 0");
    if (viewWidth == 0)
        throw EngineException("Unable to make projection matrix: viewWidth is 0");
    
    float aspectRatio = viewWidth / viewHeight;
    return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
}

glm::mat4 Renderer::makeViewMatrix(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale) {
    glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, scale);
    return glm::inverse(model);
}

glm::mat4 Renderer::calculateModelMatrix(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale) {
    glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, scale);
    return model;
}