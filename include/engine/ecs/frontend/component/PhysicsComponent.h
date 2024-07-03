/**************************************************************************************************
 * @file   PhysicsComponent.h
 * @author Valentin Dumitru
 * @date   2024-04-17
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

#pragma once

#include "engine/ecs/backend/component/IComponent.h"
#include "engine/subsystems/physics/Physics.h"
#include "engine/subsystems/physics/Collider.h"
#include "engine/subsystems/physics/PhysicsTypes.h"
#include "engine/subsystems/transform/Transform.h"

namespace GLESC::ECS {
    struct PhysicsComponent : public IComponent {
        Physics::Physics physics;
        /**
         * @details This transform is the old transform before applying the physics
         * It can be used to change the behavior of the physics (such as collisions)
         */
        Transform::Transform oldTransform;


        std::string getName() const override {
            return "PhysicsComponent";
        }

        std::string toString() const override {
            return physics.toString();
        }

#ifndef NDEBUG_GLESC
        void setDebuggingValues() override {
            for (auto& value : physics.getDebuggingValues()) {
                values.push_back(value);
            }
        }

        void setUpdatedDebuggingValues() override {
            for (auto& value : physics.getUpdatedDebuggingValues()) {
                updatedValues.push_back(value);
            }
        }
#endif
    };
} // namespace GLESC::ECS
