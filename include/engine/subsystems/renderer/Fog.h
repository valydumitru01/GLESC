/**************************************************************************************************
 * @file   Fog.h
 * @author Valentin Dumitru
 * @date   2024-05-03
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "RendererTypes.h"

class Fog {
public:
    Fog(float density, float& start, float& end, const GLESC::Render::ColorRgbNorm& color)
        : density(density), start(start), end(end), color(color) {
    }


    void setDensity(float density) {
        this->density.set(density);
    }

    void setStart(float& start) {
        this->start = start;
    }

    void setEnd(float& end) {
        this->end = end;
    }

    void setColor(const GLESC::Render::ColorRgb& color) {
        this->color = color;
    }


    [[nodiscard]] const float getDensity() const {
        return density.get();
    }

    [[nodiscard]] float getStart() const {
        return start;
    }

    [[nodiscard]] float getEnd() const {
        return end;
    }

    [[nodiscard]] const GLESC::Render::ColorRgbNorm& getColor() const {
        return color;
    }

private:
    GLESC::Render::Intensity<float> density;
    float& start;
    float& end;
    GLESC::Render::ColorRgbNorm color;
}; // class Fog
