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
    Vec3F velocity{};
    Vec3F force{};
    Vec3F acceleration{};
    
    std::string toString() override {
        return "PhysicsComponent:"
               + std::string("\n\tmass: ")
               + std::to_string(mass)
               + std::string("\n\tvelocity: ")
               + velocity.toString()
               + std::string("\n\tforce: ")
               + force.toString()
               + std::string("\n\tacceleration: ")
               + acceleration.toString();
    }
};

