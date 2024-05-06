/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "../../backend/component/IComponent.h"
#include "engine/subsystems/transform/Transform.h"

namespace GLESC::ECS {
    struct TransformComponent : IComponent {
        Transform::Transform transform;

        std::string toString() const override {
            return transform.toString();
        }

        std::string getName() const override {
            return "TransformComponent";
        }

        void setDebuggingValues() override {
            for (auto& value : transform.getDebuggingValues()) {
                values.push_back(value);
            }
        }
    };
} // namespace GLESC::ECS
