#include "core/components/Component.h"
#include "core/components/TransformComponent.h"
#include "core/components/RenderComponent.h"
#include "core/components/InputComponent.h"
#include "core/components/PhysicsComponent.h"

#include "core/systems/input/InputSystem.h"
#include "core/systems/render/RenderSystem.h"
#include "core/systems/physics/PhysicsSystem.h"
#include "core/systems/transform/TransformSystem.h"

#include <vector>
#include <memory>
#include <bitset>
#include <queue>
#include <assert.h>


class EntityCoordinator
{
private:
    /**
     * @brief Type of each ID of each entity
     * 
     */
    using EntityID = std::uint16_t;
    /**
     * @brief Type of the ID of each component
     * 
     */
    using ComponentID = std::uint8_t;
    /**
     * @brief Maximum amount of components each entity can have
     * 
     */
    const static ComponentID max_components = 16;
    /**
     * @brief type of the signature of each entity.
     * I.e. if Transform has type 0, RigidBody has type 1, Gravity has type 2 and
     * an entity that “has” those three components would have a signature of 0b111 
     * (bits 0, 1, and 2 are set).
     * 
     */
    using EntitySignature = std::bitset<max_components>;

    /**
     * @brief Maximum amount of entities can there be at once
     * 
     */
    const static EntityID max_entities = 5000;
    
    std::unique_ptr<std::vector<TransformComponent>> transforms;
    std::unique_ptr<std::vector<RenderComponent>> renders;
    std::unique_ptr<std::vector<InputComponent>> inputs;
    std::unique_ptr<std::vector<PhysicsComponent>> physics;

    std::unique_ptr<TransformSystem> transformSystem;
    std::unique_ptr<RenderSystem> renderSystem;
    std::unique_ptr<InputSystem> inputSystem;
    std::unique_ptr<PhysicsSystem> physicsSystem;


    EntityID numTransformComponents;
    EntityID numRenderComponents;
    EntityID numInputComponents;
    EntityID numPhysicsComponents;

    // Queue of unused entity IDs
	std::queue<EntityID> availableEntities;

	// Array of signatures where the index corresponds to the entity ID
	std::array<EntitySignature, max_entities> signatures;

	// Total living entities - used to keep limits on how many exist
	uint32_t livingEntityCount;

public:


    EntityCoordinator(/* args */);
    ~EntityCoordinator();
    
    EntityID& createEntity() const;
    std::unique_ptr<std::vector<Component>> getEntityComponents(EntityID& entityID) const;
    void setComponentToEntity(Component& component, EntityID& entityID);
};

EntityCoordinator::EntityCoordinator()
{
    // Initialize the queue with all possible entity IDs
    for (EntityID entity = 0; entity < max_entities; ++entity)
    {
        availableEntities.push(entity);
    }
}

EntityCoordinator::~EntityCoordinator()
{
}