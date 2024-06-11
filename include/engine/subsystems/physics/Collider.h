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
#include "Physics.h"
#include "engine/core/math/geometry/figures/BoundingVolume.h"
#include "engine/subsystems/EngineComponent.h"
#include "engine/subsystems/ingame-debug/EntityStatsManager.h"

namespace GLESC::Physics {
    class PhysicsManager;
}

namespace GLESC::Physics {
    class Collider : public EngineComponent {
        using CollisionCallback = std::function<void(Collider&)>;
        using SpecificCollisionCallbacks = std::unordered_map<Collider*, CollisionCallback>;
        friend class CollisionManager;

    public:
        Collider() = default;
        ~Collider() override = default;

        void setBoundingVolume(const Math::BoundingVolume& boundingVolume) { this->boundingVolume = boundingVolume; }
        void setCollisionCallback(std::function<void(Collider&)> callback) { collisionCallback = callback; }
        void setSolid(bool solid) { this->solid = solid; }

        void setCollisionInformation(const CollisionInformation& collisionInformation) {
            this->collisionInformation = collisionInformation;
        }


        CollisionInformation& getCollisionInformation() const { return collisionInformation; }
        const CollisionCallback& getGeneralCollisionCallback() const { return collisionCallback; }
        const SpecificCollisionCallbacks& getSpecificCollisionCallbacks() const { return collisionCallbacks; }
        bool isSolid() const { return solid; }
        const Math::BoundingVolume& getBoundingVolume() const { return boundingVolume; }

        [[nodiscard]] std::vector<EntityStatsManager::Value> getDebuggingValues() override;
        [[nodiscard]] std::vector<EntityStatsManager::Value> getUpdatedDebuggingValues() override;
        [[nodiscard]] std::string toString() const override;

    private:
        CollisionCallback collisionCallback;
        SpecificCollisionCallbacks collisionCallbacks;
        Math::BoundingVolume boundingVolume;
        mutable CollisionInformation collisionInformation;

        bool solid = true;
    }; // class Collider
}
