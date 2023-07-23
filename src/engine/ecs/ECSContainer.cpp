#include "engine/ecs/ECSContainer.h"

ECSContainers::ECSContainers() : livingEntityCount(EntityID()) {
    // Initialize the queue with all possible entity IDs
    for (EntityID entity = EntityID(); static_cast<unsigned int>(entity) < maxEntities; ++entity) {
        availableEntities.push(entity);
    }
    
}

// --------------------------------------------------------------
// ------------------------ Systems -----------------------------
[[nodiscard]] std::set <EntityID> ECSContainers::getAssociatedEntities(const std::string &name) const {
    auto it = systems.find(name);
    ASSERT(it != systems.end(), "System " + name + " not registered, cannot get associated entities.");
    return it->second.second;
}

void ECSContainers::registerSystem(const std::string &name) {
    systems.insert({name, {Signature{}, std::set <EntityID>{}}});
}

[[nodiscard]] bool ECSContainers::systemIsRegistered(const std::string &name) const {
    return systems.find(name) != systems.end();
}

[[nodiscard]] Signature ECSContainers::getSignature(const std::string &name) const {
    auto it = systems.find(name);
    ASSERT(it != systems.end(), "System " + name + " not registered, cannot get signature.");
    return it->second.first;
}

void ECSContainers::entitySignatureChanged() {
#ifdef DEBUG
    Logger::get().importantInfoBlue("Entity signature changed. Updated systems: ");
    for (auto &pair: systems) {
        auto const &system = pair.first;
        auto const &signature = pair.second.first;
        auto &entities = pair.second.second;
        for (auto const &entity: entities) {
            if ((signatures[entity] & signature) == signature) {
                Logger::get().infoBlue("Entity" + std::to_string(entity) + " is added to " + system);
            } else {
                Logger::get().infoBlue("Entity" + std::to_string(entity) + " is removed from " + system);
            }
        }
    }
#endif
    for (auto &pair: systems) {
        auto const &signature = pair.second.first;
        auto &entities = pair.second.second;
        
        for (auto const &entity: entities) {
            if ((signatures[entity] & signature) == signature) {
                entities.insert(entity);
            } else {
                entities.erase(entity);
            }
        }
    }
}

// --------------------------------------------------------------
// ------------------------- Entities ----------------------------

void ECSContainers::destroyEntity(EntityID entity) {
    ASSERT(entity < maxEntities, "Entity out of range.");
    ASSERT(isEntityAlive(entity), "Entity is not alive.");
    // Put the destroyed ID at the back of the queue
    availableEntities.push(entity);
    
    // Invalidate the destroyed entity's signature
    signatures[entity].reset();
    
    // Decrease living entity count
    --livingEntityCount;
    
    // Iterate over all the component arrays and notify them that an entity has been destroyed
    for (auto const &pair: componentArrays) {
        auto const &componentArray = pair.second.first;
        if (componentArray->hasComponent(entity))
            componentArray->entityDestroyed(entity);
    }
    
    // Erase a destroyed entity from all system lists
    for (auto &pair: systems) {
        auto &entities = pair.second.second;
        entities.erase(entity);
    }
}

[[nodiscard]] EntityID ECSContainers::getNextEntity() {
    ASSERT(canEntityBeCreated(), "There are no available entities.");
    
    EntityID id = availableEntities.front();
    availableEntities.pop();
    ++livingEntityCount;
    return id;
}

[[nodiscard]] bool ECSContainers::canEntityBeCreated() const {
    return livingEntityCount < maxEntities && !availableEntities.empty();
}

[[nodiscard]] bool ECSContainers::isEntityAlive(EntityID entity) const {
    ASSERT(entity < maxEntities, "Entity is out of range.");
    return signatures[entity].any(); // If the entity has at least one component, it is alive
}

[[nodiscard]] bool ECSContainers::doesEntityHaveComponent(EntityID entity, ComponentID component) const {
    ASSERT(entity < maxEntities, "Entity out of range.");
    ASSERT(isEntityAlive(entity), "Entity is not alive.");
    return signatures[entity][component];
}

[[nodiscard]] Signature ECSContainers::getEntitySignature(EntityID entity) const {
    ASSERT(entity < maxEntities, "Entity out of range.");
    ASSERT(isEntityAlive(entity), "Entity is not alive.");
    return signatures[entity];
}

void ECSContainers::addComponentToEntitySignature(EntityID entity, ComponentID component) {
    // Set the bit that represents the component to 1
    signatures[entity].set(component);
}