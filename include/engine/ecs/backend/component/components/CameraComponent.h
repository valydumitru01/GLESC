/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "glm/glm.hpp"

#include "engine/ecs/backend/component/Component.h"

struct CameraComponent : Component {
public:
    glm::mat4 view;
    float fov;
    float viewWidth;
    float viewHeight;
    float nearPlane;
    float farPlane;
};
