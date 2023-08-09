/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "engine/ecs/backend/Coordinator.h"
#include "engine/core/logger/Logger.h"
#include "engine/ecs/ECSTypes.h"

#include <memory>
#include <cassert>
#include <queue>
#include <array>
#include <unordered_map>

namespace GLESC {
    class Engine;
    class Entity {
        friend class GLESC::Engine;
    private:
        /**
         * @brief This constructor is internal to the ECS, it is used to create a new Entity
         * @param name The name of the entity
         */
        explicit Entity(EntityName name);
        /**
         * @brief This constructor is internal to the ECS, it is used to cast an EntityID to an Entity
         * @param id
         */
        explicit Entity(EntityID id);
    
        /**
         * @brief The entity's ID
         * The ID is used to identify the entity in the ECS
         */
        const EntityID ID;
    public:
        
        /**
         * @brief The entity will not be destroyed if the destructor is called
         * To destroy an entity, use the ECS class
         */
        ~Entity() = default;
        
        /**
         * @brief Adds a component to the entity and returns a reference to it
         * The components is registered to the ECSManager
         * The entity signature is updated to reflect the new component
         * @tparam T
         */
        template<typename Component>
        Entity &addComponent(Component &&component);
        
        
        /**
         * @brief Removes a component from the entity
         * The entity signature is updated to reflect the removed component
         *
         * @tparam T
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
        
        template<typename T>
        [[nodiscard]] bool hasComponent() const;
        
        [[nodiscard]] EntityName getName() const;
    }; // class Entity
} // namespace GLESC



template<typename Component>
GLESC::Entity &GLESC::Entity::addComponent(Component &&component) {
    GLESC::ECS::getECS()->addComponent<Component>(ID, component);
    return *this;
}

template<typename Component>
GLESC::Entity &GLESC::Entity::removeComponent() {
    GLESC::ECS::getECS()->removeComponent<Component>(ID);
    return *this;
}

template<typename Component>
[[nodiscard]] Component &GLESC::Entity::getComponent() const {
    return GLESC::ECS::getECS()->getComponent<Component>(ID);
}

template<typename Component>
bool GLESC::Entity::hasComponent() const {
    return GLESC::ECS::getECS()->doesEntityHaveComponent(ID, GLESC::ECS::getECS()->getComponentID<Component>());
}
