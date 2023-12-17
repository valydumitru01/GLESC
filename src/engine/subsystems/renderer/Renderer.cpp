
#include "engine/subsystems/renderer/math/RenderMath.h"
#include "engine/subsystems/renderer/Renderer.h"
#include "engine/subsystems/renderer/mesh/Vertex.h"

GLESC::Renderer::Renderer(GLESC::WindowManager &windowManager) :
        windowManager(windowManager), shader(Shader("Shader.glsl")) {
    
    // Set the projection matrix
    projection = RenderMath::calculateProjectionMatrix(45.0f, 0.1f, 100.0f,
                                                       static_cast<float>(windowManager
                                                   .getWindowSize().width),
                                                       static_cast<float>(windowManager
                                                   .getWindowSize().height));
    
}

GLESC::Renderer::~Renderer() {
    
    getGAPI().deleteContext();
    
}
