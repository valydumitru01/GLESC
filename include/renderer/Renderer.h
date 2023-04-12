#pragma once

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "renderer/shaders/ShaderManager.h"
#include "renderer/TextureManager.h"
#include "renderer/WindowManager.h"
#include "renderer/RenderDebugger.h"
#include "exceptions/EngineException.h"
#include "renderer/GlWrapper.h"


class Renderer {
public:
    explicit Renderer(shared_ptr <WindowManager> &windowManager);
    
    ~Renderer();
    
    /**
     * @brief Initialize GLEW
     * Must be called after the window is created and the OpenGL context is initialized
     */
    static void initGLEW();
    
    
    /**
     * @brief Get the shader manager object
     * @return ShaderManager& The shader manager object
     */
    ShaderManager & getShaderManager();
    
    /**
     * @brief Get the Window Manager object
     * @return WindowManager& The Window Manager object
     */
    shared_ptr <WindowManager> &getWindowManager();
    
    /**
     * @brief Get the Texture Manager object
     * @return TextureManager& The Texture Manager object
     */
    TextureManager &getTextureManager();
    
    /**
     * @brief Set the projection matrix
     * @param projectionParam The projection matrix
     */
    void setProjectionMatrix(glm::mat4 &projectionParam);
    
    /**
     * @brief Set the view matrix
     * @details The view matrix is the inverse of the camera's model matrix
     * @param viewParam The view matrix
     */
    void setViewMatrix(glm::mat4 &viewParam);
    
    
    /**
     * @brief Initialize OpenGL context
     * Must be called after the window is created
     */
    void initGlContext();
    
    SDL_GLContext &getContext();

private:
    /**
     * @brief Projection matrix
     *
     */
    glm::mat4 projection;
    /**
     * @brief View matrix
     *
     */
    glm::mat4 view;
    /**
     * @brief Shader manager
     *
     */
    unique_ptr <ShaderManager> shaderManager;
    /**
     * @brief Window manager
     *
     */
    shared_ptr <WindowManager> windowManager;
    /**
     * @brief Texture manager
     *
     */
    TextureManager textureManager;
    /**
     * @brief Render debugger
     *
     */
    RenderDebugger debugger;
    /**
     * @brief OpenGL context
     *
     */
    SDL_GLContext context;
    
};