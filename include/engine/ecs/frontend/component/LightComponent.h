/**************************************************************************************************
 * @file   LightComponent.h
 * @author Valentin Dumitru
 * @date   2024-03-31
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "engine/ecs/frontend/component/IComponent.h"
#include "engine/subsystems/renderer/lighting/LightSpot.h"

namespace GLESC::ECS {
    struct LightComponent : IComponent {
        Render::LightSpot light;

        [[nodiscard]] std::string getName() const override {
            return "LightComponent";
        }

        [[nodiscard]] std::string toString() const override {
            return light.toString();
        }

        void setDebuggingValues() override {

            EntityStatsManager::Value intensityValue;
            intensityValue.name = "Intensity";
            intensityValue.data = reinterpret_cast<void*>(&light.intensity.getModifiable());
            intensityValue.type = EntityStatsManager::ValueType::FLOAT;
            intensityValue.isModifiable = true;
            intensityValue.usesSlider = true;
            values.push_back(intensityValue);

            EntityStatsManager::Value colorValue;
            colorValue.name = "Color";
            colorValue.data = reinterpret_cast<void*>(&light.color);
            colorValue.type = EntityStatsManager::ValueType::VEC3F;
            colorValue.isModifiable = true;
            colorValue.usesSlider = true;
            colorValue.min = 0.0f;
            colorValue.max = 255.0f;
            values.push_back(colorValue);

        }
    }; // struct LightComponent
}
