/******************************************************************************
 * @file   EntityManager.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <queue>
#include <unordered_map>
#include <array>

#include "engine/core/asserts/Asserts.h"
#include "engine/ecs/ECSTypes.h"


namespace GLESC::ECS {
    class EntityManager {
        friend class ECS;

    public:
        /**
         * @brief Null entity with ID 0. This is used to indicate that an entity does not exist.
         */
        static constexpr EntityID nullEntity = EntityID(999999999);
        static constexpr EntityID firstEntity = EntityID(0);
        S_ASSERT_TRUE(firstEntity == 0, "First entity must be 0, ComponentArray uses the entity ID as index, "
                      "if edited this, it needs ComponentArray to be updated as well");
        const EntityName nullEntityName = EntityName{"NULL_ENTITY"};

        EntityManager();

        /**
         * @brief The default destructor is correct, no need to define it.
         */
        ~EntityManager() = default;

        const std::unordered_map<EntityName, EntityID>& getEntityNameToID() const { return entityNameToID; }
        const std::unordered_map<EntityID, EntityName>& getEntityIDToName() const { return entityIDToName; }
        const std::queue<EntityID>& getAvailableEntities() const { return availableEntities; }
        const std::array<Signature, maxEntities>& getSignatures() const { return signatures; }
        const EntityID& getLivingEntityCount() const { return livingEntityCount; }

        /**
         * @brief Create an entity with the given name. The name must be unique.
         * @param name
         * @return
         */
        EntityID createNextEntity(const EntityName& name);

        /**
         * @brief Tries to get the entity ID from the entity name
         * @details This will return the ID of the entity with the given name. If the entity does not exist,
         * it will return null entity (0).
         * @param name The name of the entity
         * @return The ID of the entity, or NULL_ENTITY if the entity does not exist
         */
        [[nodiscard]] EntityID tryGetEntity(const EntityName& name) const;

        /**
         * @brief Destroy the entity with the given ID. The entity must exist.
         * @param entity The ID of the entity
         */
        void destroyEntity(EntityID entity);

        /**
         * @brief Add a component to the entity. The entity must exist.
         * @param entity The ID of the entity
         * @param componentID The ID of the component
         */
        void addComponentToEntity(EntityID entity, ComponentID componentID);

        /**
         * @brief Remove a component from the entity. The entity must exist.
         * @param entity The ID of the entity
         * @param componentID The ID of the component
         */
        void removeComponentFromEntity(EntityID entity, ComponentID componentID);


        /**
         * @brief Get the signature of the entity. The entity must exist.
         * @param entity The ID of the entity
         * @return Copy of the signature of the entity
         */
        [[nodiscard]] Signature getSignature(EntityID entity) const;

        /**
         * @brief Get the entity name from the entity ID. The entity must exist.
         * @param entity The ID of the entity
         * @return The name of the entity
         */
        [[nodiscard]] const EntityName& getEntityName(EntityID entity) const;

        /**
         * @brief Get the entity ID from the entity name
         * @details This will return the ID of the entity with the given name. The entity must exist.
         * @param name The name of the entity
         * @return The ID of the entity
         */
        [[nodiscard]] EntityID getEntityID(const EntityName& name) const;


        /**
         * @brief Check if the entity has the given component. The entity must exist and
         * the component must be in the range of the signature.
         * @param entity
         * @param componentID
         * @return
         */
        [[nodiscard]] bool doesEntityHaveComponent(EntityID entity, ComponentID componentID) const;

        /**
         * @brief Check if the entity with the given name exists
         * @param name The name of the entity
         * @return True if the entity exists, false otherwise
         */
        [[nodiscard]] bool doesEntityExist(const EntityName& name) const;

        /**
         * @brief Check if the entity with the given ID exists
         * @param entity The ID of the entity
         * @return True if the entity exists, false otherwise
         */
        [[nodiscard]] bool doesEntityExist(EntityID entity) const;

        /**
         * @brief Check if the entity with the given ID is alive
         * @param entity The ID of the entity
         * @return True if the entity is alive, false otherwise
         */
        [[nodiscard]] bool isEntityAlive(EntityID entity) const;

        /**
         * @brief Check if the entity with the given name is alive
         * @param name The name of the entity
         * @return True if the entity is alive, false otherwise
         */
        [[maybe_unused]] [[nodiscard]] bool isEntityAlive(const EntityName& name) const;

        /**
         * @brief Check if the component ID is in the range of the signature
         * @return True if the component ID is in the range of the signature, false otherwise
         */
        [[maybe_unused]] [[nodiscard]] bool isComponentInRange(ComponentID componentID) const;

        /**
         * @brief Check if the entity can be created with the given name and the current state of the entity manager
         * @param name The name of the entity
         * @return True if the entity can be created, false otherwise
         */
        [[maybe_unused]] [[nodiscard]] bool canEntityBeCreated(const EntityName& name) const;

        [[maybe_unused]] [[nodiscard]] bool areThereLivingEntities() const;

    protected:
        /**
         * @brief Queue of the available entities, used to avoid iterating over all the entities
         */
        std::queue<EntityID> availableEntities;
        /**
         * @brief Array of the signatures of the entities
         * @details Signatures start all initialized to 0
         * @details The index of the array is the ID of the entity.
         */
        std::array<Signature, maxEntities> signatures;
        // TODO: Don't store the name of the entity in the entity manager
        //  It's a waste of memory, hash the name and store the hash instead
        std::unordered_map<EntityName, EntityID> entityNameToID;
        std::unordered_map<EntityID, EntityName> entityIDToName;
        /**
         * @brief The number of living entities
         */
        EntityID livingEntityCount{};
    }; // class EntityManager
} // namespace GLESC
