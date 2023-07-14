#pragma once

#include "engine/plat-independence/graphics-device-interface/GraphicsInterface.h"

class OpenGLGDI : public GraphicsInterface {
    void init(std::shared_ptr <WindowManager> window) override;
    
    /**
     * @brief Attributes that configure OpenGL
     * @details This is where the configuration attributes for the GDI are set, such as the OpenGL version,
     * @see https://wiki.libsdl.org/SDL_GLattr
     */
    void setAttributes() override;
    
    void update() override;
    
    void swapBuffers() override;
    
    void setViewport(int x, int y, int width, int height) override;
    
    void setViewport(int width, int height) override;
    
    void setViewport() override;
    
    void useShader(const std::string &shaderName) override;
    
    void bindMesh(const std::string &meshName) override;
    
    int loadTexture(const std::string &texturePath) override;
    
    void bindTexture(int textureID) override;

private:
    
    void createContext() override;
    
    static void setGlAttribute(SDL_GLattr attrib, int val);
    
    SDL_GLContext context;
    
    std::shared_ptr <SDL_Window> window;
};