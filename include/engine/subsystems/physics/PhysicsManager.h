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
    class PhysicsManager {
    public:
        void updatePhysics(Physics& physics, Collider& collider, Transform::Transform& transform) {
            addCollider(collider);

            physics = getNextPhysics(physics, transform);
            Transform::Transform nextTransform = getNextTransform(transform, physics);
            if (!collider.isSolid()) {
                transform = nextTransform;
                return;
            }
            Transform::Transform oldTransform = transform;

            // Check if the X translation in the next frame will cause a collision
            Transform::Transform nextTransformX = nextTransform;
            nextTransformX.setPosition({
                nextTransformX.getPosition().getX(),
                oldTransform.getPosition().getY(),
                oldTransform.getPosition().getZ()
            });
            Collider nextColliderX = getNextCollider(collider, nextTransformX);


            // Check if the Y translation in the next frame will cause a collision
            Transform::Transform nextTransformY = nextTransform;
            nextTransformY.setPosition({
                oldTransform.getPosition().getX(),
                nextTransformY.getPosition().getY(),
                oldTransform.getPosition().getZ()
            });
            Collider nextColliderY = getNextCollider(collider, nextTransformY);


            // Check if the Z translation in the next frame will cause a collision
            Transform::Transform nextTransformZ = nextTransform;
            nextTransformY.setPosition({
                oldTransform.getPosition().getX(),
                nextTransformY.getPosition().getY(),
                oldTransform.getPosition().getZ()
            });
            Collider nextColliderZ = getNextCollider(collider, nextTransformZ);

            // Cancel the component that causes the collision
            Vec3B bools = collidesOnNextFrame(collider, nextColliderX, nextColliderY, nextColliderZ);

            // Cancel the components that cause the collision
            if (bools.getX()) {
                physics.setVelocity({0.0F, physics.getVelocity().getY(), physics.getVelocity().getZ()});
            }
            if (bools.getY()) {
                physics.setVelocity({physics.getVelocity().getX(), 0.0F, physics.getVelocity().getZ()});
            }
            if (bools.getZ()) {
                physics.setVelocity({physics.getVelocity().getX(), physics.getVelocity().getY(), 0.0F});
            }

            nextTransform = getNextTransform(transform, physics);

            transform = nextTransform;
        }

        Transform::Transform getNextTransform(const Transform::Transform& transformParam,
                                              const Physics& nextPhysics) const {
            Transform::Transform nextTransform = transformParam;

            // Calculate position
            nextTransform.addPosition(nextPhysics.getVelocity() * velocityScalar);
            nextTransform.addPosition(nextTransform.forward() * nextPhysics.getForwardVelocity() * velocityScalar);

            return nextTransform;
        }

        Physics getNextPhysics(const Physics& oldPhysics, const Transform::Transform& transform) const {
            Physics physics = oldPhysics;
            // Calculate acceleration
            physics.addAcceleration(physics.getForce() / physics.getMass());
            physics.addAcceleration(transform.forward() * physics.getForwardForce() / physics.getMass());
            if (physics.isAffectedByGravity())
                physics.addAcceleration(gravity);

            // Calculate velocity
            physics.addVelocity(physics.getAcceleration());
            physics.addVelocity(transform.forward() * physics.getForwardAcceleration());

            // Apply friction
            physics.addVelocity(-physics.getVelocity() * airFriction);

            // Clear forces
            physics.giveForce(Force(0.0F, 0.0F, 0.0F));
            physics.giveForwardForce(0.0F);

            // Clear acceleration
            physics.setAcceleration(Acceleration(0.0F, 0.0F, 0.0F));

            return physics;
        }

        Collider getNextCollider(const Collider& oldCollider, const Transform::Transform& nextTransform) const {
            Collider nextCollider = oldCollider;
            nextCollider.boundingVolume = Transform::Transformer::transformBoundingVolume(oldCollider.boundingVolume,
                nextTransform);
            return nextCollider;
        }


        Vec3B collidesOnNextFrame(const Collider& originalCollider,
                                  const Collider& nextColliderX,
                                  const Collider& nextColliderY,
                                  const Collider& nextColliderZ) {
            Vec3B finalBools;
            for (const auto& otherCollider : colliders) {
                if (otherCollider == &originalCollider) continue;
                Vec3B boolsForCollider{
                    collidesWithCollider(nextColliderX, *otherCollider),
                    collidesWithCollider(nextColliderY, *otherCollider),
                    collidesWithCollider(nextColliderZ, *otherCollider)
                };
                finalBools.setX(finalBools.getX() || boolsForCollider.getX());
                finalBools.setY(finalBools.getY() || boolsForCollider.getY());
                finalBools.setZ(finalBools.getZ() || boolsForCollider.getZ());
            }
            return finalBools;
        }

        bool collidesWithCollider(const Collider& collider, const Collider& otherCollider) {
            if (collider.boundingVolume.intersects(otherCollider.boundingVolume)) {
                if (collider.collisionCallback)
                    collider.collisionCallback();
                auto it = collider.collisionCallbacksForSpecificColliders.find(&otherCollider);
                if (it != collider.collisionCallbacksForSpecificColliders.end()) {
                    it->second();
                }
                return true;
            }
            return false;
        }

        void addCollider(const Collider& collider) {
            // Check if it is in the vector, if not add it
            if (std::find(colliders.begin(), colliders.end(), &collider) == colliders.end()) {
                colliders.push_back(&collider);
            }
        }

    private:
        std::vector<const Collider*> colliders;

        Acceleration gravity{0.f, -8.91f, 0.f};
        Friction airFriction{0.1f};
        /**
         * @brief This scalar is used to scale the velocity of the object
         * @details We need this because using fixed update time steps makes normal values too bit,
         * and the object would move too fast. Using a scalar makes the used be able to handle
         * more realistic numbers.
         */
        Scalar velocityScalar{0.001f};
    };
} // namespace GLESC
