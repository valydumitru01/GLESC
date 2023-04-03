#pragma once

#include "core/Types.h"
#include "ecs/components/ComponentArray.h"

#include <memory>
#include <cassert>
#include <unordered_map>
#include <array>
#include <vector>
#include <bitset>
#include <queue>
#include <set>

class Component;

class EntityContainer {
    friend class System;

    friend class Entity;


private:
    // Queue of unused entity IDs
    std::queue<EntityID> availableEntities;

    // Array of signatures where the index corresponds to the entity ID
    std::array<Signature, maxEntities> signatures;

    // Total living entities - used to keep limits on how many exist
    EntityID livingEntityCount;

public:
    EntityContainer() : livingEntityCount(EntityID()) {

        // Initialize the queue with all possible entity IDs
        for (EntityID entity = EntityID(); static_cast<unsigned int>(entity) < maxEntities; ++entity) {
            availableEntities.push(entity);
        }
    }
};


class ComponentContainer {
    friend class System;

    friend class Entity;

public:
    /**
     * @brief Registers the T component into the array of components
     * Creates an ID for the new component.
     */
    template<typename T>
    void registerComponent() {
        assertIsComponent<T>();
        assertComponentIsRegistered<T>();

        const char *typeName = typeid(T).name();
        componentIDs.insert({typeName, nextComponentID});
        componentArrays.insert({typeName, std::make_shared<ComponentArray<T >>()});


        // Increase the value so that the next component registered will get a different ID
        ++nextComponentID;
    }


    template<typename T>
    ComponentID getComponentID() {
        const char *typeName = typeid(T).name();
        assertIsComponent<T>();
        assertComponentIsRegistered<T>();

        return componentIDs[typeName];
    }
    /**
     * @brief Asserts that the component inherits from Component
     * @tparam T
     */
    template<typename T>
    void assertIsComponent() {
        static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");
    }

    /**
     * @brief Asserts that the component is registered before use
     * @tparam T
     */
    template<class T>
    void assertComponentIsRegistered() {
        const char *typeName = typeid(T).name();
        assert(componentIDs.find(typeName) != componentIDs.end() && "Component not registered before use.");
    }
private:
    /**
     * @brief Map which contains component IDs (each component has an unique ID)
     * Key -> name of the component i.e. "PhysicsComponent"
     * Value -> The ID of the component
     */
    std::unordered_map<const char *, ComponentID> componentIDs{};
    /**
     * @brief Map which contains component arrays
     * Key -> Name of the component i.e. "PhysicsComponent"
     * Value -> Array of all the components of that type
     */
    std::unordered_map<const char *, std::shared_ptr<IComponentArray>> componentArrays{};
    /**
     * @brief Stores the ID of the next component.
     * I.e. if there are 4 components existing, physics, transform, camera and render
     * and their IDs are 0, 1, 2 and 3 respectively, this will store the value 4.
     */
    ComponentID nextComponentID{};

    /**
     * @brief Get all the components of a type.
     *
     * @tparam T the type of the component
     * @return All the components existing with the type T
     */
    template<typename T>
    std::shared_ptr<ComponentArray<T>> getComponentArray() {
        const char *typeName = typeid(T).name();
        assertIsComponent<T>();
        assert(componentIDs.find(typeName) != componentIDs.end() && "Component not registered before use.");

        return std::static_pointer_cast<ComponentArray<T >>(componentArrays[typeName]);
    }


    template<typename T>
    T &getComponent(EntityID entity) {
        return getComponentArray<T>()->getData(entity);
    }
};

class ECSComponentContainer {
    friend class System;

    friend class Entity;

    static std::shared_ptr<ComponentContainer> getComponents() {
        if (componentContainer == nullptr) {
            componentContainer = std::make_shared<ComponentContainer>();
        }
        return componentContainer;
    }

    static std::shared_ptr<ComponentContainer> componentContainer;
};


class SystemContainer {

    friend class System;

    friend class Entity;

private:

    // Map from system type string pointer to a signature
    std::unordered_map<SystemID, std::pair<Signature, std::set<EntityID>>> systems{};


};

class ECSSystemContainer {
    friend class System;

    friend class Entity;

    static std::shared_ptr<SystemContainer> getSystems() {
        if (systemContainer == nullptr) {
            systemContainer = std::make_shared<SystemContainer>();
        }
        return systemContainer;
    }

    static std::shared_ptr<SystemContainer> systemContainer;
};

class ECSEntityContainer {
    friend class System;

    friend class Entity;

    static std::shared_ptr<EntityContainer> getEntities() {
        if (entityContainer == nullptr) {
            entityContainer = std::make_shared<EntityContainer>();
        }
        return entityContainer;
    }


    static std::shared_ptr<EntityContainer> entityContainer;


};