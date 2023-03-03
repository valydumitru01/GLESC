#pragma once

#include "core/Types.h"
#include "core/ECSContainer.h"
#include "core/components/ComponentArray.h"

#include <memory>
#include <cassert>
#include <queue>
#include <array>
#include <unordered_map>


class Entity {
public:
	Entity();
	
	
	~Entity();
	
	template<typename T>
	void addComponent(T&& component);
	
	template<typename T>
	void removeComponent();
	
	template<typename T>
	T &getComponent();

private:
	inline void entitySignatureChanged();

private:
	EntityID ID;
};

Entity::Entity() {
	assert(ECSContainer::getEntities()->livingEntityCount < Max_Entities &&
		   "Too many entities in existence.");
	
	// Take an ID from the front of the queue
	ID = {ECSContainer::getEntities()->availableEntities.front()};
	// Remove the used entity ID from available entities
	ECSContainer::getEntities()->availableEntities.pop();
	++ECSContainer::getEntities()->livingEntityCount;
}

template<typename T>
void Entity::addComponent(T&& component) {
	ECSContainer::getEntities()->signatures[ID] |= ECSContainer::getComponents()->getComponentID<T>();
	ECSContainer::getComponents()->getComponentArray<T>()->insertData(ID, component);
	entitySignatureChanged();
}

template<typename T>
void Entity::removeComponent() {
	ECSContainer::getComponents()->getComponentArray<T>()->removeData(ID);
	entitySignatureChanged();
}


Entity::~Entity() {
	for (auto const &pair: ECSContainer::getComponents()->componentArrays) {
		auto const &component = pair.second;
		component->entityDestroyed(ID);
	}
	// Erase a destroyed EntityID from all system lists
	// mEntities is a set so no check needed
	for (auto const &pair: ECSContainer::getSystems()->systems) {
		auto const &system = pair.second;
		
		system->entities.erase(ID);
	}
	// Invalidate the destroyed entity's signature
	ECSContainer::getEntities()->signatures[ID].reset();
	
	// Put the destroyed ID at the back of the queue
	ECSContainer::getEntities()->availableEntities.push(ID);
	--ECSContainer::getEntities()->livingEntityCount;
}

inline void Entity::entitySignatureChanged() {
	// Notify each system that an EntityID's signature changed
	for (auto const &pair: ECSContainer::getSystems()->systems) {
		auto const &type = pair.first;
		auto const &system = pair.second;
		auto const &systemSignature = ECSContainer::getSystems()->signatures[type];
		
		// EntityID signature matches system signature - insert into set
		if ((ECSContainer::getEntities()->signatures[ID] & systemSignature) ==
			systemSignature) {
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
	return ECSContainer::getComponents()->getComponentArray<T>()->getData(ID);
}


