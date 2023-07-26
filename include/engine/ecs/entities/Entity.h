#pragma once

#include "engine/ecs/ECSTypes.h"
#include "engine/ecs/ECSContainer.h"
#include "engine/ecs/components/ComponentArray.h"
#include "engine/ecs/components/RenderComponent.h"
#include "engine/core/asserts/Asserts.h"

#include <memory>
#include <cassert>
#include <queue>
#include <array>
#include <unordered_map>


class Entity {


public:
    Entity() {
        ASSERT(ECS::getECS()->canEntityBeCreated(), "Too many entities in existence.");
        // TODO: Create a method in ECSContainer called create entity
        // Take an ID from the front of the queue
        ID = ECS::getECS()->getNextEntity();
        Logger::get().info("Entity created with ID: " + std::to_string(ID));
    }
    
    ~Entity() {
        Logger::get().info("Entity destroyed with ID: " + std::to_string(ID));
        ECS::getECS()->destroyEntity(ID);
    }
    
    /**
     * @brief Adds a component to the entity and returns a reference to it
     * The components is registered to the ECSManager
     * The entity signature is updated to reflect the new component
     * @tparam T
     */
    template <typename T>
    Entity& addComponent(T &&component) {
        // TODO: Create a method in ECSContainer called add component to entity
        // Add the component to the entity
        ECS::getECS()->addComponentToEntitySignature(ID, ECS::getECS()->getComponentID <T>());
        // Register the component to the array for the component type
        ECS::getECS()->addComponent(ID, component);
        ECS::getECS()->entitySignatureChanged();
        return *this;
    }
    
    
    /**
     * @brief Removes a component from the entity
     * The entity signature is updated to reflect the removed component
     *
     * @tparam T
     */
    template <typename T>
    void removeComponent() {
        // TODO: Create a method in ECSContainer called remove component from entity
        ECS::getECS()->getComponentArray <T>()->entityDestroyed(ID);
        ECS::getECS()->entitySignatureChanged();
    }
    
    /**
     * @brief Returns a reference to the component
     * @tparam T
     * @return
     */
    template <typename T>
    inline T &getComponent() const {
        // TODO: Create a method in ECSContainer called get component from entity
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


