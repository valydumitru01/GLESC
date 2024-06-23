/******************************************************************************
* @file   System.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief System interface for all systems in the engine
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#pragma once

#include "engine/ecs/backend/ECS.h"
#include <set>

namespace GLESC::ECS {
    /**
     * @details Class that must be inherited by all systems in the engine.
     * This helps with the access to the entities that are related with the system
     * and facilitates the assignment of component requirements.
     */
    class System {
        friend class Entity;

    public:
        /**
         * @brief Constructs a system with a name and a reference to the ECS coordinator
         * @param ecs The ECS coordinator
         * @param name The name of the system
         */
        explicit System(ECSCoordinator &ecs, const SystemName &name);

        virtual ~System() = default;

        /**
         * @brief Adds a component requirement to the system
         * @details The component requirement makes so that only entities that have the required component
         * are considered associated with the system
         * @tparam Component The type of the component
         */
        template<class Component>
        void addComponentRequirement() {
            ecs.addComponentRequirementToSystem<Component>(name);
        }

        /**
         * @brief Updates the system
         * @details This method is called every frame
         * This must be implemented by the derived class, and the derived class must
         * know what to do with the entities that are associated with the system.
         */
        virtual void update() = 0;

        /**
         * @brief Gets the entities associated with the system
         * @details The entities are the ones that have all the required components
         * @return A set of entity IDs
         */
        [[nodiscard]] const std::set<EntityID> &getAssociatedEntities() const;

        /**
         * @brief Gets all the entities in the ECS
         * @details In case the system needs to access all the entities in the ECS
         * @return A map of entity names and IDs
         */
        [[nodiscard]] std::unordered_map<EntityName, EntityID> getAllEntities() const;

        /**
         * @brief Gets the components of an entity
         * @details This method is useful when the system needs to access the components of an entity
         * @param entityId The ID of the entity
         * @return A vector of pointers to the components
         */
        [[nodiscard]] std::vector<IComponent*> getComponents(EntityID entityId) const;

        /**
         * @brief Gets the name of an entity
         * @param entityId The ID of the entity
         * @return The name of the entity
         */
        [[nodiscard]] const EntityName& getEntityName(EntityID entityId) const;
        /**
         * @brief Gets the ID of an entity
         * @param entityName The name of the entity
         * @return The ID of the entity
         */
        [[nodiscard]] EntityID getEntity(const EntityName& entityName) const;
        /**
         * @brief Gets the metadata of an entity
         * @param entityId The ID of the entity
         * @return The metadata of the entity
         */
        [[nodiscard]] const EntityMetadata& getEntityMetadata(EntityID entityId) const;

    protected:
        /**
         * @brief Gets the component of an entity
         * @tparam Component The type of the component
         * @param entityId The ID of the entity
         * @return A reference to the component
         */
        template<class Component>
        Component &getComponent(EntityID entityId) {
            return ecs.getComponent<Component>(entityId);
        }

        /**
         * @brief Easy access to the value of nullEntity
         */
        EntityID nullEntity = EntityManager::nullEntity;

    private:
        /**
         * @brief Reference to the ECSCoordinator
         */
        ECSCoordinator &ecs;
        /**
         * @brief Easy access to the name of the system
         */
        SystemName name;
    };
}
