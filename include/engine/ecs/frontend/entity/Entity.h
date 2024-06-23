/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "engine/ecs/backend/ECS.h"
#include "engine/ecs/ECSTypes.h"

namespace GLESC::ECS {
    class EntityFactory;
} // namespace GLESC::ECS

namespace GLESC::ECS {
    class Entity {
        /**
         * @brief The EntityFactory class is a friend of the Entity class.
         */
        friend class GLESC::ECS::EntityFactory;

    public:
        /**
         * @brief The entity will not be destroyed if the destructor is called
         * To destroy an entity, use the destroy() method
         */
        ~Entity() = default;

        EntityID getID() const { return ID; }

        /**
         * @brief Adds a component to the entity and returns a reference to it
         * The components is registered to the ECSManager
         * The entity signature is updated to reflect the new component
         * @tparam Component The type of the component
         */
        template <typename Component>
        Entity& addComponent();


        /**
         * @brief Removes a component from the entity
         * The entity signature is updated to reflect the removed component
         * @tparam Component
         */
        template <typename Component>
        Entity& removeComponent();

        /**
         * @brief Returns a reference to the component
         * @tparam Component The type of the component
         * @return A reference to the component
         */
        template <typename Component>
        [[nodiscard]] Component& getComponent() const;

        void destroy();

        /**
         * @brief Checks if the entity has a component
         * @tparam Component The type of the component
         * @return True if the entity has the component, false otherwise
         */
        template <typename Component>
        [[nodiscard]] bool hasComponent() const;

        /**
         * @brief Returns the entity's name
         * @return The entity's name
         */
        [[nodiscard]] EntityName getName() const;

        /**
         * @brief Checks if the entity is alive (if the ID of the entity is valid)
         */
        [[nodiscard]] bool isAlive() const;

    private:
        /**
         * @brief This constructor is internal to the ECS, it is used to create a new Entity
         * @param name The name of the entity
         */
        explicit Entity(const EntityName& name, const EntityMetadata& metadata,  ECSCoordinator& ecs);

        /**
         * @brief This constructor is internal to the ECS, it is used to create a new without a name
         * @param ecs The ECSManager
         */
        explicit Entity(ECSCoordinator& ecs);

        /**
         * @brief This constructor is internal to the ECS, it is used to cast an EntityID to an Entity
         * @param id
         */
        explicit Entity(EntityID id, ECSCoordinator& ecs);

        /**
         * @brief The entity's ID
         * The ID is used to identify the entity in the ECS
         */
        const EntityID ID;

        ECSCoordinator& ecs;
    }; // class Entity


    template <typename Component>
    Entity& Entity::addComponent() {
        ecs.addComponent<Component>(ID, Component());
        return *this;
    }

    template <typename Component>
    Entity& Entity::removeComponent() {
        ecs.removeComponent<Component>(ID);
        return *this;
    }

    template <typename Component>
    [[nodiscard]] Component& Entity::getComponent() const {
        return ecs.getComponent<Component>(ID);
    }

    template <typename Component>
    bool Entity::hasComponent() const {
        return ecs.hasComponent(ID, ecs.getComponentID<Component>());
    }
} // namespace GLESC::ECS
