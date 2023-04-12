#pragma once

#include "core/Types.h"
#include "core/ECSContainer.h"
#include "ecs/components/ComponentArray.h"
#include "ecs/components/RenderComponent.h"
#include "exceptions/EngineException.h"

#include <memory>
#include <cassert>
#include <queue>
#include <array>
#include <unordered_map>


class Entity {


public:
    Entity() {
#ifdef DEBUG
        assert(ECS::getECS()->canEntityBeCreated() && "Too many entities in existence.");
        assert(ECS::getECS()->areThereAvailableEntities() && "No available entities left");
#endif
        
        // Take an ID from the front of the queue
        ID = ECS::getECS()->getNextEntityID();
    }
    
    ~Entity() {
        ECS::getECS()->entityDestroyed(ID);
    }
    
    /**
     * @brief Adds a component to the entity and returns a reference to it
     * The components is registered to the ECSManager
     * The entity signature is updated to reflect the new component
     * @tparam T
     */
    template <typename T>
    void addComponent(T &&component) {
        // Add the component to the entity
        ECS::getECS()->addComponentToEntity(ID, ECS::getECS()->getComponentID <T>());
        // Register the component to the array for the component type
        ECS::getECS()->addComponent(ID, component);
        ECS::getECS()->entitySignatureChanged();
        
    }
    
    
    /**
     * @brief Removes a component from the entity
     * The entity signature is updated to reflect the removed component
     *
     * @tparam T
     */
    template <typename T>
    void removeComponent() {
        ECS::getECS()->getComponentArray <T>()->removeData(ID);
        ECS::getECS()->entitySignatureChanged();
    }
    
    /**
     * @brief Returns a reference to the component
     * @tparam T
     * @return
     */
    template <typename T>
    inline T &getComponent() const {
        return ECS::getECS()->getComponentArray <T>()->getData(ID);
    }
    
    
    template <typename T>
    [[nodiscard]] bool hasComponent() const {
        return ECS::getECS()->doesEntityHaveComponent(ID, ECS::getECS()->getComponentID <T>());
    }
    
    
    [[nodiscard]] bool isAlive() const {
        return ECS::getECS()->isEntityAlive(ID);
    }


private:
    /**
     * @brief The entity's ID
     * The ID is used to identify the entity in the ECSContainer
     */
    EntityID ID;
};


