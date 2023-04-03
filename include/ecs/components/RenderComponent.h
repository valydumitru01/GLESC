#pragma once

#include <GL/glew.h>

#include "Component.h"

class RenderComponent : public Component {
    RenderComponent() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        model = glm::mat4(1.0f);
    }

public:
    /**
     * @brief The vertex array object
     * Contains the information a vertex stores
     */
    GLuint VAO{};
    /**
     * @brief The vertex buffer object
     * Contains the vertices of the object
     *
     *
     */
    GLuint VBO{};
    /**
     * @brief The element buffer object
     * Contains the indices of the vertices
     */
    GLuint EBO{};
    /**
     * @brief The model matrix
     * Contains the position, rotation and scale of the object in the world
     * It is used to transform the vertices of the object
     */
    glm::mat4 model{};
};


