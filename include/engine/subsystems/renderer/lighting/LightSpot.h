/**************************************************************************************************
 * @file   LightSpot.h
 * @author Valentin Dumitru
 * @date   2024-03-31
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include <string>

#include "engine/subsystems/renderer/RendererTypes.h"

namespace GLESC::Render {
    struct LightSpot {
        LightSpot() = default;


        void setRadius(float radiusParam) {
            radius = radiusParam;
            dirty = true;
        }

        void setIntensity(float intensityParam) {
            intensity.set(intensityParam);
            dirty = true;
        }

        void setColor(const ColorRgb& colorParam) {
            color = colorParam;
            dirty = true;
        }


        float getIntensity() const { return intensity.get(); }
        const ColorRgb& getColor() const { return color; }
        [[nodiscard]] float getRadius() const { return radius; }

        [[nodiscard]] std::vector<EntityStatsManager::Value> getDebuggingValues() {
            std::vector<EntityStatsManager::Value> values;
            EntityStatsManager::Value intensityValue;
            intensityValue.name = "Intensity";
            intensityValue.data = reinterpret_cast<void*>(&intensity.getModifiable());
            intensityValue.type = EntityStatsManager::ValueType::FLOAT;
            intensityValue.isModifiable = true;
            intensityValue.valueDirty = &dirty;
            intensityValue.usesSlider = true;
            values.push_back(intensityValue);

            EntityStatsManager::Value colorValue;
            colorValue.name = "Color";
            colorValue.data = reinterpret_cast<void*>(&color);
            colorValue.type = EntityStatsManager::ValueType::VEC3F;
            colorValue.isModifiable = true;
            colorValue.valueDirty = &dirty;
            colorValue.usesSlider = true;
            colorValue.min = 0.0f;
            colorValue.max = 255.0f;
            values.push_back(colorValue);

            EntityStatsManager::Value radiusValue;
            radiusValue.name = "Radius";
            radiusValue.data = reinterpret_cast<void*>(&radius);
            radiusValue.type = EntityStatsManager::ValueType::FLOAT;
            radiusValue.isModifiable = true;
            radiusValue.valueDirty = &dirty;
            radiusValue.usesSlider = true;
            radiusValue.min = 0.0f;
            radiusValue.max = 100.0f;
            values.push_back(radiusValue);

            return values;
        }


        [[nodiscard]] bool& isDirty() const { return dirty; }
        void setClean() const { dirty = false; }


        [[nodiscard]] std::string toString() const {
            return "Intensity:" + intensity.toString() +
                " Color:" + color.toString() +
                " Radius:" + std::to_string(radius);
        }

    private:
        Intensity<float> intensity{1.0f};
        ColorRgb color{255.f, 255.f, 255.f};
        float radius{10.0f};
        mutable bool dirty{true};
    }; // class Light
} // namespace GLESC::Render
