#include "core/components/TransformComponent.h"
TransformComponent::TransformComponent():
position (glm::vec3(0.0f, 0.0f, 3.0f)),
up ( glm::vec3(0.0f, 1.0f, 0.0f)),
front ( glm::vec3(0.0f, 0.0f, -1.0f))
{

}

void TransformComponent::move(glm::vec3 _towards, float speed){

}

void TransformComponent::rotate(glm::vec3 _rotation){

}
void TransformComponent::rotate(float x, float y, float z){

}

glm::mat4 TransformComponent::getTansform()
{

}
/*
void Transform::scale(glm::vec3 _scale){
    glm::scale(transform,_scale);
}
void Transform::scale(float x, float y, float z){

}*/