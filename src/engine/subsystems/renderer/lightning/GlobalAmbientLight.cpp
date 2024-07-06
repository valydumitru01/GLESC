
#include "engine/subsystems/renderer/lighting/GlobalAmbientLight.h"
#ifndef NDEBUG_GLESC

std::vector<EntityStatsManager::Value> GLESC::Render::GlobalAmbientLight::getDebuggingValues() {
    std::vector<EntityStatsManager::Value> values;
    EntityStatsManager::Value intensityValue;
    intensityValue.name = "Ambient Intensity";
    intensityValue.data = reinterpret_cast<void*>(&intensity);
    intensityValue.type = EntityStatsManager::ValueType::FLOAT;
    intensityValue.isModifiable = true;
    intensityValue.usesSlider = true;
    intensityValue.valueDirty = &dirty;
    intensityValue.min = 0.0f;
    intensityValue.max = 1.0f;
    values.push_back(intensityValue);

    EntityStatsManager::Value colorValue;
    colorValue.name = "Ambient Color";
    colorValue.data = reinterpret_cast<void*>(&color);
    colorValue.type = EntityStatsManager::ValueType::VEC3F;
    colorValue.isModifiable = true;
    colorValue.valueDirty = &dirty;
    colorValue.usesSlider = true;
    colorValue.min = 0.0f;
    colorValue.max = 255.0f;
    values.push_back(colorValue);

    return values;
}

#else
std::vector<EntityStatsManager::Value> GLESC::Render::GlobalAmbientLight::getDebuggingValues() {
    return {};
}
#endif
