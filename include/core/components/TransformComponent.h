#pragma once
#include "Component.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class TransformComponent :public Component
{
public:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

};