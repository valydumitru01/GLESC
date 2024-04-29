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
        friend class ECSDebugger;
        // Global namespace is necessary, IDE doesn't recognize it as an error and compiler complains, I found this
        // error by sheer luck
        friend class ::ECSTests;

    public:
        ECSCoordinator() = default;

        /**
         * @brief Create an entity with the given name. The name must be unique.
         * @param name The name of the entity
         * @return The ID of the entity or NULL_ENTITY if the entity name already exists.
         */
        EntityID createEntity(const EntityName& name);

        /**
         * @brief Destroy an entity
         * @param entity The ID of the entity
         * @return True if the entity was destroyed, false if the entity does not exist
         */
        bool destroyEntity(EntityID entity);
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
        /**
         * @brief Tries to get the entity ID from the entity name.
         * @details This will return the ID of the entity with the given name. If the entity does not exist,
         * it will return NULL_ENTITY.
         * @param name The name of the entity
         * @return The ID of the entity, or NULL_ENTITY if the entity does not exist
         */
        EntityID tryGetEntityID(const EntityName& name) const;


        template <class Component>
        void addComponent(EntityID entity, Component component);


        template <class Component>
        void removeComponent(EntityID entity);

        template <typename System>
        bool hasComponent(EntityID entity) const;

        template <class Component>
        ComponentID getComponentID() const;

        template <class Component>
        Component& getComponent(EntityID entity) const;

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

        [[nodiscard]] const std::unordered_map<EntityName, EntityID>& getAllEntities() const;

    protected:
        void printStatus(const std::string& contextMessage = "");
        void printEntity(EntityID entity);
        ComponentManager componentManager{};
        SystemManager systemManager{};
        EntityManager entityManager{};
    }; // class ECS


    template <typename Component>
    void ECSCoordinator::addComponent(EntityID entity, Component component) {
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
        return componentManager.getComponent<Component>(entity);
    }

    template <class Component>
    ComponentID ECSCoordinator::getComponentID() const {
        return componentManager.getComponentID<Component>();
    }

    template <typename Component>
    void ECSCoordinator::addComponentRequirementToSystem(const SystemName& name) {
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
