/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "IComponent.h"
#include "engine/core/math/debugger/MathDebugger.h"

struct PhysicsComponent : public IComponent {
    float mass{1.0F};
    glm::vec3 velocity{};
    glm::vec3 force{};
    glm::vec3 acceleration{};
    
    std::string toString() override {
        return "PhysicsComponent:"
               + std::string("\n\tmass: ")
               + std::to_string(mass)
               + std::string("\n\tvelocity: ")
               + GLESC::glmToString(velocity)
               + std::string("\n\tforce: ")
               + GLESC::glmToString(force)
               + std::string("\n\tacceleration: ")
               + GLESC::glmToString(acceleration);
    }
};

