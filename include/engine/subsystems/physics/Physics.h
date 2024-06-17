/**************************************************************************************************
* @file   Physics.h
 * @author Valentin Dumitru
 * @date   2024-05-15
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "PhysicsTypes.h"
#include "engine/core/math/geometry/GeometryTypes.h"
#include "engine/subsystems/EngineComponent.h"
#include "engine/subsystems/ingame-debug/EntityStatsManager.h"

namespace GLESC::Physics {
    class Physics : public EngineComponent {
    public:
        Physics() = default;

        void setMass(const Mass& mass) {
            D_ASSERT_TRUE(mass > 0.0F, "Mass must be greater than 0");
            this->mass = mass;
        }

        void addMass(const Mass& mass) { this->mass += mass; }
        void setMass(Mass& mass) { this->mass = mass; }
        void setAirFriction(Friction airFriction) { this->airFriction = airFriction; }
        void addAirFriction(Friction airFriction) { this->airFriction += airFriction; }
        void setFriction(float friction) { this->friction = friction; }
        void addFriciton(float friction) { this->friction += friction; }


        void addVelocity(const Velocity& velocity) { this->velocity += velocity; }
        void setVelocity(const Velocity& velocity) { this->velocity = velocity; }
        void setDirectionalVelocity(const Math::Direction& direction, float speed) { velocity = direction * speed; }
        void addDirectionalVelocity(const Math::Direction& direction, float speed) { velocity += direction * speed; }
        void setAngularVelocity(const AngularVelocity& angularVelocity) { this->angularVelocity = angularVelocity; }
        void addAngularVelocity(const AngularVelocity& angularVelocity) { this->angularVelocity += angularVelocity; }

        void addAcceleration(const Acceleration& acceleration) { this->acceleration += acceleration; }
        void setAcceleration(const Acceleration& acceleration) { this->acceleration = acceleration; }
        void addDirectionalAcceleration(const Math::Direction& dir, float speed) { acceleration += dir * speed; }
        void setDirectionalAcceleration(const Math::Direction& dir, float speed) { acceleration = dir * speed; }
        void setAngularAcceleration(const AngularAcceleration& angAccelParam) { this->angAccel = angAccelParam; }
        void addAngularAcceleration(const AngularAcceleration& angAccelParam) { this->angAccel += angAccelParam; }

        void setForce(const Force& force) { this->force = force; }
        void addForce(const Force& force) { this->force += force; }
        void setDirectionalForce(const Math::Direction& dir, float forceParam) { force = dir * forceParam; }
        void addDirectionalForce(const Math::Direction& dir, float forceParam) { force += dir * forceParam; }
        void giveAngularForce(const AngularForce& angularForce) { this->angularForce = angularForce; }

        void setAffectedByGravity(bool affectedByGravity) { this->affectedByGravity = affectedByGravity; }
        void setStatic(bool isStatic) { this->staticObj = isStatic; }


        [[nodiscard]] Mass getMass() const { return mass; }
        [[nodiscard]] Friction getFriction() const { return friction; }
        [[nodiscard]] Friction getAirFriction() const { return airFriction; }
        [[nodiscard]] Velocity getVelocity() const { return velocity; }
        [[nodiscard]] Force getForce() const { return force; }
        [[nodiscard]] Acceleration getAcceleration() const { return acceleration; }


        [[nodiscard]] bool isAffectedByGravity() const { return affectedByGravity; }
        [[nodiscard]] bool isStatic() const { return staticObj; }

        [[nodiscard]] AngularForce getAngularForce() const { return angularForce; }
        [[nodiscard]] AngularAcceleration getAngularAcceleration() const { return angAccel; }
        [[nodiscard]] AngularVelocity getAngularVelocity() const { return angularVelocity; }

        [[nodiscard]] std::string toString() const override;
#ifndef NDEBUG_GLESC
        [[nodiscard]] std::vector<EntityStatsManager::Value> getDebuggingValues() override;
#endif

    private:
        Mass mass{1.0F};
        Friction friction{0.01f};
        /**
         * @details While its negative, it will be the default value for air friction defined in the physics manager
         */
        Friction airFriction{-1.f};
        Velocity velocity{0, 0, 0};
        Acceleration acceleration{0, 0, 0};
        Force force{0, 0, 0};

        AngularForce angularForce{0, 0, 0};
        AngularAcceleration angAccel{0, 0, 0};
        AngularVelocity angularVelocity{0, 0, 0};

        bool staticObj{false};
        bool affectedByGravity{true};
    }; // class Physics
} // namespace Physics
