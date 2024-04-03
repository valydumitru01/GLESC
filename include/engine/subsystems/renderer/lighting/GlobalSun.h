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

        GlobalSun(float intensity, const Rgb& color, const Transform::Transform& transform){
            setIntensity(intensity);
            setColor(color);
            setTransform(transform);
        }

        float getIntensity() const {
            return intensity;
        }

        Rgb getColor() const {
            return color;
        }

        void setTransform(const Transform::Transform& transform) {
            this->transform = transform;
        }

        Transform::Transform getTransform() const {
            return transform;
        }

        void setIntensity(float intensity) {
            D_ASSERT_LESS_OR_EQUAL(intensity, 1.0f, "Intensity must be less or equal to 1.0f");
            D_ASSERT_GREATER_OR_EQUAL(intensity, 0.0f, "Intensity must be greater or equal to 0.0f");
            this->intensity = intensity;
        }

        void setColor(const Rgb& color) {
            this->color = color;
        }


    private:
        float intensity{1.0f};
        Rgb color{255, 255, 255};
        Transform::Transform transform;
    }; // class GlobalSun
}
