#pragma once

#include "core/Types.h"
#include "core/ECSContainer.h"
#include "core/components/ComponentArray.h"
#include "core/components/Component.h"

#include <memory>
#include <cassert>
#include <queue>
#include <array>
#include <unordered_map>


class Entity {
private:
	inline void entitySignatureChanged() const;
public:
	Entity();
	~Entity();
	
	template<typename T>
	void addComponent();
	
	template<typename T>
	void removeComponent();
	
	template<typename T>
	T &getComponent() const;


private:
	EntityID ID;
};

Entity::Entity() {
	assert(ECSEntityContainer::getEntities()->livingEntityCount < Max_Entities &&
		   "Too many entities in existence.");
	
	// Take an ID from the front of the queue
	ID = {ECSEntityContainer::getEntities()->availableEntities.front()};
	// Remove the used entity ID from available entities
	ECSEntityContainer::getEntities()->availableEntities.pop();
	++ECSEntityContainer::getEntities()->livingEntityCount;
}

template<typename T>
void Entity::addComponent() {
	static_assert(std::is_base_of<Component, T>::value, "T must be Component");
	if (!ECSComponentContainer::getComponents()->isComponentRegistered<T>())
		ECSComponentContainer::getComponents()->registerComponent<T>();
	T newComponent = *new T();
	ECSEntityContainer::getEntities()->signatures[ID] |= ECSComponentContainer::getComponents()->getComponentID<T>();
	ECSComponentContainer::getComponents()->getComponentArray<T>()->insertData(ID, newComponent);
	entitySignatureChanged();
}

template<typename T>
void Entity::removeComponent() {
	static_assert(std::is_base_of<Component, T>::value, "T must be Component");
	ECSComponentContainer::getComponents()->getComponentArray<T>()->removeData(ID);
	entitySignatureChanged();
}


Entity::~Entity() {
	
	for (auto const &pair: ECSComponentContainer::getComponents()->componentArrays) {
		auto const &component = pair.second;
		component->entityDestroyed(ID);
	}
	// Erase a destroyed EntityID from all system lists
	// mEntities is a set so no check needed
	for (auto &pair: ECSSystemContainer::getSystems()->systems) {
		std::set<EntityID> &entities=pair.second.second;
		entities.erase(ID);
	}
	// Invalidate the destroyed entity's signature
	ECSEntityContainer::getEntities()->signatures[ID].reset();
	
	// Put the destroyed ID at the back of the queue
	ECSEntityContainer::getEntities()->availableEntities.push(ID);
	--ECSEntityContainer::getEntities()->livingEntityCount;
}

inline void Entity::entitySignatureChanged() const {
	// Notify each system that an EntityID's signature changed
	for (auto &pair: ECSSystemContainer::getSystems()->systems) {
		Signature const &signature = pair.second.first;
		std::set<EntityID> &entities=pair.second.second;
		
		// EntityID signature matches system signature - insert into set
		if ((ECSEntityContainer::getEntities()->signatures[ID] & signature) ==
				signature) {
			entities.insert(ID);
		}
			// EntityID signature does not match system signature - erase from set
		else {
			entities.erase(ID);
		}
	}
}


template<typename T>
inline T &Entity::getComponent() const{
	return ECSComponentContainer::getComponents()->getComponentArray<T>()->getData(ID);
}


