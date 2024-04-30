/**************************************************************************************************
 * @file   SunComponent.h
 * @author Valentin Dumitru
 * @date   2024-04-30
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "IComponent.h"
#include "engine/subsystems/renderer/lighting/GlobalSun.h"

namespace GLESC::ECS {
    class SunComponent : public IComponent {
    public:
        GLESC::Render::GlobalSun sun;

        std::string toString() const override {
            return sun.toString();
        }

        std::string getName() const override {
            return "SunComponent";
        }

        void setDebuggingValues() override {
            EntityStatsManager::Value intensityValue;
            intensityValue.name = "Intensity";
            intensityValue.data = reinterpret_cast<void*>(&sun.getModifiableIntensity());
            intensityValue.type = EntityStatsManager::ValueType::FLOAT;
            intensityValue.isModifiable = true;
            intensityValue.usesSlider = true;
            intensityValue.valueDirty = &sun.isDirty();
            intensityValue.min = 0.0f;
            intensityValue.max = 1.0f;
            values.push_back(intensityValue);

            EntityStatsManager::Value colorValue;
            colorValue.name = "Color";
            colorValue.data = reinterpret_cast<void*>(&sun.getModifiableColor());
            colorValue.type = EntityStatsManager::ValueType::VEC3F;
            colorValue.isModifiable = true;
            colorValue.usesSlider = true;
            colorValue.valueDirty = &sun.isDirty();
            colorValue.min = 0.0f;
            colorValue.max = 255.0f;
            values.push_back(colorValue);

            EntityStatsManager::Value directionValue;
            directionValue.name = "Direction";
            directionValue.data = reinterpret_cast<void*>(&sun.getModifiableDirection());
            directionValue.type = EntityStatsManager::ValueType::VEC3F;
            directionValue.isModifiable = true;
            directionValue.usesSlider = true;
            directionValue.valueDirty = &sun.isDirty();
            directionValue.min = -1.0f;
            directionValue.max = 1.0f;
            values.push_back(directionValue);
        }
    }; // class SunComponent
} // namespace GLESC::ECS
