#pragma once

#include "glm/glm.hpp"

#include "Component.h"

struct CameraComponent : Component {
public:
    glm::mat4 view;
    float fov;
    float viewWidth;
    float viewHeight;
    float nearPlane;
    float farPlane;
};
