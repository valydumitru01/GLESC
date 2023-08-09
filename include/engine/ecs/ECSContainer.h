
/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <memory>
#include <unordered_map>
#include <array>
#include <vector>
#include <queue>
#include <set>

#include "ECSTypes.h"
#include "engine/ecs/backend/component/components/ComponentArray.h"
#include "engine/core/logger/Logger.h"
#include "engine/core/asserts/Asserts.h"


class Component;

class ECSContainers {
    friend class ECS;

public:
    // --------------------------------------------------------------
    // ------------------------ Systems -----------------------------
    
    /**
     * @brief Registers the system into the ECS
     * @tparam T The system class
     * @param name The name of the system
     * @return Copy of the entities associated with the system
     */
    [[nodiscard]] std::set<EntityID> getAssociatedEntities(const std::string &name) const;
    
    /**
     * @brief Registers the system into the ECS
     * @param name The name of the system
     */
    void registerSystem(const std::string &name);
    
    /**
     * @brief Checks if the system is registered
     * @param name The name of the system
     * @return True if the system is registered, false otherwise
     */
    [[nodiscard]] bool systemIsRegistered(const std::string &name) const;
    
    /**
     * @brief Gets the signature of the system
     * @param name The name of the system
     * @return The signature of the system as a bitset
     */
    [[nodiscard]] Signature getSignature(const std::string &name) const;
    
    /**
     * @brief Add a component requirement to the system
     * @details This will add a component requirement to the system, therefore the system will only
     * run on entities that have the required components. This will also update the signature of the system.
     * @tparam T The type of the component
     * @param name The name of the system
     * @param componentID The ID of the component
     */
    template<typename T>
    void addComponentRequirementToSystem(const std::string &name, ComponentID componentID);
    //--------------------------------------------------------------
    //------------------------- Components --------------------------
    /**
     * @brief Adds a component to the entity signature
     * @param entity
     * @param component
     */
    void addComponentToEntitySignature(EntityID entity, ComponentID component);
    
    /**
     * @brief Registers the T component into the array of components
     * @details This is used to register the component into the array of components
     * Can only be called once per component type
     * @tparam T The type of the component
     */
    template<typename T>
    void registerComponent();
    
    /**
     * @brief get the component ID of type T
     * @details This is used to get the ID of the component type T
     * @tparam T The type of the component
     * @return The ID of the component
     */
    template<typename T>
    ComponentID getComponentID();
    
    /**
     * @brief Adds a component of type T to the entity
     * @details This will insert the component into the array of components of type T
     * @tparam T The type of the component
     * @param entity The entity to add the component to
     * @param component The component to add
     */
    template<typename T>
    void addComponent(EntityID entity, T &component);
    
    /**
     * @brief Get all the components of a type.
     *
     * @tparam T the type of the component
     * @return All the components existing with the type T
     */
    template<typename T>
    std::shared_ptr<ComponentArray<T>> getComponentArray();
    
    /**
     * @brief Checks if the component is registered
     * @param typeName The name of the component
     * @return True if the component is registered, false otherwise
     */
    bool componentIsRegistered(const char *typeName);
    
    /**
     * @brief Get the component of type T for the entity
     * @tparam T The type of the component
     * @param entity The entity to get the component from
     * @return The component of type T for the entity
     */
    template<typename T>
    T &getComponent(EntityID entity);
    
    /**
     * @brief Registers the component if it is not registered already
     * @tparam T The type of the component
     */
    template<typename T>
    void registerComponentIfNotRegistered();
    // --------------------------------------------------------------
    // ------------------------- Entities ----------------------------
    /**
     * @brief Destroys the entity from all the systems and components
     * @details This will remove the entity from all the arrays that contain it,
     * and sets it as available to be created again
     * @param entity The entity to destroy
     */
    void destroyEntity(EntityID entity);
    
    /**
     * @brief Create an entity
     * @details This will create and set the entity as alive, therefore it will be available to be used
     * @return
     */
    [[nodiscard]] EntityID getNextEntity();
    
    /**
     * @brief Checks if the entity can be created
     * @details This will check if there are available entities to be created and
     * if the living entities are less than the maximum allowed
     * @return True if the entity can be created, false otherwise
     */
    [[nodiscard]] inline bool canEntityBeCreated() const;
    
    /**
     * @brief Checks if the entity is alive
     * @details This will check if the entity is alive by checking if there is a component array for it
     * @param entity The entity to check
     * @return True if the entity is alive, false otherwise
     */
    [[nodiscard]] bool isEntityAlive(EntityID entity) const;
    
    /**
     * @brief Checks if the entity has the component
     * @details This will check if the entity has the component by checking if the component array exists
     * @param entity
     * @param component
     * @return True if the entity has the component, false otherwise
     */
    [[nodiscard]] bool doesEntityHaveComponent(EntityID entity, ComponentID component) const;
    
    /**
     * @brief Gets the signature of the entity
     * @param entity
     * @return The signature of the entity as a bitset
     */
    [[nodiscard]] Signature getEntitySignature(EntityID entity) const;
    
    
    /**
     * @brief Updates the entity array for each system, removing or adding the entity if needed
     * @details This will remove the entity from the system array when the entity no longer has the required components.
     * It will also add the entity to the system array when the entity has the required components.
     */
    void entitySignatureChanged();

private:
    /**
     * @brief Constructor is private to prevent instantiation, must use singleton ECS::get()
     */
    ECSContainers();
    
