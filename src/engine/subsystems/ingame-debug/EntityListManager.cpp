
#include "engine/subsystems/ingame-debug/EntityListManager.h"

using namespace GLESC;
std::set<EntityListItem> EntityListManager::entities;
std::string EntityListManager::selectedEntity;

void EntityListManager::addEntity(const std::string& entity, EntityType type) {
    entities.insert({&entity, type});
}

void EntityListManager::entityRemoved(const std::string& entity) {
    entities.erase({&entity, EntityType::Default});
    if(selectedEntity == entity) selectedEntity.clear();
}
