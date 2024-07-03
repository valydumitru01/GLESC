/**
 * @file   EntityFactory.h
 * @author valyd
 * @date   2024-03-29
 * @brief  * @brief @todo Add description of this file if needed
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 */

#pragma once
#include <optional>

#include "Entity.h"

namespace GLESC::ECS {
    /**
     * @brief The EntityFactory class is responsible for creating entity objects,
     * this helps avoid the need to pass the ECSManager to the entity constructor
     * every time an entity is created. Also, if the entity needs more complex
     * creation logic, it can be encapsulated in this class.
     */
    class EntityFactory {
    public:
        explicit EntityFactory(ECSCoordinator &ecs) : ecs(ecs) {}

        /**
         * @brief Creates an entity with a name and metadata
         * @details The entity is returned as value, because is just a wrapper around an ID
         * @param name The name of the entity
         * @param metadata The metadata of the entity
         * @return The created entity
         */
        Entity createEntity(const EntityName &name, const EntityMetadata& metadata);

        /**
         * @brief Creates an entity with a default name and no metadata
         * @details The entity is returned as value, because is just a wrapper around an ID
         * @return The created entity
         */
        Entity createEntity();

        /**
         * @brief Tries to get an entity by its name
         * @param name The name of the entity
         * @return The entity if it exists, otherwise std::nullopt
         */
        std::optional<Entity> tryGetEntity(const EntityName &name);

        /**
         * @brief Gets an entity by its name
         * @details The entity is returned as value, because is just a wrapper around an ID
         * @param name The name of the entity
         * @return The entity
         */
        Entity getEntity(const EntityName &name);
        /**
         * @brief Gets an entity by its ID
         * @details The entity is returned as value, because is just a wrapper around an ID
         * @param id The ID of the entity
         * @return The entity
         */
        Entity getEntity(const EntityID &id);

    private:
        ECSCoordinator &ecs;
    }; // class EntityFactory
}
