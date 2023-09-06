/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once
#include "engine/ecs/ECSTypes.h"
#include "engine/ecs/backend/component/components/ComponentArray.h"
#include "engine/ecs/backend/asserts/component/ComponentAsserts.h"

namespace GLESC {
    class ComponentManager {
        friend void printComponentStatus(const ComponentManager& componentManager) noexcept;

    public:
        ComponentManager() = default;
        
        template<typename Component>
        void registerComponent();
        
        template<typename Component>
        void registerComponentIfNotRegistered();
        
        template<typename Component>
        bool isComponentRegistered();
        
        template<typename Component>
        ComponentID getComponentID();
        
        template<typename Component>
        void addComponent(EntityID entity, Component component);
        
        template<typename Component>
        void removeComponent(EntityID entity);
        
        template<typename Component>
        Component &getComponent(EntityID entity);
        
        void entityDestroyed(EntityID entity);
        
        ~ComponentManager() = default;
    private:
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
         * @brief ID of the next component to be registered. It is incremented after each component is registered.
         */
        ComponentID nextComponentID{};
        
        /**
         * @brief Gets the component array of a component. The component must be registered and must be a component.
         * @tparam Component The type of the component
         * @return A shared pointer to the component array of the component
         */
        template<typename Component>
        std::shared_ptr<ComponentArray<Component>> getComponentArray();
        
    };
    
}
/**
 * @details The unusual position of the include is to avoid circular dependencies, since the ComponentManagerDebugger
 * includes the ComponentManager and the component manager implementation needs the inclusion of the
 * ComponentManagerDebugger.
 */
#include "engine/ecs/backend/debugger/component/ComponentManagerDebugger.h"

template<typename Component>
bool GLESC::ComponentManager::isComponentRegistered() {
    return componentArrays.find(typeid(Component).name()) != componentArrays.end();
}

template<typename Component>
void GLESC::ComponentManager::registerComponent() {
    ASSERT_IS_COMPONENT(Component);
    ASSERT_IS_COMPONENT_NOT_REGISTERED(Component);
    PRINT_COMPONENTS_STATUS(*this, "Before registering component");
    
    const char *typeName = typeid(Component).name();
    componentArrays.try_emplace(typeName, std::make_shared<ComponentArray<Component>>());
    componentIDs.try_emplace(typeName, nextComponentID);
    ++nextComponentID;
    
    PRINT_COMPONENTS_STATUS(*this, "After component registered");
}

template<typename Component>
ComponentID GLESC::ComponentManager::getComponentID() {
    ASSERT_IS_COMPONENT(Component);
    ASSERT_IS_COMPONENT_REGISTERED(Component);
    const char *typeName = typeid(Component).name();
    return componentIDs[typeName];
}

template<typename Component>
void GLESC::ComponentManager::addComponent(EntityID entity, Component component) {
    // No need for asserts or printing, they are already done in the functions called
    registerComponentIfNotRegistered<Component>();
    getComponentArray<Component>()->insertData(entity, component);
}

template<typename Component>
void GLESC::ComponentManager::removeComponent(EntityID entity) {
    ASSERT_IS_COMPONENT(Component);
    ASSERT_IS_COMPONENT_REGISTERED(Component);
    PRINT_COMPONENTS_STATUS(*this, "Before removing component");
    getComponentArray<Component>()->removeData(entity);
    PRINT_COMPONENTS_STATUS(*this, "After removing component");
}

template<typename Component>
Component &GLESC::ComponentManager::getComponent(EntityID entity) {
    ASSERT_IS_COMPONENT(Component);
    ASSERT_IS_COMPONENT_REGISTERED(Component);
    return getComponentArray<Component>()->getData(entity);
}

template<typename Component>
void GLESC::ComponentManager::registerComponentIfNotRegistered() {
    // No need for asserts or printing, they are already done in the functions called
    if (!isComponentRegistered<Component>()) {
        registerComponent<Component>();
    }
}

template<typename Component>
std::shared_ptr<ComponentArray<Component>> GLESC::ComponentManager::getComponentArray() {
    ASSERT_IS_COMPONENT(Component);
    ASSERT_IS_COMPONENT_REGISTERED(Component);
    
    const char *typeName = typeid(Component).name();
    std::shared_ptr<IComponentArray> ptr = componentArrays[typeName];
    return std::static_pointer_cast<ComponentArray<Component>>(ptr);
}