#pragma once
#include "glm/glm.hpp"
#include "engine/plat-independence/window/WindowManager.h"
#include <string>
#include <memory>
class GraphicsInterface {
public:
    virtual void init(std::shared_ptr <WindowManager> window) = 0;
    /**
     * @brief Set the Attributes for the Graphics Device Interface
     * @details This is where the configuration attributes for the GDI are set, such as the version,
     * the profile, the context flags, etc.
     */
    virtual void setAttributes()= 0;
    
    virtual void update() = 0;
    
    virtual void swapBuffers() = 0;
    
    virtual void setViewport(int x, int y, int width, int height) = 0;
    
    virtual void setViewport(int width, int height) = 0;
    
    virtual void setViewport() = 0;
    
    virtual void useShader(const std::string &shaderName) = 0;
    
    virtual void bindMesh(const std::string &meshName) = 0;
    
    virtual int loadTexture(const std::string &texturePath) = 0;
    
    virtual void bindTexture(int textureID) = 0;
    
    virtual ~GraphicsInterface() = default;
private:
    virtual void createContext() = 0;
};