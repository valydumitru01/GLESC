/**************************************************************************************************
 * @file   GlobalAmbientLight.h
 * @author Valentin Dumitru
 * @date   2024-04-01
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "engine/subsystems/ingame-debug/EntityStatsManager.h"
#include "engine/subsystems/renderer/RendererTypes.h"

namespace GLESC::Render {
    class GlobalAmbientLight {
    public:
        /**
         * @brief Default constructor.
         */
        GlobalAmbientLight() = default;

        void setColor(const ColorRgb &color) {
            GlobalAmbientLight::color = color;
            dirty = true;
        }

        void setIntensity(float intensity) {
            GlobalAmbientLight::intensity = intensity;
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
    }; // class GlobalAmbientLight
}
