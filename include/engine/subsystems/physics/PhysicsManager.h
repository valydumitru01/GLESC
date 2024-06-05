/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once
#include "Physics.h"
#include "PhysicsTypes.h"
#include "Collider.h"
#include "CollisionInformation.h"
#include "engine/subsystems/transform/Transform.h"

namespace GLESC::Physics {
    class PhysicsManager {
    public:
        void updatePhysics(Physics& physics);
        void checkCollisions(Collider& collider, Transform::Transform& transform, Physics& physics);

        void addPhysics(Collider& collider, Physics& physics) {
            this->colliders.push_back(&collider);
            this->physics.push_back(&physics);
        }

        void clearPhysics() {
            this->colliders.clear();
            this->physics.clear();
        }

    private:
        static void handleCollisions(CollisionInformation& info, Collider& collider, Physics& physics);

        static Transform::Transform getNextTransform(const Transform::Transform& transformParam,
                                                     const Physics& nextPhysics);

        static Physics getNextPhysics(const Physics& oldPhysics);
        static Collider getNextCollider(const Collider& oldCollider, const Transform::Transform& nextTransform);


        CollisionInformation collidesOnNextFrame(const Collider& originalCollider,
                                                 const Collider& nextCollider,
                                                 const Collider& nextColliderX,
                                                 const Collider& nextColliderY,
                                                 const Collider& nextColliderZ);

        /**
         * @brief Get the depth of the collision on each axis
         * @param otherCollider The collider of the object that we are checking the collision with
         * @return The depth of the collision on each axis
         */
        static Vec3F getCollisionDepth(const Collider& nextColliderX, const Collider& nextColliderY,
                                       const Collider& nextColliderZ, const Collider& otherCollider);

        std::vector<Collider*> colliders;
        std::vector<Physics*> physics;

        static constexpr Acceleration gravity{0.f, -8.91f, 0.f};
        static constexpr Friction airFriction{0.01f};
        /**
         * @brief This scalar is used to scale the velocity of the object
         * @details We need this because using fixed update time steps makes normal values too bit,
         * and the object would move too fast. Using a scalar makes the used be able to handle
         * more realistic numbers.
         */
        static constexpr Scalar velocityScalar{0.001f};
    };
} // namespace GLESC
