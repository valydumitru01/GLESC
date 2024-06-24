/**************************************************************************************************
 * @file   GlobalSun.cpp
 * @author Valentin Dumitru
 * @date   14/06/2024
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#include "engine/subsystems/renderer/lighting/GlobalSun.h"
#ifndef NDEBUG_GLESC
std::vector<EntityStatsManager::Value> GLESC::Render::GlobalSun::getDebuggingValues() {
    std::vector<EntityStatsManager::Value> values;
    EntityStatsManager::Value intensityValue;
    intensityValue.name = "Sun Intensity";
    intensityValue.data = reinterpret_cast<void*>(&intensity.getModifiable());
    intensityValue.type = EntityStatsManager::ValueType::FLOAT;
    intensityValue.isModifiable = true;
    intensityValue.usesSlider = true;
    intensityValue.valueDirty = &dirty;
    intensityValue.min = 0.0f;
    intensityValue.max = 1.0f;
    values.push_back(intensityValue);

    EntityStatsManager::Value colorValue;
    colorValue.name = "Sun Color";
    colorValue.data = reinterpret_cast<void*>(&color.data);
    colorValue.type = EntityStatsManager::ValueType::VEC3F;
    colorValue.isModifiable = true;
    colorValue.valueDirty = &dirty;
    colorValue.usesSlider = true;
    colorValue.min = 0.0f;
    colorValue.max = 255.0f;
    values.push_back(colorValue);

    EntityStatsManager::Value directionValue;
    directionValue.name = "Sun Direction";
    directionValue.data = reinterpret_cast<void*>(&direction);
    directionValue.type = EntityStatsManager::ValueType::VEC3F;
    directionValue.isModifiable = true;
    directionValue.usesSlider = true;
    directionValue.valueDirty = &dirty;
    directionValue.min = -1.0f;
    directionValue.max = 1.0f;
    values.push_back(directionValue);

    return values;
}
#else
std::vector<EntityStatsManager::Value> GLESC::Render::GlobalSun::getDebuggingValues() {
    return {};
}
#endif

std::string GLESC::Render::GlobalSun::toString() const {
    return "Intensity: " + std::to_string(intensity.get()) +
        " Color: " + color.toString() +
        " Direction: " + direction.toString();
}
