
#include "engine/ecs/frontend/entity/Entity.h"
using namespace GLESC::ECS;

Entity::Entity(const EntityName& name, const EntityMetadata& metadata, ECSCoordinator& ecs)
    : ID(ecs.createEntity(name, metadata)), ecs(ecs) {
}

Entity::Entity(ECSCoordinator& ecs) : ID(ecs.createEntity()), ecs(ecs) {
}

Entity::Entity(EntityID id, ECSCoordinator& ecs) : ID(id), ecs(ecs) {
}

void Entity::destroy() {
    ecs.markForDestruction(ID);
}

EntityName Entity::getName() const {
    return ecs.getEntityName(ID);
}

bool Entity::isAlive() const {
    return ecs.isEntityAlive(ID);
}
