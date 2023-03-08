#pragma once

#include "core/entities/Entity.h"
#include "core/ECSContainer.h"
#include <set>
#include <memory>

class System : public std::enable_shared_from_this<System> {
	friend class Entity;

public:
	
	System() {
		
		assert(ECSSystemContainer::getSystems()->systems.find(id) ==
			   ECSSystemContainer::getSystems()->systems.end() &&
			   "Registering system more than once.");
		ECSSystemContainer::getSystems()->systems.insert({id, make_pair(Signature{},std::set<EntityID>{})});
	}
	
	template<class T>
	void addComponentRequirement() {
		
		Signature newSignature;
		newSignature.set(ECSComponentContainer::getComponents()->getComponentID<T>());
		assert(ECSSystemContainer::getSystems()->systems.find(id) ==
			   ECSSystemContainer::getSystems()->systems.end() &&
			   "Registering system more than once.");
		
		// Modify the old signature
		getSignature() |= newSignature;
	}

	inline std::set<EntityID> &getAssociatedEntities(){
		return ECSSystemContainer::getSystems()->systems[id].second;
	}
	
	
	inline Signature &getSignature(){
		return ECSSystemContainer::getSystems()->systems[id].first;
	}
protected:
	SystemID id{};
	
	template<class T>
	inline std::set<T> &getAssociatedComponents(){
		return ECSComponentContainer::getComponents()->getComponentArray<T>();
	}
};
