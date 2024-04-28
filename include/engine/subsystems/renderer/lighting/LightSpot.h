/**************************************************************************************************
 * @file   LightSpot.h
 * @author Valentin Dumitru
 * @date   2024-03-31
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include <string>

#include "engine/subsystems/renderer/RendererTypes.h"

namespace GLESC::Render {
    struct LightSpot {
        LightSpot() = default;


        void setRadius(float radiusParam) {
            radius = radiusParam;
            dirty = true;
        }

        void setIntensity(float intensityParam) {
            intensity.set(intensityParam);
            dirty = true;
        }

        void setColor(const ColorRgb& colorParam) {
            color = colorParam;
            dirty = true;
        }


        float getIntensity() const { return intensity.get(); }
        const ColorRgb& getColor() const { return color; }
        [[nodiscard]] float getRadius() const { return radius; }



        float& getModifiableIntensity() {
            return intensity.getModifiable();
            dirty = true;
        }

        ColorRgb& getModifiableColor() {
            dirty = true;
            return color;
        }

        [[nodiscard]] float& getModifiableRadius() {
            dirty = true;
            return radius;
        }



        [[nodiscard]] bool& isDirty() const { return dirty; }
        void setClean() const { dirty = false; }


        [[nodiscard]] std::string toString() const {
            return "Intensity:" + intensity.toString() +
                " Color:" + color.toString() +
                " Radius:" + std::to_string(radius);
        }

    private:
        Intensity<float> intensity{1.0f};
        ColorRgb color{255.f, 255.f, 255.f};
        float radius{10.0f};
        mutable bool dirty{true};
    }; // class Light
} // namespace GLESC::Render
