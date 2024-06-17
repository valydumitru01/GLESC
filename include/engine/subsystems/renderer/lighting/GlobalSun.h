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
#include <utility>

#include "engine/core/math/geometry/GeometryTypes.h"
#include "engine/subsystems/ingame-debug/EntityStatsManager.h"
#include "engine/subsystems/renderer/RendererTypes.h"

namespace GLESC::Render {
    class GlobalSun {
    public:
        /**
         * @brief Default constructor.
         */
        GlobalSun() = default;

        GlobalSun(float intensity, ColorRgb  color, Math::Direction  direction) :
            intensity(intensity), color(std::move(color)), direction(std::move(direction)) {
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
        [[nodiscard]] std::vector<EntityStatsManager::Value> getDebuggingValues() ;
        [[nodiscard]] std::string toString() const;

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
