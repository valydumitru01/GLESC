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
#include "engine/subsystems/ingame-debug/EntityStatsManager.h"

class Fog {
public:
    Fog() = default;

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

    [[nodiscard]] float& getModifiableDensity() {
        return density.getModifiable();
    }

    [[nodiscard]] const GLESC::Render::ColorRgbNorm& getColor() const {
        return color;
    }


    [[nodisacrd]] std::vector<EntityStatsManager::Value> getDebuggingValues() {
        std::vector<EntityStatsManager::Value> values;
        EntityStatsManager::Value densityValue;
        densityValue.name = "Density";
        densityValue.data = reinterpret_cast<void*>(&density.getModifiable());
        densityValue.type = EntityStatsManager::ValueType::FLOAT;
        densityValue.isModifiable = true;
        values.push_back(densityValue);

        EntityStatsManager::Value startValue;
        startValue.name = "Start";
        startValue.data = reinterpret_cast<void*>(&start);
        startValue.type = EntityStatsManager::ValueType::FLOAT;
        startValue.isModifiable = true;
        values.push_back(startValue);

        EntityStatsManager::Value endValue;
        endValue.name = "End";
        endValue.data = reinterpret_cast<void*>(&end);
        endValue.type = EntityStatsManager::ValueType::FLOAT;
        endValue.isModifiable = true;
        values.push_back(endValue);

        EntityStatsManager::Value colorValue;
        colorValue.name = "Color";
        colorValue.data = reinterpret_cast<void*>(&color);
        colorValue.type = EntityStatsManager::ValueType::VEC3F;
        colorValue.isModifiable = true;
        values.push_back(colorValue);


        return values;
    }

    [[nodiscard]] std::string toString() const {
        return "Fog: density=" + std::to_string(density.get()) + ", start=" + std::to_string(start) + ", end=" +
            std::to_string(end) + ", color=" + color.toString();
    }

private:
    GLESC::Render::Intensity<float> density{1.0f};
    float start{0.0f};
    float end{50.0f};
    GLESC::Render::ColorRgbNorm color{0.5f, 0.5f, 0.5f};
}; // class Fog
