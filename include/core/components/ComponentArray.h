#pragma once

#include <assert.h>>
#include <unordered_map>

class IComponentArray {
public:
    virtual ~IComponentArray() = default;

    virtual void entityDestroyed(EntityID entity) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray {
public:
    void InsertData(EntityID entity, T component) {
        assert(
                indexToEntityMap.find(entity) == indexToEntityMap.end()
                && "Component added to same entity more than once.");

        // Put new entry at end and update the maps
        size_t newIndex = size;
        indexToEntityMap[entity] = newIndex;
        indexToEntityMap[newIndex] = entity;
        componentArray[newIndex] = component;
        ++size;
    }

    void RemoveData(EntityID entity) {
        assert(
                indexToEntityMap.find(entity) != indexToEntityMap.end()
                && "Removing non-existent component.");

        // Copy element at end into deleted element's place to maintain density
        size_t indexOfRemovedEntity = indexToEntityMap[entity];
        size_t indexOfLastElement = size - 1;
        componentArray[indexOfRemovedEntity] =
                componentArray[indexOfLastElement];

        // Update map to point to moved spot
        EntityID entityOfLastElement = indexToEntityMap[indexOfLastElement];
        indexToEntityMap[entityOfLastElement] = indexOfRemovedEntity;
        indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

        indexToEntityMap.erase(entity);
        indexToEntityMap.erase(indexOfLastElement);

        --size;
    }

    T &GetData(EntityID entity) {
        assert(
                indexToEntityMap.find(entity) != indexToEntityMap.end()
                && "Retrieving non-existent component.");

        // Return a reference to the entity's component
        return componentArray[indexToEntityMap[entity]];
    }
    void entityDestroyed(EntityID entity) override {
        if (indexToEntityMap.find(entity) != indexToEntityMap.end()) {
            // Remove the entity's component if it existed
            RemoveData(entity);
        }
    }

private:
    /**
     * @brief The packed array of components (of generic type T),
     * set to a specified maximum amount, matching the maximum number
     * of entities allowed to exist simultaneously, so that each entity
     * has a unique spot.
     */
    std::array<T, max_entities> componentArray;

    /**
     * @brief Map from an entity ID to an array index.
     *
     */
    std::unordered_map<EntityID, size_t> entityToIndexMap;

    /**
     * @brief Map from an array index to an entity ID.
     *
     */
    std::unordered_map<size_t, EntityID> indexToEntityMap;

    /**
     * @brief Total size of valid entries in the array.
     *
     */
    size_t size;
};
