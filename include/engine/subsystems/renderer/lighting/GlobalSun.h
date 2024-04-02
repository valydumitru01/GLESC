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

        GlobalSun(float intensity, const Rgb& color, const Math::Direction& direction){
            setIntensity(intensity);
            setColor(color);
            setDirection(direction);
        }

        float getIntensity() const {
            return intensity;
        }

        Rgb getColor() const {
            return color;
        }

        Math::Direction getDirection() const {
            return direction;
        }

        void setIntensity(float intensity) {
            D_ASSERT_LESS_OR_EQUAL(intensity, 1.0f, "Intensity must be less or equal to 1.0f");
            D_ASSERT_GREATER_OR_EQUAL(intensity, 0.0f, "Intensity must be greater or equal to 0.0f");
            this->intensity = intensity;
        }

        void setColor(const Rgb& color) {
            this->color = color;
        }

        void setDirection(const Math::Direction& direction) {
            D_ASSERT_TRUE(direction.isNormalized(), "Direction must be normalized");
            this->direction = direction;
        }

    protected:

    private:
        float intensity{1.0f};
        Rgb color{255, 255, 255};
        Math::Direction direction{0.0f, 0.0f, 1.0f};
    }; // class GlobalSun
}
