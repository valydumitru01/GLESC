/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once
#include "Physics.h"
#include "PhysicsTypes.h"
#include "Collider.h"
#include "engine/subsystems/transform/Transform.h"

namespace GLESC::Physics {
    struct CollisionInformation {
        std::vector<Vec3F> collisionPenetrationsForAxis;
        bool collided = false;
        std::vector<Collider*> colliders;
        std::vector<Physics*> physicsOfCollided;
    };

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
                                                 const Collider& nextColliderX,
                                                 const Collider& nextColliderY,
                                                 const Collider& nextColliderZ) ;

        /**
         *
         * @param collider The collider that is being checked for collision
         * @param otherCollider The collider that is being checked against
         * @return The volume of the collision for each axis
         * < 0 - Collision happened on the negative side of the axis
         * 0 - No collision
         * > 0 - Collision happened on the positive side of the axis
         */
        static Vec3F collidesWithCollider(const Collider& collider, const Collider& otherCollider);


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
