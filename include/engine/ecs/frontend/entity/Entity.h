/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "engine/ecs/backend/ECS.h"
#include "engine/core/logger/Logger.h"
#include "engine/ecs/ECSTypes.h"


namespace GLESC {
    class Engine;
    class Entity {
        /**
         * @brief The Engine class needs to access the Entity's constructor, it acts as a factory
         */
        friend class GLESC::Engine;
    private:
        /**
         * @brief This constructor is internal to the ECS, it is used to create a new Entity
         * @param name The name of the entity
         */
        explicit Entity(const EntityName& name, ECS& ecs);
        /**
         * @brief This constructor is internal to the ECS, it is used to cast an EntityID to an Entity
         * @param id
         */
        explicit Entity(EntityID id, ECS& ecs);
    
        /**
         * @brief The entity's ID
         * The ID is used to identify the entity in the ECS
         */
        const EntityID ID;
        
        ECS& ecs;
    public:
        
        /**
         * @brief The entity will not be destroyed if the destructor is called
         * To destroy an entity, use the destroy() method
         */
        ~Entity() = default;
        
        /**
         * @brief Adds a component to the entity and returns a reference to it
         * The components is registered to the ECSManager
         * The entity signature is updated to reflect the new component
         * @tparam Component The type of the component
         */
        template<typename Component>
        Entity &addComponent(Component &&component);
        
        
        /**
         * @brief Removes a component from the entity
         * The entity signature is updated to reflect the removed component
         * @tparam Component
         */
        template<typename Component>
        Entity &removeComponent();
        
        /**
         * @brief Returns a reference to the component
         * @tparam Component The type of the component
         * @return A reference to the component
         */
        template<typename Component>
        [[nodiscard]] Component &getComponent() const;
        
        void destroy();
        /**
         * @brief Checks if the entity has a component
         * @tparam Component The type of the component
         * @return True if the entity has the component, false otherwise
         */
        template<typename Component>
        [[nodiscard]] bool hasComponent() const;
        /**
         * @brief Returns the entity's name
         * @return The entity's name
         */
        [[nodiscard]] EntityName getName() const;
    }; // class Entity
} // namespace GLESC



template<typename Component>
GLESC::Entity &GLESC::Entity::addComponent(Component &&component) {
    ecs.addComponent<Component>(ID, std::forward<Component>(component));
    return *this;
}

template<typename Component>
GLESC::Entity &GLESC::Entity::removeComponent() {
    ecs.removeComponent<Component>(ID);
    return *this;
}

template<typename Component>
[[nodiscard]] Component &GLESC::Entity::getComponent() const {
    return ecs.getComponent<Component>(ID);
}

template<typename Component>
bool GLESC::Entity::hasComponent() const {
    return ecs.doesEntityHaveComponent(ID, ecs.getComponentID<Component>());
}
