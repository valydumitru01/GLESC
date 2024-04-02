/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "IComponent.h"
#include "engine/subsystems/physics/PhysicsTypes.h"

namespace GLESC::ECS {
    struct PhysicsComponent : IComponent {
        Mass mass{1.0F};
        Velocity velocity{};
        Force force{};
        Acceleration acceleration{};

        std::string toString() const override {
            return std::string("\n\tmass: ")
                + std::to_string(mass)
                + std::string("\n\tvelocity: ")
                + velocity.toString()
                + std::string("\n\tforce: ")
                + force.toString()
                + std::string("\n\tacceleration: ")
                + acceleration.toString();
        }

        std::string getName() const override {
            return "PhysicsComponent";
        }
    };
} // namespace GLESC::ECS
