/**************************************************************************************************
 * @file   PhysicsManager.h
 * @author Valentin Dumitru
 * @date   2024-04-17
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

#pragma once
#include "CollisionInformation.h"
#include "Physics.h"
#include "PhysicsTypes.h"
#include "engine/core/counter/FPSManager.h"
#include "engine/subsystems/transform/Transform.h"
#include "engine/subsystems/physics/Collider.h"

namespace GLESC::Physics {
    class PhysicsManager {
    public:
        explicit PhysicsManager(const GLESC::FPSManager& fpsManager);
        void applyForces(Physics& physics) const;
        void handleCollisions(Collider& collider, Physics& physics) const;
        Transform::Transform updateTransform(const Transform::Transform& transform, const Physics& physics) const;

    private:
        static void executeCallbacks(Collider& collider, const CollisionInformation& collisionInfo);

        Acceleration gravity{0.f, -8.91f, 0.f};
        Friction airFriction{0.01f};
        Bounciness bounciness{0.1f};
        float bouncinessThreshold{50.f};
        /**
         * @brief This is the timestep for calculating the physics
         * @details Must be defined from the update FPS
         */
        Scalar timestep{-1};
    };
} // namespace GLESC
