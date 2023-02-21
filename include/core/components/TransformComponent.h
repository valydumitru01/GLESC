#pragma once
#include "Component.h"
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class TransformComponent 
{
    friend class TFGL;
public:
    TransformComponent();

    void move(glm::vec3 _towards, float speed);

    void rotate(glm::vec3 _rotation);
    void rotate(float x, float y, float z);

    void scale(glm::vec3 _scale);
    void scale(float x, float y, float z);

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    glm::vec3 front;
    glm::vec3 up;

private:
    glm::mat4 getTansformMat();

};