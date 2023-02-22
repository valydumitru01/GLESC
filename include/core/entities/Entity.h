#pragma once
#include "core/Types.h"
#include "core/components/Component.h"
#include "core/ComponentManager.h"
#include "core/EntityManager.h"
#include "core/components/ComponentArray.h"
#include "SystemManager.h"
#include <memory>
#include <cassert>
#include <queue>
#include <array>
#include <unordered_map>


class Entity {
public:
	Entity(const std::shared_ptr<EntityManager>& entityManager,
			const std::shared_ptr<ComponentManager>& componentManager);
    ~Entity();
	template<typename T>
	void addComponent(T component);
	template<typename T>
	void removeComponent(T component);
	template<typename T>
	T& getComponent();

private:
	EntityID ID;
	std::shared_ptr<EntityManager> entityManager;
	std::shared_ptr<ComponentManager> componentManager;
    std::shared_ptr<SystemManager> systemManager;
};

Entity::Entity(std::shared_ptr<EntityManager> const& entityManager,
		std::shared_ptr<ComponentManager> const& componentManager) :
		entityManager(entityManager), componentManager(componentManager), ID(
				entityManager->CreateEntity()) {

    assert(
            entityManager->livingEntityCount < max_entities
            && "Too many entities in existence.");

    // Take an ID from the front of the queue
    EntityID id = entityManager->availableEntities.front();
    entityManager->availableEntities.pop();
    ++entityManager->livingEntityCount;
}

template<typename T>
void Entity::addComponent(T component) {
	componentManager->getComponentArray<T>()->InsertData(ID, component);
}

template<typename T>
void Entity::removeComponent(T component) {
	componentManager->getComponentArray<T>()->RemoveData(ID);
}



Entity::~Entity() {
    for (auto const &pair: componentManager->componentArrays) {
        auto const &component = pair.second;
        component->entityDestroyed(ID);
    }

    // Erase a destroyed EntityID from all system lists
    // mEntities is a set so no check needed
    for (auto const& pair : systemManager->systems)
    {
        auto const& system = pair.second;

        system->entities.erase(ID);
    }


    // Invalidate the destroyed entity's signature
    entityManager->signatures[ID].reset();

    // Put the destroyed ID at the back of the queue
    entityManager->availableEntities.push(ID);
    --entityManager->livingEntityCount;

}


template<typename T>
inline T& Entity::getComponent() {
	return componentManager->getComponentArray<T>()->GetData(ID);
}


void SetSignature(EntityID entityID, Signature &signatureBits) {
    assert(entityID < max_entities && "Entity out of range.");

    // Put this entity's signature into the array
    signatures[entityID] = signatureBits;
}
Signature GetSignature(EntityID entityID) {
    assert(entityID < max_entities && "Entity out of range.");

    // Get this entity's signature from the array
    return signatures[entityID];
}