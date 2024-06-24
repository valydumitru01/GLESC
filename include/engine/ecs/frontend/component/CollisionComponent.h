/**************************************************************************************************
 * @file   CollisionComponent.h
 * @author Valentin Dumitru
 * @date   06/06/2024
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "engine/ecs/backend/component/IComponent.h"
#include "engine/subsystems/physics/Collider.h"

namespace GLESC::ECS {
    class CollisionComponent : public IComponent {
    public:
        Physics::Collider collider;

        std::string toString() const override {
            return collider.toString();
        }

        std::string getName() const override {
            return "CollisionComponent";
        }
#ifndef NDEBUG_GLESC
        void setDebuggingValues() override {
            for (auto& value : collider.getDebuggingValues()) {
                values.push_back(value);
            }
        }

        void setUpdatedDebuggingValues() override {
            for (auto& value : collider.getUpdatedDebuggingValues()) {
                updatedValues.push_back(value);
            }
        }
#endif
    }; // class CollisionComponent
}
