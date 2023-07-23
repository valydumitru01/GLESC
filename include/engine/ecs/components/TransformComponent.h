#pragma once

#include "Component.h"

#include "glm/glm.hpp"
struct TransformComponent : public Component {
    glm::vec3 position{0.f};
    glm::vec3 rotation{0.f};
    glm::vec3 scale{1.f};
};