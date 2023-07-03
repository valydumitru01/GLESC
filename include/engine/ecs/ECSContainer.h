#pragma once

#include "ECSTypes.h"
#include "engine/ecs/components/ComponentArray.h"

#include <memory>
#include <cassert>
#include <unordered_map>
#include <array>
#include <vector>
#include <bitset>
#include <queue>
#include <set>

class Component;
class ECSContainers {
    friend class ECS;
    friend class Entity;
    friend class System;
private:
    ECSContainers() : livingEntityCount(EntityID()) {
        // Initialize the queue with all possible entity IDs
        for (EntityID entity = EntityID(); static_cast<unsigned int>(entity) < maxEntities; ++entity) {
            availableEntities.push(entity);
        }
        
    }
    
    // --------------------------------------------------------------
    // ------------------------- System -----------------------------
    
    void registerSystem(const std::string &name) {
        systems.insert({name, {Signature{}, std::set <EntityID>{}}});
    }
    
    [[nodiscard]] std::set <EntityID> &getAssociatedEntities(const std::string &name) {
        return systems[name].second;
    }
    
    
    bool systemIsRegistered(const std::string &name) {
        return systems.find(name) != systems.end();
    }
    
    
    [[nodiscard]] Signature &getSignature(const std::string &name) {
        return systems[name].first;
    }
    
    
    template <class T>
    void addComponentRequirementToSystem(const std::string &name, ComponentID componentID) {
        Signature newSignature;
        newSignature.set(getComponentID <T>());
        systems[name].first |= newSignature;
    }
    
    void entitySignatureChanged() {
#ifdef DEBUG
        Logger::get().importantInfoBlue("Entity signature changed. Updated systems: ");
        for (auto &pair: systems) {
            auto const &system = pair.first;
            auto const &signature = pair.second.first;
            auto &entities = pair.second.second;
            for (auto const &entity: entities) {
                if ((signatures[entity] & signature) == signature) {
                    Logger::get().infoBlue("Entity" + std::to_string(entity) + " is added to " + system);
                } else {
                    Logger::get().infoBlue("Entity" + std::to_string(entity) + " is removed from " + system);
                }
            }
        }
#endif
        for (auto &pair: systems) {
            auto const &signature = pair.second.first;
            auto &entities = pair.second.second;
            
            for (auto const &entity: entities) {
                if ((signatures[entity] & signature) == signature) {
                    entities.insert(entity);
                } else {
                    entities.erase(entity);
                }
            }
        }
    }
    // Map from system type string pointer to a signature
    std::unordered_map <std::string, std::pair <Signature, std::set <EntityID>>> systems{};
    
    
    //--------------------------------------------------------------
    //------------------------- Components --------------------------
    
    /**
     * @brief Registers the T component into the array of components
     * @details This is used to register the component into the array of components
     * Can only be called once per component type
     * @tparam T The type of the component
     */
    template <typename T>
    void registerComponent() {
        assertIsComponent <T>();
        assertComponentIsNotRegistered <T>();
        
        const char *typeName = typeid(T).name();
        std::pair registeredComponent = std::make_pair(std::make_shared <ComponentArray <T >>(), nextComponentID);
        componentArrays.insert({typeName, registeredComponent});
        
        // Increase the value so that the next component registered will get a different ID
        ++nextComponentID;
    }
    
    
    
    /**
     * @brief get the component ID of type T
     * @details This is used to get the ID of the component type T
     * @tparam T The type of the component
     * @return The ID of the component
     */
    template <typename T>
    ComponentID getComponentID() {
        const char *typeName = typeid(T).name();
        assertIsComponent <T>();
        assertComponentIsRegistered <T>();
        
        return componentArrays[typeName].second;
    }
    
    /**
     * @brief Adds a component of type T to the entity
     * @details This will insert the component into the array of components of type T
     * @tparam T The type of the component
     * @param entity The entity to add the component to
     * @param component The component to add
     */
    template <typename T>
    void addComponent(EntityID entity, T& component) {
        assertIsComponent <T>();
        assertComponentIsRegistered <T>();
        
        // Add a component to the array for an entity
        getComponentArray <T>()->insertData(entity, component);
    }
    
    /**
     * @brief Asserts that the component inherits from Component
     * @tparam T
     */
    template <typename T>
    void assertIsComponent() {
#ifdef DEBUG
        static_assert(std::is_base_of <Component, T>::value, "T must inherit from Component");
#endif
    }
    
    /**
     * @brief Asserts that the component is registered before use
     * @details This is used to make sure that the component is registered before it is used
     * Only used in debug mode
     * @tparam T
     */
    template <class T>
    void assertComponentIsRegistered() {
#ifdef DEBUG
        const char *typeName = typeid(T).name();
        assert(componentIsRegistered(typeName) && "Component not registered before use.");
#endif
    }
    
