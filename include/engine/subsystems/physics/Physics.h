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
        void setMass(const Mass& mass);
        void setVelocity(const Velocity& velocity);
        void setForce(const Force& force);
        void setAcceleration(const Acceleration& acceleration);

        void setForwardVelocity(const ForwardVelocity& forwardVelocity);
        void addForwardForce(const ForwardForce& forwardForce);
        void setForwardAcceleration(const ForwardAcceleration& forwardAcceleration);
        void setAffectedByGravity(bool affectedByGravity);


        [[nodiscard]] Mass getMass() const;
        [[nodiscard]] Velocity getVelocity() const;
        [[nodiscard]] Force getForce() const;
        [[nodiscard]] Acceleration getAcceleration() const;

        [[nodiscard]] ForwardVelocity getForwardVelocity() const;
        [[nodiscard]] ForwardForce getForwardForce() const;
        [[nodiscard]] ForwardAcceleration getForwardAcceleration() const;

        [[nodiscard]] bool isAffectedByGravity() const;

        [[nodiscard]] std::vector<EntityStatsManager::Value> getDebuggingValues();
        [[nodisacrd]] std::string toString() const;

    private:
        Mass mass{1.0F};
        Velocity velocity{0, 0, 0};
        Acceleration acceleration{0,0,0};
        Force force{0,0,0};

        AngularForce angularForce{0,0,0};
        AngularAcceleration angularAcceleration{0,0,0};
        AngularVelocity angularVelocity{0,0,0};

        ForwardVelocity forwardVelocity{0};
        ForwardAcceleration forwardAcceleration{0};
        ForwardForce forwardForce{0};

        bool affectedByGravity{true};
    }; // class Physics
} // namespace Physics
