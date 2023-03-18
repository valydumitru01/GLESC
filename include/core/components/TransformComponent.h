#pragma once
#include "Component.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class TransformComponent :public Component
{
public:
    glm::mat4 tranformMatrix{1.f};
    static void translate(TransformComponent* transform,glm::vec3 speed){
        glm::translate(transform->tranformMatrix, glm::vec3(0.5f, -0.5f, 0.0f));
    }
    static void lookAt(){

    }
};