    /**
     * @brief Asserts that the component is not registered before use
     * @details This is used to make sure that the same component is not registered twice
     * Only used in debug mode
     * @tparam T
     */
    template <class T>
    void assertComponentIsNotRegistered() {
#ifdef DEBUG
        assert(!componentIsRegistered(typeid(T).name()) && "Component is already registered.");
#endif
    }
    bool componentIsRegistered(const char *typeName) {
        return componentArrays.find(typeName) != componentArrays.end();
    }
    
    template <class T>
    void registerComponentIfNotRegistered() {
        if (!componentIsRegistered(typeid(T).name())) {
            registerComponent <T>();
        }
    }
    
    /**
     * @brief Get all the components of a type.
     *
     * @tparam T the type of the component
     * @return All the components existing with the type T
     */
    template <typename T>
    std::shared_ptr <ComponentArray <T>> getComponentArray() {
        const char *typeName = typeid(T).name();
        assertIsComponent <T>();
        assertComponentIsRegistered<T>();
        return std::static_pointer_cast <ComponentArray <T >>(componentArrays[typeName].first);
    }
    

    /**
     * @brief Get the component of type T for the entity
     * @tparam T The type of the component
     * @param entity The entity to get the component from
     * @return The component of type T for the entity
     */
    template <typename T>
    T &getComponent(EntityID entity) {
        return getComponentArray <T>()->getData(entity);
    }
    /**
     * @brief Map which contains component arrays
     * @details This is used to store the component arrays for each component type
     * Key -> Name of the component i.e. "PhysicsComponent"
     * Value -> Pair <ComponentArray, ComponentID>
     */
    std::unordered_map <const char *, std::pair<std::shared_ptr<IComponentArray>, ComponentID>> componentArrays{};
    /**
     * @brief Stores the ID of the next component.
     * I.e. if there are 4 components existing, physics, transform, camera and render
     * and their IDs are 0, 1, 2 and 3 respectively, this will store the value 4.
     */
    ComponentID nextComponentID{};
    
    // --------------------------------------------------------------
    // ------------------------- Entity -----------------------------
    
    
    [[nodiscard]] EntityID getNextEntityID() {
        EntityID id = availableEntities.front();
        availableEntities.pop();
        ++livingEntityCount;
        return id;
    }
    
    [[nodiscard]] bool areThereAvailableEntities() const {
        return !availableEntities.empty();
    }
    
    [[nodiscard]] bool canEntityBeCreated() const {
        return livingEntityCount < maxEntities;
    }
    
    [[nodiscard]] bool isEntityAlive(EntityID entity) const {
        return signatures[entity].any();
    }
    
    [[nodiscard]] bool doesEntityHaveComponent(EntityID entity, ComponentID component) const {
        return signatures[entity][component];
    }
    
    [[nodiscard]] Signature getEntitySignature(EntityID entity) const {
        return signatures[entity];
    }
    
    void entityDestroyed(EntityID entity) {
        // Put the destroyed ID at the back of the queue
        availableEntities.push(entity);
        
        // Invalidate the destroyed entity's signature
        signatures[entity].reset();
        
        // Decrease living entity count
        --livingEntityCount;
    
        // Iterate over all the component arrays and notify them that an entity has been destroyed
        for (auto const &pair: componentArrays) {
            auto const &componentArray = pair.second.first;
            if(componentArray->hasComponent(entity))
                componentArray->entityDestroyed(entity);
        }
    
        // Erase a destroyed entity from all system lists
        for (auto &pair: systems) {
            auto &entities = pair.second.second;
            entities.erase(entity);
        }
    }
    
    void changeEntitySignature(EntityID entity, ComponentID component) {
        // Set the bit that represents the component to 1
        signatures[entity].set(component);
    }
    
    /**
     * @brief Queue of unused entity IDs
     * @details The queue is used to keep track of the unused entity IDs
     * Contains maxEntities amount of IDs
     */
    std::queue <EntityID> availableEntities;
    
    /**
     * @brief Array of signatures where the index corresponds to the entity ID
     * @details The array is used to keep track of the signatures of the entities
     * The signature of an entity is a bitset where each bit represents a component
     */
    std::array <Signature, maxEntities> signatures;
    
    
    /**
     * @brief Total living entities - used to keep limits on how many exist
     * @details The number of living entities is used to keep track of the number of entities that exist
     * The living entities are not available in the queue of available entities
     */
    EntityID livingEntityCount;
};




/**
 * @brief Singleton class which contains all the ECS containers
 * @details This is used to access all the ECS containers from anywhere in the program
 */
class ECS{
public:
    static std::shared_ptr<ECSContainers> getECS() {
        static std::shared_ptr<ECSContainers> ecs = std::make_shared<ECSContainers>(ECSContainers());
        return ecs;
    }
private:
    static std::shared_ptr<ECSContainers> ecs;
};
