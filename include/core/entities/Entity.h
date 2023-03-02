#pragma once

#include "core/Types.h"

#include "core/ECSFactory.h"

#include "core/components/ComponentArray.h"

#include <memory>
#include <cassert>
#include <queue>
#include <array>
#include <unordered_map>

class EntityContainer;

class ComponentContainer;

class SystemContainer;

class Entity {
public:
    Entity();


    ~Entity();

    template<typename T>
    void addComponent(T component);

    template<typename T>
    void removeComponent();

    template<typename T>
    T &getComponent();

private:
    inline void entitySignatureChanged();

private:
    EntityID ID;
};

Entity::Entity() : {
    assert(ECSFactory::getEntityContainer()->livingEntityCount < max_entities && "Too many entities in existence.");

    // Take an ID from the front of the queue
    ID = {ECSFactory::getEntityContainer()->availableEntities.front()};
    // Remove the used entity ID from available entities
    ECSFactory::getEntityContainer()->availableEntities.pop();
    ++ECSFactory::getEntityContainer()->livingEntityCount;
}

template<typename T>
void Entity::addComponent(T component) {
    ECSFactory::getEntityContainer()->signatures[ID] |= ECSFactory::getComponentContainer()->getComponentID<T>();
    ECSFactory::getComponentContainer()->getComponentArray<T>()->InsertData(ID, component);
    entitySignatureChanged();
}

template<typename T>
void Entity::removeComponent() {
    ECSFactory::getComponentContainer()->getComponentArray<T>()->RemoveData(ID);
    entitySignatureChanged();
}


Entity::~Entity() {
    for (auto const &pair: ECSFactory::getComponentContainer()->componentArrays) {
        auto const &component = pair.second;
        component->entityDestroyed(ID);
    }
    // Erase a destroyed EntityID from all system lists
    // mEntities is a set so no check needed
    for (auto const &pair: ECSFactory::getSystemContainer()->systems) {
        auto const &system = pair.second;

        system->entities.erase(ID);
    }
    // Invalidate the destroyed entity's signature
    ECSFactory::getEntityContainer()->signatures[ID].reset();

    // Put the destroyed ID at the back of the queue
    ECSFactory::getEntityContainer()->availableEntities.push(ID);
    --ECSFactory::getEntityContainer()->livingEntityCount;
}

inline void Entity::entitySignatureChanged() {
    // Notify each system that an EntityID's signature changed
    for (auto const &pair: ECSFactory::getSystemContainer()->systems) {
        auto const &type = pair.first;
        auto const &system = pair.second;
        auto const &systemSignature = ECSFactory::getSystemContainer()->signatures[type];

        // EntityID signature matches system signature - insert into set
        if ((ECSFactory::getEntityContainer()->signatures[ID] & systemSignature) == systemSignature) {
            system->entities.insert(ID);
        }
            // EntityID signature does not match system signature - erase from set
        else {
            system->entities.erase(ID);
        }
    }
}

template<typename T>
inline T &Entity::getComponent() {
    return ECSFactory::getComponentContainer()->getComponentArray<T>()->GetData(ID);
}


