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
#include "Physics.h"
#include "PhysicsTypes.h"
#include "Collider.h"
#include "CollisionInformation.h"
#include "engine/subsystems/transform/Transform.h"

namespace GLESC::Physics {
    class PhysicsManager {
    public:
        void applyForces(Physics& physics) const;
        void handleCollisions(Collider& collider, Physics& physics) const;
        static Transform::Transform updateTransform(const Transform::Transform& transform, const Physics& physics);

    private:
        static void executeCallbacks(Collider& collider, const CollisionInformation& collisionInfo);

        Acceleration gravity{0.f, -8.91f, 0.f};
        Friction airFriction{0.01f};
        Bounciness bounciness{0.1f};
        float bouncinessThreshold{50.f};
        /**
         * @brief This scalar is used to scale the velocity of the object
         * @details We need this because using fixed update time steps makes normal values too bit,
         * and the object would move too fast. Using a scalar makes the used be able to handle
         * more realistic numbers.
         */
        static constexpr Scalar velocityScalar{0.001f};
    };
} // namespace GLESC
