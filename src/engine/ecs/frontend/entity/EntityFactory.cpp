/**
 * @file   EntityFactory.cpp
 * @author valyd
 * @date   2024-03-29
 * @brief  * @brief @todo Add description of this file if needed
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 */
#include "engine/ecs/frontend/entity/EntityFactory.h"

namespace GLESC::ECS {
    Entity EntityFactory::createEntity(const EntityName& name, const EntityMetadata& metadata) {
        return Entity(name, metadata, ecs);
    }

    Entity EntityFactory::createEntity() {
        return Entity(ecs);
    }

    std::optional<Entity> EntityFactory::tryGetEntity(const EntityName& name) {
        if (ecs.tryGetEntityID(name) == EntityManager::nullEntity)
            return std::nullopt;
        return Entity(ecs.tryGetEntityID(name), ecs);
    }

    Entity EntityFactory::getEntity(const EntityName& name) {
        return Entity(ecs.getEntityID(name), ecs);
    }

    Entity EntityFactory::getEntity(const EntityID& id) {
        return Entity(id, ecs);
    }
}
