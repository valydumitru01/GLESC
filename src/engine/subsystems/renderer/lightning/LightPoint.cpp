/**************************************************************************************************
 * @file   LightPoint.cpp
 * @author Valentin Dumitru
 * @date   14/06/2024
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#include "engine/subsystems/renderer/lighting/LightPoint.h"
#ifndef NDEBUG_GLESC
std::vector<EntityStatsManager::Value> GLESC::Render::LightPoint::getDebuggingValues() {
    std::vector<EntityStatsManager::Value> values;
    EntityStatsManager::Value intensityValue;
    intensityValue.name = "Intensity";
    intensityValue.data = reinterpret_cast<void*>(&intensity.getModifiable());
    intensityValue.type = EntityStatsManager::ValueType::FLOAT;
    intensityValue.isModifiable = true;
    intensityValue.valueDirty = &dirty;
    intensityValue.usesSlider = true;
    values.push_back(intensityValue);

    EntityStatsManager::Value colorValue;
    colorValue.name = "Color";
    colorValue.data = reinterpret_cast<void*>(&color);
    colorValue.type = EntityStatsManager::ValueType::VEC3F;
    colorValue.isModifiable = true;
    colorValue.valueDirty = &dirty;
    colorValue.usesSlider = true;
    colorValue.min = 0.0f;
    colorValue.max = 255.0f;
    values.push_back(colorValue);

    EntityStatsManager::Value radiusValue;
    radiusValue.name = "Radius";
    radiusValue.data = reinterpret_cast<void*>(&radius);
    radiusValue.type = EntityStatsManager::ValueType::FLOAT;
    radiusValue.isModifiable = true;
    radiusValue.valueDirty = &dirty;
    radiusValue.usesSlider = true;
    radiusValue.min = 0.0f;
    radiusValue.max = 100.0f;
    values.push_back(radiusValue);

    return values;
}
#else
std::vector<EntityStatsManager::Value> GLESC::Render::LightPoint::getDebuggingValues() {
    return {};
}
#endif

std::string GLESC::Render::LightPoint::toString() const {
    return "Intensity:" + intensity.toString() +
        " Color:" + color.toString() +
        " Radius:" + std::to_string(radius);
}
