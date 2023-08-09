/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "engine/ecs/ECSTypes.h"
#include "engine/ecs/backend/system/SystemManager.h"
#include "engine/ecs/backend/entity/EntityManager.h"
#include "engine/ecs/backend/component/ComponentManager.h"

namespace GLESC {
    class Coordinator {
    public:
        Coordinator() = default;
        
        EntityID createEntity(EntityName name);
        
        void destroyEntity(EntityID entity);
        
        template<class Component>
        void registerComponent();
        
        template<class Component>
        void addComponent(EntityID entity, Component component);
        
        template<class Component>
        void removeComponent(EntityID entity);
        
        template<class Component>
        Component &getComponent(EntityID entity);
        
        template<class Component>
        ComponentID getComponentID();
        
        void registerSystem(SystemName name);
        
        template<typename System>
        bool doesEntityHaveComponent(EntityID entity);
        
        EntityID getEntityID(EntityName name);
        
        /**
         * @brief Add a component requirement to the system
         * @details This will add a component requirement to the system, therefore the system will only
         * run on entities that have the required components. This will also update the signature of the system.
         * @tparam T The type of the component
         * @param name The name of the system
         * @param componentID The ID of the component
         */
        template<typename T>
        void addComponentRequirementToSystem(SystemName name);
        
        EntityName getEntityName(EntityID entity);
        
        [[nodiscard]] std::set<EntityID> getAssociatedEntities(SystemName name);
    
    private:
        ComponentManager componentManager;
        SystemManager systemManager;
        EntityManager entityManager;
    }; // class Coordinator
    
    class ECS {
    public:
        static std::shared_ptr<Coordinator> getECS() {
            static std::shared_ptr<Coordinator> coordinator;
            return coordinator;
        }
    }; // class ECS
    
    template<typename Component>
    void Coordinator::registerComponent() {
        componentManager.registerComponent<Component>();
    }
    
    template<typename Component>
    void Coordinator::addComponent(EntityID entity, Component component) {
        componentManager.addComponent<Component>(entity, component);
    }
    
    template<class Component>
    void Coordinator::removeComponent(EntityID entity) {
        componentManager.removeComponent<Component>(entity);
        
        systemManager.entitySignatureChanged(entity, entityManager.getSignature(entity));
    }
    
    template<class Component>
    Component &Coordinator::getComponent(EntityID entity) {
        return componentManager.getComponent<Component>(entity);
    }
    
    template<class Component>
    ComponentID Coordinator::getComponentID() {
        return componentManager.getComponentID<Component>();
    }
    
    template<typename Component>
    void Coordinator::addComponentRequirementToSystem(SystemName name) {
        Signature newSignature;
        newSignature.set(componentManager.getComponentID<Component>());
        systemManager.setSignature(name, newSignature);
    }
    
    template<typename System>
    bool Coordinator::doesEntityHaveComponent(EntityID entity) {
        return entityManager.doesEntityHaveComponent(entity, componentManager.getComponentID<System>());
    }
    
    
} // namespace GLESC




