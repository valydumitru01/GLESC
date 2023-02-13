#pragma once
#include "Component.h"
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class TransformComponent
{
public:
    TransformComponent();

    void move(glm::vec3 _towards, float speed);

    void rotate(glm::vec3 _rotation);
    void rotate(float x, float y, float z);

    void scale(glm::vec3 _scale);
    void scale(float x, float y, float z);

    glm::mat4 getTransform(){return _transform;}
    glm::vec3 getPosition(){return _position;}
    glm::vec3 getRotation(){return _rotation;}
    glm::vec3 getScale(){return _scale;}
    

private:
    glm::mat4 _transform;
    glm::vec3 _position;
    glm::vec3 _rotation;
    glm::vec3 _scale;
};