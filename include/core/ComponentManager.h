#pragma once

#include "Types.h"
#include "core/components/ComponentArray.h"

#include <any>
#include <memory>
#include <unordered_map>
#include <cassert>
#include <array>
#include <unordered_map>

class ComponentManager {
    friend class Entity;

public:
    /**
     * @brief Registers the T component into the array of components
     * Creates an ID for the new component.
     */
    template<typename T>
    void registerComponent() {
        // Get the name of the type through reflection
        const char *typeName = typeid(T).name();

        assert(componentIDs.find(typeName) == componentIDs.end() && "Registering component type more than once.");

        componentIDs.insert({typeName, nextComponentID});
        componentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});
        // Increase the
        ++nextComponentID;
    }

    template<typename T>
    ComponentID getComponentID() {
        const char *typeName = typeid(T).name();

        assert(componentIDs.find(typeName) != componentIDs.end() && "Component not registered before use.");

        return componentIDs[typeName];
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

        assert(componentIDs.find(typeName) != componentIDs.end() && "Component not registered before use.");

        return std::static_pointer_cast<ComponentArray<T>>(componentArrays[typeName]);
    }
};

