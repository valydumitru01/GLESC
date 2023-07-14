#pragma once

#include "GL/glew.h"

#include <utility>

#include "Component.h"
#include "engine/core/renderer/Mesh.h"

class RenderComponent : public Component {

public:
    explicit RenderComponent() : textureID(0), mesh(){
    }
    ~RenderComponent(){
        glDeleteTextures(1, &textureID);
        mesh.destroy();
    }
    /**
     * @brief Texture ID of the object
     * @details This value is used to bind the texture to the object
     */
    GLuint textureID;
    std::string texturePath;
    /**
     * @brief The mesh of the object
     * Contains the vertices and indices of the object
     * The data stored in a vertex is position, color, texture coordinates and normal
     */
    Mesh mesh;
    
};


