#pragma once
#include "Component.h"
class RenderComponent:public Component
{
public:
    GLuint VAO;         // Vertex Array Object
    GLuint VBO;         // Vertex Buffer Object
    glm::mat4 model;    // Model matrix
};


