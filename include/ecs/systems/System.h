#pragma once

#include "ecs/entities/Entity.h"
#include "core/ECSContainer.h"
#include <set>
#include <memory>

class System {
    friend class Entity;

public:
    
    explicit System(const std::string &name) {
        this->name = name;
        // Create a signature for this system
        ECS::getECS()->registerSystem(name);
        assert(!ECS::getECS()->systemIsRegistered(name) && "Registering system more than once.");
        Console::success("Registered system: " + name);
        
    }
    
    template <class T>
    void addComponentRequirement() {
        ECS::getECS()->addComponentRequirementToSystem <T>(name, ECS::getECS()->getComponentID <T>());
    }
    
    [[nodiscard]] Signature &getSignature() const {
        return ECS::getECS()->getSignature(name);
    }
    
    [[nodiscard]] std::set <EntityID> &getAssociatedEntities() const {
        return ECS::getECS()->getAssociatedEntities(name);
    }
    
    virtual void init() = 0;


protected:
    std::string name{};
    
    template <class T>
    inline T &getComponent(EntityID entityId) {
        return ECS::getECS()->getComponent <T>(entityId);
    }
};
