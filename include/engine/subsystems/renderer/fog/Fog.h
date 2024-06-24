/**************************************************************************************************
 * @file   Fog.h
 * @author Valentin Dumitru
 * @date   2024-05-03
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include <string>

#include "engine/subsystems/ingame-debug/EntityStatsManager.h"
#include "engine/subsystems/renderer/RendererTypes.h"

namespace GLESC::Render {
    class Fog {
    public:
        Fog() = default;

        void setDensity(float density) {
            this->density.set(density);
        }

        void setColor(const ColorRgb& color) {
            this->color = color;
        }

        void setEnd(float end) {
            this->end = end;
        }

        [[nodiscard]] float getDensity() const {
            return density.get();
        }


        [[nodiscard]] float getEnd() const {
            return end;
        }

        [[nodiscard]] const ColorRgb& getColor() const {
            return color;
        }

#ifndef NDEBUG_GLESC

    [[nodisacrd]] std::vector<EntityStatsManager::Value> getDebuggingValues();
#endif


        [[nodiscard]] std::string toString() const ;

    private:
        GLESC::Render::Intensity<float> density{1.0f};
        float end = 300.0f;
        GLESC::Render::ColorRgb color{255.f, 255.f, 255.f};
    }; // class Fog

}
