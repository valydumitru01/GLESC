#include "core/components/Transform.h"

Transform::Transform()
{
    _transform = glm::mat4(1.0f);

    glm::vec3 position = glm::vec3(1.0f);
    glm::vec3 rotation = glm::vec3(1.0f);
    glm::vec3 scale = glm::vec3(1.0f);
}

void Transform::move(glm::vec3 _towards, float speed){

}

void Transform::rotate(glm::vec3 _rotation){

}
void Transform::rotate(float x, float y, float z){

}
/*
void Transform::scale(glm::vec3 _scale){
    glm::scale(transform,_scale);
}
void Transform::scale(float x, float y, float z){

}*/