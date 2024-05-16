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
#include "engine/subsystems/ingame-debug/EntityStatsManager.h"

namespace GLESC::Physics {
    class Physics {
    public:
        Physics() = default;

        void setMass(const Mass& mass) {
            D_ASSERT_TRUE(mass > 0.0F, "Mass must be greater than 0");
            this->mass = mass;
        }

        void setVelocity(const Velocity& velocity) { this->velocity = velocity; }
        void giveForce(const Force& force) { this->force = force; }
        void setAcceleration(const Acceleration& acceleration) { this->acceleration = acceleration; }

        void giveAngularForce(const AngularForce& angularForce) { this->angularForce = angularForce; }

        void setAngularAcceleration(const AngularAcceleration& angularAcceleration) {
            this->angularAcceleration = angularAcceleration;
        }

        void setAngularVelocity(const AngularVelocity& angularVelocity) { this->angularVelocity = angularVelocity; }


        void setForwardVelocity(const ForwardVelocity& forwardVelocity) { this->forwardVelocity = forwardVelocity; }
        void giveForwardForce(const ForwardForce& forwardForce) { this->forwardForce = forwardForce; }

        void setForwardAcceleration(const ForwardAcceleration& forwardAcceleration) {
            this->forwardAcceleration = forwardAcceleration;
        }

        void setAffectedByGravity(bool affectedByGravity) { this->affectedByGravity = affectedByGravity; }


        [[nodiscard]] Mass getMass() const { return mass; }
        [[nodiscard]] Velocity getVelocity() const { return velocity; }
        [[nodiscard]] Force getForce() const { return force; }
        [[nodiscard]] Acceleration getAcceleration() const { return acceleration; }

        [[nodiscard]] ForwardVelocity getForwardVelocity() const { return forwardVelocity; }
        [[nodiscard]] ForwardForce getForwardForce() const { return forwardForce; }
        [[nodiscard]] ForwardAcceleration getForwardAcceleration() const { return forwardAcceleration; }


        void addMass(const Mass& mass) { this->mass += mass; }
        void addVelocity(const Velocity& velocity) { this->velocity += velocity; }
        void addForce(const Force& force) { this->force += force; }
        void addAcceleration(const Acceleration& acceleration) { this->acceleration += acceleration; }

        void addAngularAcceleration(const AngularAcceleration& angularAcceleration) {
            this->angularAcceleration += angularAcceleration;
        }

        void addAngularVelocity(const AngularVelocity& angularVelocity) { this->angularVelocity += angularVelocity; }

        void addForwardVelocity(const ForwardVelocity& forwardVelocity) { this->forwardVelocity += forwardVelocity; }

        void addForwardAcceleration(const ForwardAcceleration& forwardAcceleration) {
            this->forwardAcceleration += forwardAcceleration;
        }


        bool isAffectedByGravity() const { return affectedByGravity; }

        [[nodiscard]] std::vector<EntityStatsManager::Value> getDebuggingValues();
        [[nodisacrd]] std::string toString() const;

    private:
        Mass mass{1.0F};
        Velocity velocity{0, 0, 0};
        Acceleration acceleration{0, 0, 0};
        Force force{0, 0, 0};

        AngularForce angularForce{0, 0, 0};
        AngularAcceleration angularAcceleration{0, 0, 0};
        AngularVelocity angularVelocity{0, 0, 0};

        ForwardVelocity forwardVelocity{0};
        ForwardAcceleration forwardAcceleration{0};
        ForwardForce forwardForce{0};

        bool affectedByGravity{true};
    }; // class Physics
} // namespace Physics
