/**************************************************************************************************
 * @file   Collider.cpp
 * @author Valentin Dumitru
 * @date   05/06/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/


#include "engine/subsystems/physics/Collider.h"


std::vector<EntityStatsManager::Value> GLESC::Physics::Collider::getDebuggingValues() {
    std::vector<EntityStatsManager::Value> values;
    EntityStatsManager::Value solidValue;
    solidValue.name = "Solid";
    solidValue.data = reinterpret_cast<void*>(&solid);
    solidValue.type = EntityStatsManager::ValueType::BOOL;
    solidValue.isModifiable = true;
    values.push_back(solidValue);

    EntityStatsManager::Value onAirValue;
    onAirValue.name = "On Air";
    onAirValue.data = reinterpret_cast<void*>(&onAir);
    onAirValue.type = EntityStatsManager::ValueType::BOOL;
    onAirValue.isModifiable = true;
    values.push_back(onAirValue);

    EntityStatsManager::Value boundingVolumeValueMin;
    boundingVolumeValueMin.name = "Bounding Volume";
    boundingVolumeValueMin.data = reinterpret_cast<void*>(&boundingVolume.getBoundingBox().min);
    boundingVolumeValueMin.type = EntityStatsManager::ValueType::VEC3F;
    boundingVolumeValueMin.usesSlider = true;
    boundingVolumeValueMin.min = -1000.0F;
    boundingVolumeValueMin.max = 1000.0F;
    boundingVolumeValueMin.isModifiable = true;
    values.push_back(boundingVolumeValueMin);

    EntityStatsManager::Value boundingVolumeValueMax;
    boundingVolumeValueMax.name = "Bounding Volume";
    boundingVolumeValueMax.data = reinterpret_cast<void*>(&boundingVolume.getBoundingBox().max);
    boundingVolumeValueMax.type = EntityStatsManager::ValueType::VEC3F;
    boundingVolumeValueMax.usesSlider = true;
    boundingVolumeValueMax.min = -1000.0F;
    boundingVolumeValueMax.max = 1000.0F;
    boundingVolumeValueMax.isModifiable = true;
    values.push_back(boundingVolumeValueMax);

    EntityStatsManager::Value isCollidingValue;
    isCollidingValue.name = "Is Colliding";
    isCollidingValue.data = reinterpret_cast<void*>(&collidesAxis);
    isCollidingValue.type = EntityStatsManager::ValueType::VEC3B;
    isCollidingValue.isModifiable = true;
    values.push_back(isCollidingValue);

    EntityStatsManager::Value colliderNamesValue;
    colliderNamesValue.name = "Colliders";
    colliderNamesValue.data = reinterpret_cast<void*>(&collidingWith);
    colliderNamesValue.type = EntityStatsManager::ValueType::STRING;
    colliderNamesValue.isModifiable = false;
    values.push_back(colliderNamesValue);


    return values;
}

std::vector<EntityStatsManager::Value> GLESC::Physics::Collider::getUpdatedDebuggingValues() {
    std::vector<EntityStatsManager::Value> values;
    EntityStatsManager::Value colliderNamesValue;
    colliderNamesValue.name = "Colliders";
    colliderNamesValue.isString = true;
    for (auto& collider : collidingWith) {
        colliderNamesValue.stringData += std::string(collider->getOwnerName()) + " ";
    }
    colliderNamesValue.type = EntityStatsManager::ValueType::STRING;
    colliderNamesValue.isModifiable = false;
    values.push_back(colliderNamesValue);

    return values;
}
