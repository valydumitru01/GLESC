#include <utility>
#include "engine/subsystems/renderer/Renderer.h"
#include "engine/core/logger/Logger.h"

Renderer::Renderer(WindowManager &windowManager, GraphicsInterface &graphicsInterface) : graphicsInterface(
        graphicsInterface), windowManager(windowManager), shaderManager(), textureManager(), projection(), view() {
    
    // Set the projection matrix
    projection = calculateProjectionMatrix(45.0f, 0.1f, 100.0f, (float) windowManager.getWidth(),
                                           (float) windowManager.getHeight());
}


ShaderManager &Renderer::getShaderManager() {
    return shaderManager;
}

TextureManager &Renderer::getTextureManager() {
    return textureManager;
}


Renderer::~Renderer() {
    graphicsInterface.deleteContext();
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
Renderer::calculateProjectionMatrix(float fov, float nearPlane, float farPlane, float viewWidth, float viewHeight) {
    if (viewHeight == 0)
        throw EngineException("Unable to make projection matrix: viewHeight is 0");
    if (viewWidth == 0)
        throw EngineException("Unable to make projection matrix: viewWidth is 0");
    
    float aspectRatio = viewWidth / viewHeight;
    return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
}

glm::mat4 Renderer::calculateViewMatrix(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale) {
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

void Renderer::renderMesh(Mesh &mesh, const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale) {
    glm::mat4 model = calculateModelMatrix(position, rotation, scale);
    
    // Set the model matrix uniform in the shader
    // With OpenGL the multiplication must be done in reverse P x V x M
    getShaderManager().setMat4("mvp", model * getView() * getProjection());
    getShaderManager().setVec3("position", position);
    
    
}
void Renderer::start(){
    graphicsInterface.clear(ClearBits::Color, ClearBits::Depth, ClearBits::Stencil);
    graphicsInterface.clearColor(0.2f, 0.3f, 0.3f, 1.0f);
}
void Renderer::end(){
    swapBuffers();
}
void Renderer::swapBuffers() {
    graphicsInterface.getSwapBuffersFunc()(windowManager.getWindow());
}
