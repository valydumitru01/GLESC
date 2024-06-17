/**************************************************************************************************
 * @file   Material.cpp
 * @author Valentin Dumitru
 * @date   14/06/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

#include "engine/subsystems/renderer/material/Material.h"
#ifndef NDEBUG_GLESC

std::vector<EntityStatsManager::Value> GLESC::Render::Material::getDebuggingValues() {
    std::vector<EntityStatsManager::Value> values;
    EntityStatsManager::Value diffuseColorValue;
    diffuseColorValue.name = "Diffuse Color";
    diffuseColorValue.data = reinterpret_cast<void*>(&diffuseColor);
    diffuseColorValue.type = EntityStatsManager::ValueType::VEC3F;
    diffuseColorValue.isModifiable = true;
    diffuseColorValue.valueDirty = &dirty;
    diffuseColorValue.usesSlider = true;
    diffuseColorValue.min = 0.0f;
    diffuseColorValue.max = 255.0f;
    values.push_back(diffuseColorValue);

    EntityStatsManager::Value diffuseIntensityValue;
    diffuseIntensityValue.name = "Diffuse Intensity";
    diffuseIntensityValue.data = reinterpret_cast<void*>(&diffuseIntensity.getModifiable());
    diffuseIntensityValue.type = EntityStatsManager::ValueType::FLOAT;
    diffuseIntensityValue.isModifiable = true;
    diffuseIntensityValue.valueDirty = &dirty;
    diffuseIntensityValue.usesSlider = true;
    diffuseIntensityValue.min = 0.0f;
    diffuseIntensityValue.max = 1.0f;
    values.push_back(diffuseIntensityValue);

    EntityStatsManager::Value specularColorValue;
    specularColorValue.name = "Specular Color";
    specularColorValue.data = reinterpret_cast<void*>(&specularColor);
    specularColorValue.type = EntityStatsManager::ValueType::VEC3F;
    specularColorValue.isModifiable = true;
    specularColorValue.valueDirty = &dirty;
    specularColorValue.usesSlider = true;
    specularColorValue.min = 0.0f;
    specularColorValue.max = 255.0f;
    values.push_back(specularColorValue);

    EntityStatsManager::Value specularIntensityValue;
    specularIntensityValue.name = "Specular Intensity";
    specularIntensityValue.data = reinterpret_cast<void*>(&specularIntensity.getModifiable());
    specularIntensityValue.type = EntityStatsManager::ValueType::FLOAT;
    specularIntensityValue.isModifiable = true;
    specularIntensityValue.valueDirty = &dirty;
    specularIntensityValue.usesSlider = true;
    specularIntensityValue.min = 0.0f;
    specularIntensityValue.max = 1.0f;
    values.push_back(specularIntensityValue);

    EntityStatsManager::Value emissionColorValue;
    emissionColorValue.name = "Emission Color";
    emissionColorValue.data = reinterpret_cast<void*>(&emissionColor);
    emissionColorValue.type = EntityStatsManager::ValueType::VEC3F;
    emissionColorValue.isModifiable = true;
    emissionColorValue.valueDirty = &dirty;
    emissionColorValue.usesSlider = true;
    emissionColorValue.min = 0.0f;
    emissionColorValue.max = 255.0f;

    values.push_back(emissionColorValue);

    EntityStatsManager::Value emissionIntensityValue;
    emissionIntensityValue.name = "Emission Intensity";
    emissionIntensityValue.data = reinterpret_cast<void*>(&emmisionIntensity.getModifiable());
    emissionIntensityValue.type = EntityStatsManager::ValueType::FLOAT;
    emissionIntensityValue.isModifiable = true;
    emissionIntensityValue.valueDirty = &dirty;
    emissionIntensityValue.usesSlider = true;
    emissionIntensityValue.min = 0.0f;
    emissionIntensityValue.max = 1.0f;
    values.push_back(emissionIntensityValue);

    EntityStatsManager::Value shininessValue;
    shininessValue.name = "Shininess";
    shininessValue.data = reinterpret_cast<void*>(&shininess.getModifiable());
    shininessValue.type = EntityStatsManager::ValueType::FLOAT;
    shininessValue.isModifiable = true;
    shininessValue.valueDirty = &dirty;
    shininessValue.usesSlider = true;
    shininessValue.min = 0.0f;
    shininessValue.max = 1.0f;
    values.push_back(shininessValue);

    return values;
}

#else
std::vector<EntityStatsManager::Value> GLESC::Render::Material::getDebuggingValues() {
    return {};
}
#endif
