#include <utility>
#include "engine/core/renderer/Renderer.h"
#include "engine/core/logger/Logger.h"
Renderer::Renderer(const std::shared_ptr <WindowManager>& windowManager)
        : textureManager(), context(nullptr), projection(), view() {
    
    int width = windowManager->getWidth();
    int height = windowManager->getHeight();
    
    this->windowManager = std::move(windowManager);
    
    initGlContext();
    

    RenderDebugger::initDebugCallback();
    
    // Set the projection matrix
    projection = makeProjectionMatrix(45.0f, 0.1f, 100.0f, (float)width, (float)height);
    
    shaderManager = make_unique <ShaderManager>();
}


ShaderManager &Renderer::getShaderManager() {
    return *shaderManager;
}

std::shared_ptr <WindowManager> &Renderer::getWindowManager() {
    return windowManager;
}

TextureManager &Renderer::getTextureManager() {
    return textureManager;
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

void
Renderer::renderMesh(Mesh& mesh, const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale) {

}
