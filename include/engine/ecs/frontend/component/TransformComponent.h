/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "IComponent.h"
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
            EntityStatsManager::Value positionValue;
            positionValue.name = "Position";
            positionValue.data = reinterpret_cast<void*>(&transform.getModifiablePosition());
            positionValue.type = EntityStatsManager::ValueType::VEC3F;
            positionValue.isModifiable = true;
            positionValue.usesSlider = false;
            values.push_back(positionValue);

            EntityStatsManager::Value rotationValue;
            rotationValue.name = "Rotation";
            rotationValue.data = reinterpret_cast<void*>(&transform.getModifiableRotation());
            rotationValue.type = EntityStatsManager::ValueType::VEC3F;
            rotationValue.isModifiable = true;
            rotationValue.usesSlider = true;
            rotationValue.min = -360.0f;
            rotationValue.max = 360.0f;
            values.push_back(rotationValue);

            EntityStatsManager::Value scaleValue;
            scaleValue.name = "Scale";
            scaleValue.data = reinterpret_cast<void*>(&transform.getModifiableScale());
            scaleValue.type = EntityStatsManager::ValueType::VEC3F;
            scaleValue.isModifiable = true;
            scaleValue.usesSlider = true;
            scaleValue.min = -10.0f;
            scaleValue.max = 10.0f;
            values.push_back(scaleValue);
        }
    };
} // namespace GLESC::ECS