    // --------------------------------------------------------------
    // ------------------------- System -----------------------------
    
    /**
     * @brief Map from system type string to system type (signature, set<entities>)
     */
    std::unordered_map<std::string, SystemData> systems{};
    
    
    //--------------------------------------------------------------
    //------------------------- Components --------------------------
    
    /**
     * @brief Asserts that the component inherits from Component
     * @tparam T The type of the component
     */
    template<typename T>
    void assertIsComponent();
    
    /**
     * @brief Asserts that the component is registered before use
     * @details This is used to make sure that the component is registered before it is used
     * Only used in debug mode
     * @tparam T The type of the component
     */
    template<class T>
    void assertComponentIsRegistered();
    
    /**
     * @brief Asserts that the component is not registered before use
     * @details This is used to make sure that the same component is not registered twice
     * Only used in debug mode
     * @tparam T The type of the component
     */
    template<class T>
    void assertComponentIsNotRegistered();
    
    
    /**
     * @brief Map which contains component arrays
     * @details This is used to store the component arrays for each component type
     * Key -> Name of the component i.e. "PhysicsComponent"
     * Value -> Pair <ComponentArray (containing all the components of the same type), ComponentID>
     */
    std::unordered_map<const char *, std::pair<std::shared_ptr<IComponentArray>, ComponentID>> componentArrays{};
    /**
     * @brief Stores the ID of the next component.
     * I.e. if there are 4 components existing, physics, transform, camera and render
     * and their IDs are 0, 1, 2 and 3 respectively, this will store the value 4.
     */
    ComponentID nextComponentID{};
    
    // --------------------------------------------------------------
    // ------------------------- Entity -----------------------------
    
    /**
     * @brief Queue of unused entity IDs
     * @details The queue is used to keep track of the unused entity IDs
     * Contains maxEntities amount of IDs
     */
    std::queue<EntityID> availableEntities;
    
    /**
     * @brief Array of signatures where the index corresponds to the entity ID
     * @details The array is used to keep track of the signatures of the entities
     * The signature of an entity is a bitset where each bit represents a component
     */
    std::array<Signature, maxEntities> signatures;
    
    
    /**
     * @brief Total living entities - used to keep limits on how many exist
     * @details The number of living entities is used to keep track of the number of entities that exist
     * The living entities are not available in the queue of available entities
     */
    EntityID livingEntityCount;
};

template<typename Component>
void ECSContainers::registerComponent() {
    assertIsComponent<Component>();
    assertComponentIsNotRegistered<Component>();
    
    const char *typeName = typeid(Component).name();
    std::pair registeredComponent = std::make_pair(std::make_shared<ComponentArray<Component >>(), nextComponentID);
    componentArrays.insert({typeName, registeredComponent});
    
    // Increase the value so that the next component registered will get a different ID
    ++nextComponentID;
}


template<typename T>
ComponentID ECSContainers::getComponentID() {
    const char *typeName = typeid(T).name();
    assertIsComponent<T>();
    assertComponentIsRegistered<T>();
    
    return componentArrays[typeName].second;
}


template<typename T>
void ECSContainers::addComponent(EntityID entity, T &component) {
    assertIsComponent<T>();
    assertComponentIsRegistered<T>();
    
    // Add a component to the array for an entity
    getComponentArray<T>()->insertData(entity, component);
}


template<typename T>
std::shared_ptr<ComponentArray<T>> ECSContainers::getComponentArray() {
    const char *typeName = typeid(T).name();
    assertIsComponent<T>();
    assertComponentIsRegistered<T>();
    return componentArrays[typeName].first;
}


template<typename T>
T &ECSContainers::getComponent(EntityID entity) {
    return getComponentArray<T>()->getData(entity);
}

template<class T>
void ECSContainers::addComponentRequirementToSystem(const std::string &name, ComponentID componentID) {
    Signature newSignature;
    newSignature.set(getComponentID<T>());
    systems[name].first |= newSignature;
}

template<typename T>
void ECSContainers::assertIsComponent() {
    static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");
}

template<class T>
void ECSContainers::assertComponentIsRegistered() {
    ASSERT(componentIsRegistered(typeid(T).name()), "Component not registered before use.");
}

template<class T>
void ECSContainers::assertComponentIsNotRegistered() {
    ASSERT(!componentIsRegistered(typeid(T).name()), "Component is already registered.");
}

template<class T>
void ECSContainers::registerComponentIfNotRegistered() {
    if (!componentIsRegistered(typeid(T).name())) {
        registerComponent<T>();
    }
}

/**
 * @brief Singleton class which contains all the ECS containers
 * @details This is used to access all the ECS containers from anywhere in the program
 */
class ECS {
public:
    static std::shared_ptr<ECSContainers> getECS() {
        static std::shared_ptr<ECSContainers> ecs = std::make_shared<ECSContainers>(ECSContainers());
        return ecs;
    }
};
