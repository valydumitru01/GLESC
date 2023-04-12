#pragma once

#include "Component.h"

#include <glm/glm.hpp>
class TransformComponent : public Component {
public:
    glm::vec3 position{0.f};
    glm::vec3 rotation{0.f};
    glm::vec3 scale{1.f};
    glm::mat4 model{1.f};
};