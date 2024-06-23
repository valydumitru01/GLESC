/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "engine/ecs/ECSTypes.h"
#include "ComponentArray.h"
#include "engine/core/asserts/Asserts.h"

namespace GLESC::ECS {
    class ComponentManager {
        friend class ECSCoordinator;

    public:
        /**
         * @brief The first component ID is zero, this is because signatures are just a bitset, and the first bit is the
         * 'zeroth' bit, so std::bitset bitset[0] is the first bit.
         */
        static constexpr ComponentID firstComponentID = 0;

        ComponentManager() = default;

        const std::unordered_map<ComponentName, IComponentArrayPtr>& getComponentArrays() const {
            return componentArrays;
        }

        const std::unordered_map<ComponentName, ComponentID>& getComponentIDs() const {
            return componentIDs;
        }

        const ComponentID& getNextComponentID() const {
            return nextComponentID;
        }

        /**
         * @brief Get the ID of a component by its type.
         * @tparam Component The type of the component.
         * @return The ID of the component.
         */
        template <typename Component>
        ComponentID getComponentID() const;

        /**
         * @brief Get the name of a component by its ID.
         * @param componentID The ID of the component.
         * @return The name of the component.
         */
        ComponentName getComponentName(ComponentID componentID) const;

        /**
         * @brief Get the component of an entity by its ID.
         * @param entity The ID of the entity.
         * @param componentID The ID of the component.
         * @return The component.
         */
        IComponent& getComponent(EntityID entity, ComponentID componentID) const;

        /**
         * @brief Get the component of an entity by its Id
         * @tparam Component The type of the component
         * @param entity The ID of the entity
         * @return The component
         */
        template <typename Component>
        Component& getComponent(EntityID entity) const;

        /**
         * @brief Register a component.
         * @details When a component is registered, it is added to the component arrays and it is assigned an ID.
         * @tparam Component The type of the component.
         */
        template <typename Component>
        void registerComponent();

        /**
         * @brief Register a component if it is not already registered. If it is already registered, does nothing.
         * @tparam Component The type of the component.
         */
        template <typename Component>
        void registerComponentIfNotRegistered();

        /**
         * @brief Add a component to an entity.
         * @details The component must be registered before adding it to an entity.
         * Adding a component to an entity means adding a new component to the array of components of that type.
         * And assigning the component to the entity inside the component array.
         * @tparam Component The type of the component.
         * @param entity The ID of the entity.
         * @param component The component to add.
         */
        template <typename Component>
        void addComponentToEntity(EntityID entity, const Component& component);

        /**
         * @brief Remove a component from an entity.
         * @details Removing a component from an entity means removing the component from the array of components of
         * that type and removing the component from the entity inside the component array.
         * @tparam Component The type of the component.
         * @param entity The ID of the entity.
         */
        template <typename Component>
        void removeComponent(EntityID entity);

        /**
         * @brief Check if a component is registered.
         * @tparam Component The type of the component.
         * @return True if the component is registered, false otherwise.
         */
        template <typename Component>
        bool isComponentRegistered() const;

        /**
         * @brief Check if a component is registered.
         * @param componentID The ID of the component.
         * @return True if the component is registered, false otherwise.
        */
        bool isComponentRegistered(ComponentID componentID) const;

        /**
         * @brief Alert the component manager that an entity has been destroyed.
         * @details This will alert all the component arrays that an entity has been destroyed amd they should remove
         * the entity from their arrays with their assigned components.
         * @param entity The ID of the entity.
         */
        void entityDestroyed(EntityID entity);

        ~ComponentManager() = default;

