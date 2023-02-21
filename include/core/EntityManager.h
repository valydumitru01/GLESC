#pragma once
#include "core/components/Component.h"
#include "core/components/TransformComponent.h"
#include "core/components/RenderComponent.h"
#include "core/components/InputComponent.h"
#include "core/components/PhysicsComponent.h"

#include "core/systems/input/InputSystem.h"
#include "core/systems/render/RenderSystem.h"
#include "core/systems/physics/PhysicsSystem.h"
#include "core/systems/transform/TransformSystem.h"
#include "core/types.h"
#include "core/entities/entity.h"

#include <vector>
#include <memory>
#include <bitset>
#include <queue>
#include <assert.h>

class EntityManager {
	friend class Entity;
private:


	// Queue of unused entity IDs
	std::queue<EntityID> availableEntities;

	// Array of signatures where the index corresponds to the entity ID
	std::array<Signature, max_entities> signatures;

	// Total living entities - used to keep limits on how many exist
	uint32_t livingEntityCount;

public:
	EntityManager():
		livingEntityCount(0){
		// Initialize the queue with all possible entity IDs
		for (EntityID entity = 0; entity < max_entities; ++entity) {
			availableEntities.push(entity);
		}
	}

	EntityID CreateEntity() {
		assert(
				livingEntityCount < max_entities
						&& "Too many entities in existence.");

		// Take an ID from the front of the queue
		EntityID id = availableEntities.front();
		availableEntities.pop();
		++livingEntityCount;

		return id;
	}
	std::unique_ptr<std::vector<Component>> getEntityComponents(
			EntityID &entityID) const;

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

	void destroyEntity(EntityID entityID) {
		assert(entityID < max_entities && "Entity out of range.");

		// Invalidate the destroyed entity's signature
		signatures[entityID].reset();

		// Put the destroyed ID at the back of the queue
		availableEntities.push(entityID);
		--livingEntityCount;
	}
};










