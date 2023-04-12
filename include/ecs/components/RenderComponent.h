#pragma once

#include <GL/glew.h>

#include <utility>

#include "Component.h"
#include "renderer/Mesh.h"

class RenderComponent : public Component {

public:
    explicit RenderComponent() : textureID(0), color(glm::vec4(1.0f)) {
    }
    
    GLuint textureID;
    std::string texturePath;
    
    /**
     * @brief The mesh of the object
     * Contains the vertices and indices of the object
     * The data stored in a vertex is position, color, texture coordinates and normal
     */
    Mesh mesh;
    
    glm::vec4 color;
};