    protected:
        //TODO: Change the use of strings to something more lightweight
        /**
         * @brief Map from the name of a component to a component array that stores all the components of that type.
         */
        std::unordered_map<ComponentName, IComponentArrayPtr> componentArrays{};
        /**
         * @brief Map from the name of a component to the ID of that component.
         */
        std::unordered_map<ComponentName, ComponentID> componentIDs{};
        /**
         * @brief Map from the ID of a component to the name of that component.
         */
        std::unordered_map<ComponentID, ComponentName> componentNames{};
        /**
         * @brief ID of the next component to be registered. It is incremented after each component is registered.
         * @details It starts as 1, because it is needed for defining signatures and having it as as zero wouldn't
         * allow for signature definition.
         */
        ComponentID nextComponentID{firstComponentID};

        /**
         * @brief Gets the component array of a component. The component must be registered and must be a component.
         * @tparam Component The type of the component
         * @return A shared pointer to the component array of the component
         */
        template <typename Component>
        std::shared_ptr<ComponentArray<Component>> getComponentArray() const;
    };

    template <typename Component>
    Component& ComponentManager::getComponent(EntityID entity) const {
        auto componentArray = getComponentArray<Component>();
        S_ASSERT_TRUE((std::is_base_of_v<IComponent, Component>), "Component must inherit from IComponent");
        D_ASSERT_TRUE(isComponentRegistered<Component>(), "Component is not registered");
        D_ASSERT_TRUE(componentArray->hasComponent(entity),
                      "Entity does not have component. Add component first. "
                      "Check if you tried to get the component before adding it.")
        ;
        return componentArray->getData(entity);
    }

    template <typename Component>
    bool ComponentManager::isComponentRegistered() const {
        auto name = typeid(Component).name();
        return componentArrays.find(name) !=
            componentArrays.end();
    }

    template <typename Component>
    ComponentID ComponentManager::getComponentID() const {
        S_ASSERT_TRUE((std::is_base_of_v<IComponent, Component>), "Component must inherit from IComponent");
        D_ASSERT_TRUE(isComponentRegistered<Component>(), "Component is not registered");
        const char* typeName = typeid(Component).name();
        return componentIDs.at(typeName);
    }


    template <typename Component>
    void ComponentManager::registerComponent() {
        S_ASSERT_TRUE((std::is_base_of_v<IComponent, Component>), "Component must inherit from IComponent");
        D_ASSERT_TRUE(!isComponentRegistered<Component>(), "Component is already registered");

        const char* typeName = typeid(Component).name();
        componentArrays.try_emplace(typeName,
                                    std::make_shared<ComponentArray<Component>>());
        componentIDs.insert({typeName, nextComponentID});
        componentNames.insert({nextComponentID, typeName});

        ++nextComponentID;
    }

    template <typename Component>
    void
    ComponentManager::addComponentToEntity(EntityID entity, const Component& component) {
        // No need for asserts or printing, they are already done in the functions called
        registerComponentIfNotRegistered<Component>();
        getComponentArray<Component>()->insertData(entity, component);
    }

    template <typename Component>
    void ComponentManager::removeComponent(EntityID entity) {
        S_ASSERT_TRUE((std::is_base_of_v<IComponent, Component>), "Component must inherit from IComponent");
        D_ASSERT_TRUE(isComponentRegistered<Component>(), "Component is not registered");
        D_ASSERT_TRUE(getComponentArray<Component>()->hasComponent(entity), "Entity does not have component");
        getComponentArray<Component>()->removeData(entity);
    }

    template <typename Component>
    void ComponentManager::registerComponentIfNotRegistered() {
        // No need for asserts or printing,
        // they are already done in the functions called
        if (!isComponentRegistered<Component>()) {
            registerComponent<Component>();
        }
    }

    template <typename Component>
    std::shared_ptr<ComponentArray<Component>>
    ComponentManager::getComponentArray() const {
        S_ASSERT_TRUE((std::is_base_of_v<IComponent, Component>), "Component must inherit from IComponent");
        D_ASSERT_TRUE(isComponentRegistered<Component>(), "Component is not registered");

        const char* typeName = typeid(Component).name();
        return std::static_pointer_cast<ComponentArray<Component>>(componentArrays.at(typeName));
    }
}
