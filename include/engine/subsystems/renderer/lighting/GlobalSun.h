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

        float& getModifiableIntensity() {
            return intensity.getModifiable();
        }

        ColorRgb& getModifiableColor() {
            return color;
        }

        Math::Direction& getModifiableDirection() {
            return direction;
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
            D_ASSERT_LESS_OR_EQUAL(intensity, 1.0f, "Intensity must be less or equal to 1.0f");
            D_ASSERT_GREATER_OR_EQUAL(intensity, 0.0f, "Intensity must be greater or equal to 0.0f");
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
