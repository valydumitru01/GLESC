/**************************************************************************************************
 * @file   GlobalAmbienLight.h
 * @author Valentin Dumitru
 * @date   2024-04-01
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "engine/subsystems/renderer/RendererTypes.h"

namespace GLESC::Render {
    class GlobalAmbienLight {
    public:
        /**
         * @brief Default constructor.
         */
        GlobalAmbienLight() = default;

        void setColor(const Rgb &color) {
            GlobalAmbienLight::color = color;
        }

        void setIntensity(float intensity) {
            GlobalAmbienLight::intensity = intensity;
        }

        [[nodiscard]] float getIntensity() const {
            return intensity;
        }

        [[nodiscard]] Rgb getColor() const {
            return color;
        }

    protected:

    private:
        Rgb color{255, 255, 255};
        /**
         * @brief Intensity of the light.
         * @details It should be between 0 and 1. The standard is to set it somewhat low, because its the light when
         * there is no other light source, so the player can see something.
         */
        float intensity{0.1f};
    }; // class GlobalAmbienLight
}
