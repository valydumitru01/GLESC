#pragma once
#include "engine/plat-independence/graphics-device-interface/GraphicsInterface.h"
class OpenGLGDI : public GraphicsInterface
{
    void init();
    
    void draw();
    
    void update();
    
    void destroy() ;
    
    void setClearColor(float r, float g, float b, float a);
    
    void clear();
    
    void swapBuffers();
    
    void setViewport(int x, int y, int width, int height);
    
    void setWireframe(bool wireframe);
    
    void setDepthTest(bool depthTest);
    
    void setBlend(bool blend);
    
    void setBlendFunction(int sfactor, int dfactor);
    
    void setDepthFunction(int depthFunction);
    
    void setFaceCulling(bool faceCulling);
    
    void setFaceCullingMode(int faceCullingMode);
    
    void setFaceCullingWindingOrder(int faceCullingWindingOrder);
    
    void setViewport(int width, int height);
    
    void setViewport();
    
    void setViewport(glm::vec2 size);
    
    void setViewport(glm::vec2 position, glm::vec2 size);
    
    void setViewport(glm::vec4 viewport);
    
    void setViewport(glm::ivec4 viewport);
    
    void setViewport(glm::ivec2 position, glm::ivec2 size);
    
    void setViewport(glm::ivec2 size);
    
    void setViewport(glm::ivec2 position, glm::ivec2 size, float minDepth, float maxDepth);
    
    void setViewport(glm::vec2 position, glm::vec2 size, float minDepth, float maxDepth);
    
    void setViewport(glm::ivec4 viewport, float minDepth, float maxDepth);
    
    void setViewport(glm::vec4 viewport, float minDepth, float maxDepth);
    
    void setViewport(glm::ivec2 position, glm::ivec2 size, glm::vec2 depth);
    
    void setViewport(glm::vec2 position, glm::vec2 size, glm::vec2 depth);
    
    void useShader(const std::string &shaderName);
    
    void setShaderMat4(const std::string &name, const glm::mat4 &matrix);
    
    void setShaderVec3(const std::string &name, const glm::vec3 &vector);
    
    void setShaderInt(const std::string &name, int value);
    
    void bindMesh(const std::string &meshName);
    
    int loadTexture(const std::string &texturePath);
    
    void bindTexture(int textureID);
};