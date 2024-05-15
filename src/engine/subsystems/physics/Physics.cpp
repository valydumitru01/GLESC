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

void Physics::setMass(const Mass& mass) {
    D_ASSERT_TRUE(mass > 0.0F, "Mass must be greater than 0");
    this->mass = mass;
}

void Physics::setVelocity(const Velocity& velocity) {
    this->velocity = velocity;
}

void Physics::setForce(const Force& force) {
    this->force = force;
}

void Physics::setAcceleration(const Acceleration& acceleration) {
    this->acceleration = acceleration;
}

void Physics::setForwardVelocity(const ForwardVelocity& forwardVelocity) {
    this->forwardVelocity = forwardVelocity;
}

void Physics::addForwardForce(const ForwardForce& forwardForce) {
    this->forwardForce = forwardForce;
}

void Physics::setForwardAcceleration(const ForwardAcceleration& forwardAcceleration) {
    this->forwardAcceleration = forwardAcceleration;
}

void Physics::setAffectedByGravity(bool affectedByGravity) {
    this->affectedByGravity = affectedByGravity;
}


[[nodiscard]] Mass Physics::getMass() const {
    return mass;
}

[[nodiscard]] Velocity Physics::getVelocity() const {
    return velocity;
}

[[nodiscard]] Force Physics::getForce() const {
    return force;
}

[[nodiscard]] Acceleration Physics::getAcceleration() const {
    return acceleration;
}

[[nodiscard]] ForwardVelocity Physics::getForwardVelocity() const {
    return forwardVelocity;
}

[[nodiscard]] ForwardForce Physics::getForwardForce() const {
    return forwardForce;
}

[[nodiscard]] ForwardAcceleration Physics::getForwardAcceleration() const {
    return forwardAcceleration;
}

bool Physics::isAffectedByGravity() const {
    return affectedByGravity;
}

[[nodiscard]] std::string Physics::toString() const {
    return "Physics: " +
        std::to_string(mass) + " " +
        velocity.toString() + " " +
        acceleration.toString() + " " +
        force.toString() + " " +
        std::to_string(forwardVelocity) + " " +
        std::to_string(forwardForce) + " " +
        std::to_string(forwardAcceleration) + " " +
        std::to_string(affectedByGravity);
}


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

    EntityStatsManager::Value forwardVelocityValue;
    forwardVelocityValue.name = "Forward Velocity";
    forwardVelocityValue.data = reinterpret_cast<void*>(&forwardVelocity);
    forwardVelocityValue.type = EntityStatsManager::ValueType::FLOAT;
    forwardVelocityValue.isModifiable = true;
    forwardVelocityValue.usesSlider = true;
    forwardVelocityValue.min = -1000.0F;
    forwardVelocityValue.max = 1000.0F;
    values.push_back(forwardVelocityValue);

    EntityStatsManager::Value forwardForceValue;
    forwardForceValue.name = "Forward Force";
    forwardForceValue.data = reinterpret_cast<void*>(&forwardForce);
    forwardForceValue.type = EntityStatsManager::ValueType::FLOAT;
    forwardForceValue.isModifiable = true;
    forwardForceValue.usesSlider = true;
    forwardForceValue.min = -1000.0F;
    forwardForceValue.max = 1000.0F;
    values.push_back(forwardForceValue);

    EntityStatsManager::Value forwardAccelerationValue;
    forwardAccelerationValue.name = "Forward Acceleration";
    forwardAccelerationValue.data = reinterpret_cast<void*>(&forwardAcceleration);
    forwardAccelerationValue.type = EntityStatsManager::ValueType::FLOAT;
    forwardAccelerationValue.isModifiable = true;
    forwardAccelerationValue.usesSlider = true;
    forwardAccelerationValue.min = -1000.0F;
    forwardAccelerationValue.max = 1000.0F;
    values.push_back(forwardAccelerationValue);


    return values;
}
