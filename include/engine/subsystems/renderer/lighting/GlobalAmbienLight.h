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
        float intensity{1.0f};
    }; // class GlobalAmbienLight
}
