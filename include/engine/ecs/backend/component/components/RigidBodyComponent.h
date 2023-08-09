/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/ecs/backend/component/Component.h"
#include "glm/glm.hpp"

struct RigidBodyComponent : public Component {
    float mass;
    glm::vec3 velocity;
    glm::vec3 force;
    
    explicit RigidBodyComponent(float m = 1.0F) : mass(m), velocity(0.0F), force(0.0F) {}
};