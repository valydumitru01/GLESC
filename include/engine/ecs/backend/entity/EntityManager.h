/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <queue>
#include <boost/bimap/bimap.hpp>
#include <boost/bimap.hpp>

#include "engine/ecs/ECSTypes.h"

/**
 * @brief Null entity with ID -1. This is used to indicate that an entity does not exist.
 */
#define NULL_ENTITY -1
namespace GLESC {
    class EntityManager {
    private:
        /**
         * @brief Queue of the available entities, used to avoid iterating over all the entities
         */
        std::queue<EntityID> availableEntities;
        /**
         * @brief Array of the signatures of the entities
         * @details The index of the array is the ID of the entity.
         */
        std::array<Signature, maxEntities> signatures;
        // TODO: Don't store the name of the entity in the entity manager
        //  It's a waste of memory, hash the name and store the hash instead
        boost::bimap<EntityName, EntityID> entityIDs;
        /**
         * @brief The number of living entities
         */
        EntityID livingEntityCount{};
    public:
        EntityManager();
        /**
         * @brief The default destructor is correct, no need to define it.
         */
        ~EntityManager() = default;
        /**
         * @brief Create an entity with the given name. The name must be unique.
         * @param name
         * @return
         */
        [[nodiscard]] EntityID createNextEntity(EntityName name);
        
        /**
         * @brief Destroy the entity with the given ID. The entity must exist.
         * @param entity The ID of the entity
         */
        void destroyEntity(EntityID entity);
        
        /**
         * @brief Get the signature of the entity. The entity must exist.
         * @param entity The ID of the entity
         * @return Copy of the signature of the entity
         */
        [[nodiscard]] Signature getSignature(EntityID entity) const;
        
        /**
         * @brief Check if the entity has the given component. The entity must exist and
         * the component must be in the range of the signature.
         * @param entity
         * @param componentID
         * @return
         */
        [[nodiscard]] bool doesEntityHaveComponent(EntityID entity, ComponentID componentID) const;
        /**
         * @brief Get the entity name from the entity ID. The entity must exist.
         * @param entity The ID of the entity
         * @return The name of the entity
         */
        [[nodiscard]] EntityName getEntityName(EntityID entity) const;
        
        /**
         * @brief Get the entity ID from the entity name
         * @details This will return the ID of the entity with the given name. The entity must exist.
         * @param name The name of the entity
         * @return The ID of the entity
         */
        [[nodiscard]] EntityID getEntity(EntityName name) const;
        /**
         * @brief Check if the entity with the given name exists
         * @param name The name of the entity
         * @return True if the entity exists, false otherwise
         */
        [[nodiscard]] bool doesEntityExist(EntityName name) const;
        
        /**
         * @brief Check if the entity with the given ID exists
         * @param entity The ID of the entity
         * @return True if the entity exists, false otherwise
         */
        [[nodiscard]] bool doesEntityExist(EntityID entity) const;
    }; // class EntityManager
    
} // namespace GLESC