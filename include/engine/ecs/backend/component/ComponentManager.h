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

        const std::unordered_map<ComponentName, IComponentArrayPtr> &getComponentArrays() const {
            return componentArrays;
        }

        const std::unordered_map<ComponentName, ComponentID> &getComponentIDs() const {
            return componentIDs;
        }

        const ComponentID &getNextComponentID() const {
            return nextComponentID;
        }

        template<typename Component>
        ComponentID getComponentID() const;

        ComponentName getComponentName(ComponentID componentID) const;

        IComponent &getComponent(EntityID entity, ComponentID componentID) const;

        template<typename Component>
        Component &getComponent(EntityID entity) const;

        template<typename Component>
        void registerComponent();

        template<typename Component>
        void registerComponentIfNotRegistered();

        template<typename Component>
        void addComponentToEntity(EntityID entity, Component component);

        template<typename Component>
        void removeComponent(EntityID entity);

        template<typename Component>
        bool isComponentRegistered() const;

        bool isComponentRegistered(ComponentID componentID) const;

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
        template<typename Component>
        std::shared_ptr<ComponentArray<Component>> getComponentArray() const;
    };

    template<typename Component>
    Component &ComponentManager::getComponent(EntityID entity) const {
        S_ASSERT_TRUE((std::is_base_of_v<IComponent, Component>), "Component must inherit from IComponent");
        D_ASSERT_TRUE(isComponentRegistered<Component>(), "Component is not registered");
        D_ASSERT_TRUE(getComponentArray<Component>()->hasComponent(entity), "Entity does not have component");
        return getComponentArray<Component>()->getData(entity);
    }

    template<typename Component>
    bool ComponentManager::isComponentRegistered() const {
        auto name = typeid(Component).name();
        return componentArrays.find(name) !=
               componentArrays.end();
    }

    template<typename Component>
    ComponentID ComponentManager::getComponentID() const {
        S_ASSERT_TRUE((std::is_base_of_v<IComponent, Component>), "Component must inherit from IComponent");
        D_ASSERT_TRUE(isComponentRegistered<Component>(), "Component is not registered");
        const char *typeName = typeid(Component).name();
        return componentIDs.at(typeName);
    }


    template<typename Component>
    void ComponentManager::registerComponent() {
        S_ASSERT_TRUE((std::is_base_of_v<IComponent, Component>), "Component must inherit from IComponent");
        D_ASSERT_TRUE(!isComponentRegistered<Component>(), "Component is already registered");

        const char *typeName = typeid(Component).name();
        componentArrays.try_emplace(typeName,
                                    std::make_shared<ComponentArray<Component>>());
        componentIDs.insert({typeName, nextComponentID});
        componentNames.insert({nextComponentID, typeName});

        ++nextComponentID;
    }

    template<typename Component>
    void
    ComponentManager::addComponentToEntity(EntityID entity, Component component) {
        // No need for asserts or printing, they are already done in the functions called
        registerComponentIfNotRegistered<Component>();
        getComponentArray<Component>()->insertData(entity, component);
    }

    template<typename Component>
    void ComponentManager::removeComponent(EntityID entity) {
        S_ASSERT_TRUE((std::is_base_of_v<IComponent, Component>), "Component must inherit from IComponent");
        D_ASSERT_TRUE(isComponentRegistered<Component>(), "Component is not registered");
        D_ASSERT_TRUE(getComponentArray<Component>()->hasComponent(entity), "Entity does not have component");
        getComponentArray<Component>()->removeData(entity);
    }

    template<typename Component>
    void ComponentManager::registerComponentIfNotRegistered() {
        // No need for asserts or printing,
        // they are already done in the functions called
        if (!isComponentRegistered<Component>()) {
            registerComponent<Component>();
        }
    }

    template<typename Component>
    std::shared_ptr<ComponentArray<Component>>
    ComponentManager::getComponentArray() const {
        S_ASSERT_TRUE((std::is_base_of_v<IComponent, Component>), "Component must inherit from IComponent");
        D_ASSERT_TRUE(isComponentRegistered<Component>(), "Component is not registered");

        const char *typeName = typeid(Component).name();
        return std::static_pointer_cast<ComponentArray<Component>>(componentArrays.at(typeName));
    }
}
