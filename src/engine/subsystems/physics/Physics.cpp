/**************************************************************************************************
 * @file   Physics.cpp
 * @author Valentin Dumitru
 * @date   2024-05-15
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#include "engine/subsystems/physics/Physics.h"
using namespace GLESC::Physics;


[[nodiscard]] std::string Physics::toString() const {
    return "Physics: " +
        std::to_string(mass) + " " +
        velocity.toString() + " " +
        acceleration.toString() + " " +
        force.toString() + " " +
        std::to_string(affectedByGravity);
}
#ifndef NDEBUG_GLESC
[[nodiscard]] std::vector<EntityStatsManager::Value> Physics::getDebuggingValues() {
    std::vector<EntityStatsManager::Value> values;
    EntityStatsManager::Value massValue;
    massValue.name = "Mass";
    massValue.data = reinterpret_cast<void*>(&mass);
    massValue.type = EntityStatsManager::ValueType::FLOAT;
    massValue.isModifiable = true;
    massValue.usesSlider = true;
    massValue.min = 0.0F;
    massValue.max = 10000.0F;
    values.push_back(massValue);

    EntityStatsManager::Value velocityValue;
    velocityValue.name = "Velocity";
    velocityValue.data = reinterpret_cast<void*>(&velocity);
    velocityValue.type = EntityStatsManager::ValueType::VEC3F;
    velocityValue.isModifiable = true;
    velocityValue.usesSlider = true;
    velocityValue.min = -1000.0F;
    velocityValue.max = 1000.0F;
    values.push_back(velocityValue);

    EntityStatsManager::Value forceValue;
    forceValue.name = "Force";
    forceValue.data = reinterpret_cast<void*>(&force);
    forceValue.type = EntityStatsManager::ValueType::VEC3F;
    forceValue.isModifiable = true;
    forceValue.usesSlider = true;
    forceValue.min = -1000.0F;
    forceValue.max = 1000.0F;
    values.push_back(forceValue);

    EntityStatsManager::Value accelerationValue;
    accelerationValue.name = "Acceleration";
    accelerationValue.data = reinterpret_cast<void*>(&acceleration);
    accelerationValue.type = EntityStatsManager::ValueType::VEC3F;
    accelerationValue.isModifiable = true;
    accelerationValue.usesSlider = true;
    accelerationValue.min = -1000.0F;
    accelerationValue.max = 1000.0F;
    values.push_back(accelerationValue);

    EntityStatsManager::Value affectedByGravity;
    affectedByGravity.name = "Affected by gravity";
    affectedByGravity.data = reinterpret_cast<void*>(&this->affectedByGravity);
    affectedByGravity.type = EntityStatsManager::ValueType::BOOL;
    affectedByGravity.isModifiable = true;
    values.push_back(affectedByGravity);

    EntityStatsManager::Value frictionValue;
    frictionValue.name = "Friction";
    frictionValue.data = reinterpret_cast<void*>(&friction);
    frictionValue.type = EntityStatsManager::ValueType::FLOAT;
    frictionValue.isModifiable = true;
    frictionValue.usesSlider = true;
    frictionValue.min = 0.0F;
    frictionValue.max = 1.0F;
    values.push_back(frictionValue);

    return values;
}
#endif