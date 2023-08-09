/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "engine/ecs/ECSTypes.h"
#include "engine/ecs/backend/component/components/ComponentArray.h"
#include "engine/ecs/backend/asserts/component/ComponentAsserts.h"
#include "engine/ecs/backend/debugger/component/ComponentManagerDebugger.h"

namespace GLESC {
    class ComponentManager {
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
        /**
         * @brief Map which contains component arrays
         * @details This is used to store the component arrays for each component type
         * Key -> Name of the component i.e. "PhysicsComponent"
         * Value -> Pair <ComponentArray (containing all the components of the same type), ComponentID>
         */
        std::unordered_map<ComponentName, std::pair<IComponentArrayPtr, ComponentID>> componentArrays{};
        ComponentID nextComponentID{};
        
        template<typename Component>
        std::shared_ptr<ComponentArray<Component>> getComponentArray();
    };
}

template<typename Component>
bool GLESC::ComponentManager::isComponentRegistered() {
    return componentArrays.find(typeid(Component).name()) != componentArrays.end();
}

template<typename Component>
void GLESC::ComponentManager::registerComponent() {
    ASSERT_IS_COMPONENT(Component);
    ASSERT_IS_COMPONENT_NOT_REGISTERED(Component);
    PRINT_COMPONENTS_STATUS( componentArrays, nextComponentID, "Before registering component" );
    
    const char *typeName = typeid(Component).name();
    
    componentArrays.insert({typeName, std::make_pair(IComponentArrayPtr(), nextComponentID)});
    
    ++nextComponentID;
    PRINT_COMPONENTS_STATUS( componentArrays, nextComponentID, "After component registered" );
}

template<typename Component>
ComponentID GLESC::ComponentManager::getComponentID() {
    ASSERT_IS_COMPONENT(Component);
    ASSERT_IS_COMPONENT_REGISTERED(Component);
    const char *typeName = typeid(Component).name();
    return componentArrays[typeName].second;
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
    PRINT_COMPONENTS_STATUS( componentArrays, nextComponentID, "Before removing component" );
    getComponentArray<Component>()->removeData(entity);
    PRINT_COMPONENTS_STATUS( componentArrays, nextComponentID, "After removing component" );
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
    if (isComponentRegistered<Component>()) {
        registerComponent<Component>();
    }
}

template<typename Component>
std::shared_ptr<ComponentArray<Component>> GLESC::ComponentManager::getComponentArray() {
    ASSERT_IS_COMPONENT(Component);
    ASSERT_IS_COMPONENT_REGISTERED(Component);
    
    const char *typeName = typeid(Component).name();
    std::shared_ptr<IComponentArray> ptr = componentArrays[typeName].first;
    return std::static_pointer_cast<ComponentArray<Component>>(ptr);
}