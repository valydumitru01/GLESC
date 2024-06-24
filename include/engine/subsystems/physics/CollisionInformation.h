/**************************************************************************************************
 * @file   CollisionInformation.h
 * @author Valentin Dumitru
 * @date   06/06/2024
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include <vector>
#include "engine/core/math/algebra/vector/Vector.h"

namespace GLESC::Physics {
    class Collider;
    class Physics;

    class CollisionInformation {
    public:
        void setCollidesAxis(const Vec3B& collidesAxis) {
            this->collidingAxis = collidesAxis;
        }

        void addCollidingWith(Collider* collider, Physics* physics, const Vec3F& collisionDepthForAxis) {
            this->collidingWithColliders.push_back(collider);
            this->physicsOfCollided.push_back(physics);
            this->collisionDepthForAxis.push_back(collisionDepthForAxis);
        }

        void setColliding(bool colliding) {
            this->colliding = colliding;
        }

        void setOnGround(bool onGround) {
            this->onGround = onGround;
            this->onGoundLastFrame = onGround;
        }

        [[nodiscard]] Vec3B& getCollidingAxis() {
            return collidingAxis;
        }

        [[nodiscard]] std::vector<Vec3F>& getCollisionDepthForAxis() {
            return collisionDepthForAxis;
        }

        [[nodiscard]] std::vector<Collider*>& getCollidingWithColliders() {
            return collidingWithColliders;
        }

        [[nodiscard]] std::vector<Physics*>& getPhysicsOfCollided() {
            return physicsOfCollided;
        }

        [[nodiscard]] bool& isColliding() {
            return colliding;
        }

        [[nodiscard]] bool& isOnGround() {
            return onGround;
        }

        [[nodiscard]] const std::vector<Physics*>& getPhysicsOfCollided() const {
            return physicsOfCollided;
        }

        [[nodiscard]] const std::vector<Collider*>& getCollidingWithColliders() const {
            return collidingWithColliders;
        }

        [[nodiscard]] const std::vector<Vec3F>& getCollisionDepthForAxis() const {
            return collisionDepthForAxis;
        }

        [[nodiscard]] const Vec3B& getCollidingAxis() const {
            return collidingAxis;
        }

        [[nodiscard]] bool isColliding() const {
            return colliding;
        }

        [[nodiscard]] bool isOnGround() const {
            return onGround;
        }

        [[nodiscard]] bool wasOnGroundLastFrame() const {
            return onGoundLastFrame;
        }

        void clearInformation() {
            collidingAxis = {false, false, false};
            collisionDepthForAxis.clear();
            collidingWithColliders.clear();
            physicsOfCollided.clear();
            colliding = false;
        }

    private:
        std::vector<Vec3F> collisionDepthForAxis;
        std::vector<Collider*> collidingWithColliders;
        std::vector<Physics*> physicsOfCollided;
        Vec3B collidingAxis{false, false, false};
        bool colliding = false;
        bool onGround = true;
        bool onGoundLastFrame = false;
    }; // class CollisionInformation
} // namespace GLESC::Physics
