#pragma once

#include "core/Types.h"
#include "core/entities/Entity.h"
#include "core/ECSContainer.h"


#include <vector>
#include <memory>
#include <bitset>
#include <queue>
#include <cassert>

class EntityContainer {
    friend class Entity;
	

private:
    // Queue of unused entity IDs
    std::queue<EntityID> availableEntities;
	
    // Array of signatures where the index corresponds to the entity ID
    std::array<Signature, Max_Entities> signatures;

    // Total living entities - used to keep limits on how many exist
	EntityID livingEntityCount;
	
public:
    EntityContainer() : livingEntityCount(EntityID()) {
		
		// Initialize the queue with all possible entity IDs
        for (EntityID entity = EntityID(); static_cast<unsigned int>(entity) < Max_Entities; ++entity) {
            availableEntities.push(entity);
        }
    }
};










