#include "glm/glm.hpp"
#include <string>
class GraphicsInterface {
public:
    virtual void init() = 0;
    
    virtual void draw() = 0;
    
    virtual void update() = 0;
    
    virtual void destroy() = 0;
    
    virtual void setClearColor(float r, float g, float b, float a) = 0;
    
    virtual void clear() = 0;
    
    virtual void swapBuffers() = 0;
    
    virtual void setViewport(int x, int y, int width, int height) = 0;
    
    virtual void setWireframe(bool wireframe) = 0;
    
    virtual void setDepthTest(bool depthTest) = 0;
    
    virtual void setBlend(bool blend) = 0;
    
    virtual void setBlendFunction(int sfactor, int dfactor) = 0;
    
    virtual void setDepthFunction(int depthFunction) = 0;
    
    virtual void setFaceCulling(bool faceCulling) = 0;
    
    virtual void setFaceCullingMode(int faceCullingMode) = 0;
    
    virtual void setFaceCullingWindingOrder(int faceCullingWindingOrder) = 0;
    
    virtual void setViewport(int width, int height) = 0;
    
    virtual void setViewport() = 0;
    
    virtual void setViewport(glm::vec2 size) = 0;
    
    virtual void setViewport(glm::vec2 position, glm::vec2 size) = 0;
    
    virtual void setViewport(glm::vec4 viewport) = 0;
    
    virtual void setViewport(glm::ivec4 viewport) = 0;
    
    virtual void setViewport(glm::ivec2 position, glm::ivec2 size) = 0;
    
    virtual void setViewport(glm::ivec2 size) = 0;
    
    virtual void setViewport(glm::ivec2 position, glm::ivec2 size, float minDepth, float maxDepth) = 0;
    
    virtual void setViewport(glm::vec2 position, glm::vec2 size, float minDepth, float maxDepth) = 0;
    
    virtual void setViewport(glm::ivec4 viewport, float minDepth, float maxDepth) = 0;
    
    virtual void setViewport(glm::vec4 viewport, float minDepth, float maxDepth) = 0;
    
    virtual void setViewport(glm::ivec2 position, glm::ivec2 size, glm::vec2 depth) = 0;
    
    virtual void setViewport(glm::vec2 position, glm::vec2 size, glm::vec2 depth) = 0;
    
    virtual void useShader(const std::string &shaderName) = 0;
    
    virtual void setShaderMat4(const std::string &name, const glm::mat4 &matrix) = 0;
    
    virtual void setShaderVec3(const std::string &name, const glm::vec3 &vector) = 0;
    
    virtual void setShaderInt(const std::string &name, int value) = 0;
    
    virtual void bindMesh(const std::string &meshName) = 0;
    
    virtual int loadTexture(const std::string &texturePath) = 0;
    
    virtual void bindTexture(int textureID) = 0;
    
    virtual ~GraphicsInterface() = default;
    
};