/**************************************************************************************************
 * @file   GlobalSun.h
 * @author Valentin Dumitru
 * @date   2024-04-01
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "engine/core/math/geometry/GeometryTypes.h"
#include "engine/subsystems/renderer/RendererTypes.h"

namespace GLESC::Render {
    class GlobalSun {
    public:
        /**
         * @brief Default constructor.
         */
        GlobalSun() = default;

        GlobalSun(float intensity, const ColorRgb& color, const Math::Direction& direction) :
            intensity(intensity), color(color), direction(direction) {
        }

        float getIntensity() const {
            return intensity.get();
        }

        ColorRgb getColor() const {
            return color;
        }

        Math::Direction getDirection() const {
            return direction;
        }


        void setIntensity(float intensity) {
            this->intensity = Intensity(intensity);
            setDirty();
        }

        void setColor(const ColorRgb& color) {
            this->color = color;
            setDirty();
        }

        void setDirection(const Math::Direction& direction) {
            this->direction = direction;
            setDirty();
        }

        void setDirty() const {
            dirty = true;
        }

        void setClean() const {
            dirty = false;
        }


        bool& isDirty() const {
            return dirty;
        }

        [[nodiscard]] std::vector<EntityStatsManager::Value> getDebuggingValues() {
            std::vector<EntityStatsManager::Value> values;
            EntityStatsManager::Value intensityValue;
            intensityValue.name = "Intensity";
            intensityValue.data = reinterpret_cast<void*>(&intensity.getModifiable());
            intensityValue.type = EntityStatsManager::ValueType::FLOAT;
            intensityValue.isModifiable = true;
            intensityValue.usesSlider = true;
            intensityValue.valueDirty = &dirty;
            intensityValue.min = 0.0f;
            intensityValue.max = 1.0f;
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

            EntityStatsManager::Value directionValue;
            directionValue.name = "Direction";
            directionValue.data = reinterpret_cast<void*>(&direction);
            directionValue.type = EntityStatsManager::ValueType::VEC3F;
            directionValue.isModifiable = true;
            directionValue.usesSlider = true;
            directionValue.valueDirty = &dirty;
            directionValue.min = -1.0f;
            directionValue.max = 1.0f;
            values.push_back(directionValue);

            return values;
        }

        std::string toString() const {
            return "Intensity: " + std::to_string(intensity.get()) +
                " Color: " + color.toString() +
                " Direction: " + direction.toString();
        }

    private:
        Intensity<float> intensity{1.0f};
        Math::Direction direction{0.f, -1.0f, 0.f};
        ColorRgb color{255, 255, 255};
        /**
         * @brief Dirty flag for the sun
         * @details If the sun is dirty, it will be updated in the shader
         */
        mutable bool dirty = true;
    }; // class GlobalSun
}
