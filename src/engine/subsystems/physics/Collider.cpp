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

#include <sstream>
#ifndef NDEBUG_GLESC

std::vector<EntityStatsManager::Value> GLESC::Physics::Collider::getDebuggingValues() {
    std::vector<EntityStatsManager::Value> values;
    EntityStatsManager::Value solidValue;
    solidValue.name = "Solid";
    solidValue.data = reinterpret_cast<void*>(&solid);
    solidValue.type = EntityStatsManager::ValueType::BOOL;
    solidValue.isModifiable = true;
    values.push_back(solidValue);


    EntityStatsManager::Value boundingVolumeValueMin;
    boundingVolumeValueMin.name = "Bounding Volume Min";
    boundingVolumeValueMin.data = reinterpret_cast<void*>(&boundingVolume.getBoundingBox().min);
    boundingVolumeValueMin.type = EntityStatsManager::ValueType::VEC3F;
    boundingVolumeValueMin.usesSlider = true;
    boundingVolumeValueMin.min = -1000.0F;
    boundingVolumeValueMin.max = 1000.0F;
    boundingVolumeValueMin.isModifiable = true;
    values.push_back(boundingVolumeValueMin);

    EntityStatsManager::Value boundingVolumeValueMax;
    boundingVolumeValueMax.name = "Bounding Volume Max";
    boundingVolumeValueMax.data = reinterpret_cast<void*>(&boundingVolume.getBoundingBox().max);
    boundingVolumeValueMax.type = EntityStatsManager::ValueType::VEC3F;
    boundingVolumeValueMax.usesSlider = true;
    boundingVolumeValueMax.min = -1000.0F;
    boundingVolumeValueMax.max = 1000.0F;
    boundingVolumeValueMax.isModifiable = true;
    values.push_back(boundingVolumeValueMax);

    EntityStatsManager::Value isCollidingValue;
    isCollidingValue.name = "Is Colliding";
    isCollidingValue.data = reinterpret_cast<void*>(&collisionInformation.isColliding());
    isCollidingValue.type = EntityStatsManager::ValueType::BOOL;
    isCollidingValue.isModifiable = false;
    values.push_back(isCollidingValue);

    EntityStatsManager::Value isCollidingWithAxisValue;
    isCollidingWithAxisValue.name = "Is Colliding with axis";
    isCollidingWithAxisValue.data = reinterpret_cast<void*>(&collisionInformation.getCollidingAxis());
    isCollidingWithAxisValue.type = EntityStatsManager::ValueType::VEC3B;
    isCollidingWithAxisValue.isModifiable = true;
    values.push_back(isCollidingWithAxisValue);

    EntityStatsManager::Value onAirValue;
    onAirValue.name = "Is on ground";
    onAirValue.data = reinterpret_cast<void*>(&collisionInformation.isOnGround());
    onAirValue.type = EntityStatsManager::ValueType::BOOL;
    onAirValue.isModifiable = true;
    values.push_back(onAirValue);


    return values;
}

std::vector<EntityStatsManager::Value> GLESC::Physics::Collider::getUpdatedDebuggingValues() {
    std::vector<EntityStatsManager::Value> values;
    EntityStatsManager::Value colliderNamesValue;
    colliderNamesValue.name = "Colliders";
    colliderNamesValue.isString = true;
    for (int i = 0; i < collisionInformation.getCollisionDepthForAxis().size(); i++) {
        Vec3F& collisionDepth = collisionInformation.getCollisionDepthForAxis()[i];
        Collider* collider = collisionInformation.getCollidingWithColliders()[i];
        colliderNamesValue.stringData += std::string(collider->getOwnerName()) +
            " depth: " + collisionDepth.toString() + "\n";
    }
    colliderNamesValue.type = EntityStatsManager::ValueType::STRING;
    colliderNamesValue.isModifiable = false;
    values.push_back(colliderNamesValue);


    return values;
}
#endif


std::string GLESC::Physics::Collider::toString() const {
    // TODO: Improve this if needed (missing stuff)
    std::stringstream ss;
    ss << "AABB max:" + boundingVolume.getMax().toString() + " min:" + boundingVolume.getMin().toString();
    ss << " Solid:" << solid;
    ss << " On Air:" << collisionInformation.isOnGround();
    ss << " Collides Axis:" << collisionInformation.getCollidingAxis().toString();
    return ss.str();
}