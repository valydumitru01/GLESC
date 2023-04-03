#pragma once

#include <SDL.h>
#include <GL/glew.h>
#include <memory>
#include "renderer/shaders/ShaderManager.h"
#include "renderer/TextureManager.h"
#include "renderer/WindowManager.h"
#include "renderer/RenderDebugger.h"

class Renderer {
public:
    Renderer(shared_ptr <WindowManager> windowManager);
    
    ~Renderer();
    
    /**
     * @brief Initialize GLEW
     * Must be called after the window is created
     */
    static void initGLEW();
    
    /**
     * @brief Initialize OpenGL
     * Must be called after the window is created
     */
    void initGL();
    
    
    void bindBuffers(GLuint VAO, GLuint VBO, GLuint EBO);
    
    shared_ptr <ShaderManager> getShaderManager();


private:
    void init();
    
    glm::mat4 projection;
    glm::mat4 view;
    unique_ptr <ShaderManager> shaderManager;
    unique_ptr <TextureManager> textureManager;
    shared_ptr <WindowManager> window;
    unique_ptr <RenderDebugger> debugger;
    
};