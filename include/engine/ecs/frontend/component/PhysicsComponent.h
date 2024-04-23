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

        void setDebuggingValues() override {
            EntityStatsManager::Value massValue;
            massValue.name = "Mass";
            massValue.data = reinterpret_cast<void*>(&mass);
            massValue.type = EntityStatsManager::ValueType::FLOAT;
            massValue.isModifiable = true;
            massValue.usesSlider = false;
            values.push_back(massValue);

            EntityStatsManager::Value velocityValue;
            velocityValue.name = "Velocity";
            velocityValue.data = reinterpret_cast<void*>(&velocity);
            velocityValue.type = EntityStatsManager::ValueType::VEC3F;
            velocityValue.isModifiable = true;
            velocityValue.usesSlider = false;
            values.push_back(velocityValue);

            EntityStatsManager::Value forceValue;
            forceValue.name = "Force";
            forceValue.data = reinterpret_cast<void*>(&force);
            forceValue.type = EntityStatsManager::ValueType::VEC3F;
            forceValue.isModifiable = true;
            values.push_back(forceValue);

            EntityStatsManager::Value accelerationValue;
            accelerationValue.name = "Acceleration";
            accelerationValue.data = reinterpret_cast<void*>(&acceleration);
            accelerationValue.type = EntityStatsManager::ValueType::VEC3F;
            accelerationValue.isModifiable = true;
            accelerationValue.usesSlider = true;
            values.push_back(accelerationValue);
        }
    };
} // namespace GLESC::ECS
