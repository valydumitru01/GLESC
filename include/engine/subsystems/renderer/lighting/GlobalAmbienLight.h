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
#include "engine/subsystems/ingame-debug/EntityStatsManager.h"
#include "engine/subsystems/renderer/RendererTypes.h"

namespace GLESC::Render {
    class GlobalAmbienLight {
    public:
        /**
         * @brief Default constructor.
         */
        GlobalAmbienLight() = default;

        void setColor(const ColorRgb &color) {
            GlobalAmbienLight::color = color;
            dirty = true;
        }

        void setIntensity(float intensity) {
            GlobalAmbienLight::intensity = intensity;
            dirty = true;
        }

        [[nodiscard]] float getIntensity() const {
            return intensity;
        }


        [[nodiscard]] const ColorRgb& getColor() const {
            return color;
        }

        void setClean() const {
            dirty = false;
        }

        [[nodiscard]] bool& isDirty() const {
            return dirty;
        }
        [[nodisacrd]] std::vector<EntityStatsManager::Value> getDebuggingValues();

    private:
        ColorRgb color{255, 255, 255};
        /**
         * @brief Intensity of the light.
         * @details It should be between 0 and 1. The standard is to set it somewhat low, because its the light when
         * there is no other light source, so the player can see something.
         */
        float intensity{0.1f};
        /**
         * @brief If the light is dirty, it should be resend to the shader.
         */
        mutable bool dirty{true};
    }; // class GlobalAmbienLight
}
