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

class Renderer {
public:
    Renderer();
    ~Renderer();
    void init(short height, short width);
    void render();

private:
    void setGlAttributes();
    void createShaderAttributes();
    void createBuffers();
    void generateTexture(GLuint texture, const char* path);
    void generateTextures();
    CoordinateSystem* coordSystem;
    ShaderManager* shaderManager;
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