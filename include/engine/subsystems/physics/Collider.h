/**************************************************************************************************
 * @file   Collider.h
 * @author Valentin Dumitru
 * @date   16/05/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include <functional>

#include "CollisionInformation.h"
#include "engine/core/math/geometry/figures/BoundingVolume.h"
#include "engine/subsystems/EngineComponent.h"
#include "engine/subsystems/ingame-debug/EntityStatsManager.h"

namespace GLESC::Physics {
    class PhysicsManager;
}

namespace GLESC::Physics {
    class Collider : public EngineComponent {
    public:
        Collider() = default;
        ~Collider() = default;

        void setBoundingVolume(const Math::BoundingVolume& boundingVolume) { this->boundingVolume = boundingVolume; }
        void setCollisionCallback(std::function<void(Collider&)> callback) { collisionCallback = callback; }
        void setSolid(bool solid) { this->solid = solid; }
        void setIsOnAir(bool isOnAir) { this->onAir = isOnAir; }
        void setColliding(Vec3B collideAxisParam) { collidesAxis = collideAxisParam; }

        void setCollisionCallbackForCollider(Collider& collider, std::function<void(Collider&)> callback) {
            collisionCallbacks[&collider] = callback;
        }
        void addCollidingWith(Collider& collider) { collidingWith.push_back(&collider); }
        void setCollidingWith(const std::vector<Collider*>& colliders) { collidingWith = colliders; }

        bool isSolid() const { return solid; }
        bool isOnAir() const { return onAir; }
        Vec3B isColliding() const { return collidesAxis; }
        const auto& getGeneralCollisionCallback() const { return collisionCallback; }
        const auto& getSpecificCollisionCallbacks() const { return collisionCallbacks; }
        const Math::BoundingVolume& getBoundingVolume() const { return boundingVolume; }

        [[nodiscard]] std::vector<EntityStatsManager::Value> getDebuggingValues() override;
        [[nodiscard]] std::vector<EntityStatsManager::Value> getUpdatedDebuggingValues() override;

    private:
        std::function<void(Collider&)> collisionCallback;
        std::unordered_map<Collider*, std::function<void(Collider&)>> collisionCallbacks;
        GLESC::Math::BoundingVolume boundingVolume;
        bool solid = true;
        bool onAir = true;
        Vec3B collidesAxis{false, false, false};
#ifndef NDEBUG
        std::vector<Collider*> collidingWith;
#endif
    }; // class Collider
}
