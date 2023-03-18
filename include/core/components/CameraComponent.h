#pragma once

#include "Component.h"
#include "glm.hpp"

class CameraComponent : Component {
public:
    glm::mat4 view;
	float fov;
    float viewWidth;
    float viewHeight;
    float nearPlane;
	float farPlane;


};
