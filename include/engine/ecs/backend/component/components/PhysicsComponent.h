/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "engine/ecs/backend/component/Component.h"
#include "engine/core/math/debugger/MathDebugger.h"

struct PhysicsComponent : public Component {
    float mass{1.0F};
    glm::vec3 velocity{};
    glm::vec3 force{};
    glm::vec3 acceleration{};
    
    [[nodiscard]] std::string toString() const override {
        return "PhysicsComponent:"
        + std::string("\n\tmass: ")
        + std::to_string(mass)
        + std::string("\n\tvelocity: ")
        + GLESC::toString(velocity)
        + std::string("\n\tforce: ")
        + GLESC::toString(force)
        + std::string("\n\tacceleration: ")
        + GLESC::toString(acceleration);
    }
};

