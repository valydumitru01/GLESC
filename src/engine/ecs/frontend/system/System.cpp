
#include "engine/ecs/frontend/system/System.h"

using namespace GLESC::ECS;

System::System(ECSCoordinator &ecs, const SystemName& name) : ecs(ecs), name(name) {
    ecs.registerSystem(name);
}

const std::set<EntityID>& System::getAssociatedEntities() const {
    return ecs.getAssociatedEntities(name);
}

 std::unordered_map<EntityName, EntityID> System::getAllEntities() const {
    return ecs.getAllEntities();
}

std::vector<IComponent*> System::getComponents(EntityID entityId) const {
    return ecs.getComponents(entityId);
}

const EntityName& System::getEntityName(EntityID entityId) const {
    return ecs.getEntityName(entityId);
}

EntityID System::getEntity(const EntityName& entityName) const {
    return ecs.getEntityID(entityName);
}

const EntityMetadata& System::getEntityMetadata(EntityID entityId) const {
    return ecs.getEntityMetadata(entityId);
}