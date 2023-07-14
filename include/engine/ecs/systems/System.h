#pragma once

#include "engine/ecs/entities/Entity.h"
#include "engine/ecs/ECSContainer.h"
#include "engine/foundation/logger/Logger.h"
#include <set>
#include <memory>

class System {
    friend class Entity;

public:
    
    explicit System(const std::string &name) {
        Logger::get().importantInfo("Registering system: " + name);
        // Create a signature for this system
        assert(!ECS::getECS()->systemIsRegistered(name) && "Registering system more than once.");
        ECS::getECS()->registerSystem(name);
        Logger::get().success("Registered system: " + name);
        
    }
    
    template <class T>
    void addComponentRequirement() {
        ECS::getECS()->registerComponentIfNotRegistered<T>();
        ECS::getECS()->addComponentRequirementToSystem <T>(this->name(), ECS::getECS()->getComponentID <T>());
    }
    
    [[nodiscard]] Signature &getSignature() const {
        return ECS::getECS()->getSignature(this->name());
    }
    
    [[nodiscard]] std::set <EntityID> &getAssociatedEntities() const {
        return ECS::getECS()->getAssociatedEntities(this->name());
    }
    
    virtual void init() = 0;


protected:
    [[nodiscard]] std::string name() const { return typeid(*this).name(); }
    template <class T>
    inline T &getComponent(EntityID entityId) {
        return ECS::getECS()->getComponent <T>(entityId);
    }
};
