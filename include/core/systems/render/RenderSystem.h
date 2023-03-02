#pragma once
#include <iostream>
#include <unordered_map>
#include <vector> 

#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include <SDL2/SDL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "CoordinateSystem.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "../Debugger.h"

class RenderSystem : System{
public:
    RenderSystem(short height, short width,ShaderManager* shaderManager,CoordinateSystem* coordSystem);
    ~RenderSystem();
    /**
     * @brief Initialize the renderer
     * 
     * @param height 
     * @param width 
     */
    void init();
    /**
     * @brief Render the content of the screen.
     * Must be called every frame
     * 
     */
    void update();

private:
    /**
     * @brief Create a Shader Attributes object
     * 
     */
    void createShaderAttributes();
    /**
     * @brief Create VBO, VAO and EBO buffers
     * 
     */
    void createBuffers();
    /**
     * @brief Generate a texture
     * 
     * @param texture ID to the texture object
     * @param path 
     */
    void generateTexture(GLuint texture, const char* path);
    /**
     * @brief Iterate over the textures and generate them calling generateTexture()
     * 
     */
    void generateTextures();
    
    ShaderManager* shaderManager;
    CoordinateSystem* coordSystem;
    std::unordered_map<GLuint, const char *> textures;
    GLuint VBO, VAO, EBO;

    unsigned int texture1;
    unsigned int texture2;
    std::vector<float> vertices;
    std::vector<int> indices;
    glm::mat4 trans;
    glm::mat4 trans2;
    
    unsigned int transformLoc;
    
};