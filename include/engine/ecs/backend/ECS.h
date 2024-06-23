/*******************************************************************************
 * @file   ECS.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <mutex>
#include <shared_mutex>

#include "engine/ecs/ECSTypes.h"
#include "engine/ecs/backend/system/SystemManager.h"
#include "engine/ecs/backend/entity/EntityManager.h"
#include "engine/ecs/backend/component/ComponentManager.h"

#ifndef NDEBUG_ECS
#define PRINT_ECS_STATUS(contextMessage) printStatus(contextMessage)
#else
#define PRINT_ECS_STATUS(contextMessage)
#endif


class ECSTests;

namespace GLESC::ECS {
    class ECSCoordinator {
        friend class ::ECSTests;
        friend class ECSDebugger;

    public:
        ECSCoordinator() = default;

        /**
         * @brief Create an entity with the given name. The name must be unique.
         * @param name The name of the entity
         * @return The ID of the entity or NULL_ENTITY if the entity name already exists.
         */
        EntityID createEntity(const EntityName& name, const EntityMetadata& metadata);

        /**
         * @brief Create an entity with a default name
         * @return The ID of the entity
         */
        EntityID createEntity();

        /**
         * @brief Mark entity to be destroyed
         * @details Destruction in the ECS is deferred to the end of the frame. This is to avoid
         * invalidating iterators while iterating over the entities.
         */
        void markForDestruction(EntityID entity);

        const std::vector<EntityID>& getEntitiesToBeDestroyed() const {
            return entitiesToDestroy;
        }

        /**
         * @brief Destroy all entities marked for destruction
         */
        void destroyEntities();

        /**
         * @brief Get the entity ID from the entity name
         * @param name The name of the entity
         * @return The ID of the entity with the given name or NULL_ENTITY if the entity does not exist
         */
        EntityID getEntityID(const EntityName& name) const;
        /**
         * @brief Get the name of the entity given the ID
         * @param entity The ID of the entity
         * @return The name of the entity or nullptr if the entity does not exist
         */
        const EntityName& getEntityName(EntityID entity) const;

        bool isEntityAlive(EntityID entity) const;
        /**
         * @brief Tries to get the entity ID from the entity name.
         * @details This will return the ID of the entity with the given name. If the entity does not exist,
         * it will return NULL_ENTITY.
         * @param name The name of the entity
         * @return The ID of the entity, or NULL_ENTITY if the entity does not exist
         */
        EntityID tryGetEntityID(const EntityName& name) const;

        /**
         * @brief Get the a list of entities that are instanced by the given instance name
         * @param name The name of the instance
         * @return A list of entity IDs that are instanced by the given instance name
         */
        const std::vector<EntityID>& getInstancedEntities(const EntityName& name) const;

        /**
         * @brief Get the metadata of the entity
         * @param entity The ID of the entity
         * @return The metadata of the entity
         */
        const EntityMetadata& getEntityMetadata(EntityID entity) const;

        /**
         * @brief Check if an entity is instanced
         * @details An entity is instanced if it's name is a name followed by a number
         * @param name The name of the entity
         * @return True if the entity is instanced, false otherwise
         */
        bool isEntityInstanced(const EntityName& name) const;

        /**
         * @brief Add a component to an entity.
         * @details This will store the component in a contiguous memory block and update the entity's signature.
         * If the component is already added to the entity, nothing happens.
         * @tparam Component The type of the component
         * @param entity The ID of the entity
         * @param component The component to add
         */
        template <class Component>
        void addComponent(EntityID entity,const Component& component);

        /**
         * @brief Remove a component from an entity.
         * @details This will remove the component from the entity's signature and from the component array.
         * If the component is not added to the entity, nothing happens.
         * @tparam Component The type of the component
         * @param entity The ID of the entity
         */
        template <class Component>
        void removeComponent(EntityID entity);

        /**
         * @brief Check if an entity has a component, checking it's signature.
         * @tparam System The type of the system
         * @param entity The ID of the entity
         * @return True if the entity has the component, false otherwise
         */
        template <typename System>
        bool hasComponent(EntityID entity) const;

        /**
         * @brief Get the ID of a component
         * @tparam Component The type of the component
         * @return The ID of the component
         */
        template <class Component>
        ComponentID getComponentID() const;

        /**
         * @brief Get the component of an entity by its Id
         * @tparam Component The type of the component
         * @param entity The ID of the entity
         * @return The component
         */
        template <class Component>
        Component& getComponent(EntityID entity) const;

        /**
         * @brief Get the components of an entity
         * @details This will return a vector of components that the entity has.
         * The components are pointers to the actual components stored in the component manager.
         * The pointers point to an interface, so the actual type of the component is unknown.
         * @param entityId The ID of the entity
         * @return A vector of components
         */
        std::vector<IComponent*> getComponents(EntityID entityId) const;


        /**
         * @brief Registers the system in the system manager so it can be used and updated.
         * If the system is already registered, nothing happens.
         * @param name The name of the system
         */
        void registerSystem(const SystemName& name);

        /**
         * @brief Add a component requirement to the system
         * @details This will add a component requirement to the system, therefore the system will only
         * run on entities that have the required components. This will also update the signature of the system.
         * @tparam Component The type of the component
         * @param name The name of the system
         */
        template <typename Component>
        void addComponentRequirementToSystem(const SystemName& name);
        /**
         * @brief Get the entities associated with a system
         * @param name The name of the system
         * @return A set of entities associated with the system or an empty set if the system does not exist
         */
        [[nodiscard]] const std::set<EntityID>&
        getAssociatedEntities(const SystemName& name) const;

        /**
         * @brief Get all the entities in the ECS
         * @return A map of entity names and their IDs
         */
        [[nodiscard]] const std::unordered_map<EntityName, EntityID>& getAllEntities() const;

        /**
         * @brief Destroy an entity, destroying all the components and removing it from the systems
         * @param entity The ID of the entity
         * @return True if the entity was destroyed, false if the entity does not exist
         */
        bool destroyEntity(EntityID entity);
    protected:

        /**
         * @brief Print the status of the ECS
         * @param contextMessage The message to print before the status
         */
        void printStatus(const std::string& contextMessage = "");
        /**
         * @brief Print the status of the entity
         * @param entity The ID of the entity
         */
        void printEntity(EntityID entity);
        /**
         * @brief Manager that handles the components.
         * @details It stores the components in contigous arrays and knows which component is linked to which entity.
         */
        ComponentManager componentManager{};
        /**
         * @brief Manager that handles the systems.
         * @details It stores the systems and their signatures and knows which entities are associated with which
         * system. It also knows which components are required by the system.
         */
        SystemManager systemManager{};
        /**
         * @brief Manager that handles the entities.
         * @details It stores the entities and their signatues. Also knows what entities are available and ensures
         * the entities are unique.
         */
        EntityManager entityManager{};
        /**
         * @brief The entities that are marked for destruction
         */
        std::vector<EntityID> entitiesToDestroy{};
        /**
         * @brief Mutex for the ECS
         * @details This mutex is used to lock the ECS when adding or removing components, entities or systems.
         * Ths ensures ECS is thread safe.
         */
        mutable std::shared_mutex ecsMutex{};
    }; // class ECS


    template <typename Component>
    void ECSCoordinator::addComponent(EntityID entity,const Component& component) {
        std::lock_guard<std::shared_mutex> lock(ecsMutex);
        PRINT_ECS_STATUS("Before adding component " + std::string(typeid(Component).name()) +
            "to entity with ID " + std::to_string(entity));
        componentManager.addComponentToEntity<Component>(entity, component);
        entityManager.addComponentToEntity(entity, componentManager.getComponentID<Component>());
        systemManager.entitySignatureChanged(entity,
                                             entityManager.getSignature(entity));
        PRINT_ECS_STATUS("After adding component " + std::string(typeid(Component).name()) +
            " to entity with ID " + std::to_string(entity));
    }

    template <class Component>
    void ECSCoordinator::removeComponent(EntityID entity) {
        std::lock_guard<std::shared_mutex> lock(ecsMutex);
        PRINT_ECS_STATUS("Before removing component " + std::string(typeid(Component).name()) +
            " from entity with ID " + std::to_string(entity));
        componentManager.removeComponent<Component>(entity);
        entityManager.removeComponentFromEntity(entity, componentManager.getComponentID<Component>());
        systemManager.entitySignatureChanged(entity,
                                             entityManager.getSignature(entity));
        PRINT_ECS_STATUS("After removing component " + std::string(typeid(Component).name()) +
            " from entity with ID " + std::to_string(entity));
    }

    template <class Component>
    Component& ECSCoordinator::getComponent(EntityID entity) const {
        D_ASSERT_TRUE(entityManager.doesEntityExist(entity), "Entity must exist");
        return componentManager.getComponent<Component>(entity);
    }

    template <class Component>
    ComponentID ECSCoordinator::getComponentID() const {
        return componentManager.getComponentID<Component>();
    }

    template <typename Component>
    void ECSCoordinator::addComponentRequirementToSystem(const SystemName& name) {
        std::lock_guard<std::shared_mutex> lock(ecsMutex);
        if (!systemManager.isSystemRegistered(name)) {
            Logger::get().warning("System " + name + " is not registered. Cannot add component requirement.");
            return;
        }
        PRINT_ECS_STATUS(
            std::string("Before adding component") + typeid(Component).name() + std::string(" to system ") + name);
        componentManager.registerComponentIfNotRegistered<Component>();
        systemManager.addComponentRequirementToSystem(name, componentManager.getComponentID<Component>());
        PRINT_ECS_STATUS(
            std::string("After adding component") + typeid(Component).name() + std::string(" to system ") + name);
    }

    template <typename Component>
    bool ECSCoordinator::hasComponent(EntityID entity) const {
        if (componentManager.isComponentRegistered<Component>()) {
            return entityManager.doesEntityHaveComponent(entity,
                                                         componentManager.getComponentID<Component>());
        }
        return false;
    }
} // namespace GLESC
