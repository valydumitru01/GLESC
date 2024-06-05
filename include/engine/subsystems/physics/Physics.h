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
        void setMass(float mass) { this->mass = mass; }
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
        void setDirectionalForce(const Math::Direction& dir, float speed) { force = dir * speed; }
        void addDirectionalForce(const Math::Direction& dir, float speed) { force += dir * speed; }
        void giveAngularForce(const AngularForce& angularForce) { this->angularForce = angularForce; }

        void setAffectedByGravity(bool affectedByGravity) { this->affectedByGravity = affectedByGravity; }


        [[nodiscard]] Mass getMass() const { return mass; }
        [[nodiscard]] Friction getFriction() const { return friction; }
        [[nodiscard]] Velocity getVelocity() const { return velocity; }
        [[nodiscard]] Force getForce() const { return force; }
        [[nodiscard]] Acceleration getAcceleration() const { return acceleration; }


        [[nodiscard]] bool isAffectedByGravity() const { return affectedByGravity; }

        [[nodiscard]] AngularForce getAngularForce() const { return angularForce; }
        [[nodiscard]] AngularAcceleration getAngularAcceleration() const { return angAccel; }
        [[nodiscard]] AngularVelocity getAngularVelocity() const { return angularVelocity; }


        [[nodiscard]] std::vector<EntityStatsManager::Value> getDebuggingValues() override;
        [[nodisacrd]] std::string toString() const;

    private:
        Mass mass{1.0F};
        Friction friction{0.1F};
        Velocity velocity{0, 0, 0};
        Acceleration acceleration{0, 0, 0};
        Force force{0, 0, 0};

        AngularForce angularForce{0, 0, 0};
        AngularAcceleration angAccel{0, 0, 0};
        AngularVelocity angularVelocity{0, 0, 0};


        bool affectedByGravity{true};
    }; // class Physics
} // namespace Physics
