#pragma once

#include <set>
#include <memory>
#include "core/types.h"
#include "core/SystemManager.h"

class System {
private:
    std::set<EntityID> entities;
    std::shared_ptr<SystemManager> systemManager;
public:
    void setSignature(Signature signature) {
        const char *typeName = typeid(*this).name();

        assert(systemManager->systems.find(typeName) != systemManager->systems.end() &&
               "System used before registered.");

        // Set the signature for this system
        systemManager->signatures.insert({typeName, signature});
    }
    void addComponentSignature();

    void entityIDSignatureChanged(EntityID EntityID, Signature EntityIDSignature)
    {
        // Notify each system that an EntityID's signature changed
        for (auto const& pair : systemManager->systems)
        {
            auto const& type = pair.first;
            auto const& system = pair.second;
            auto const& systemSignature = systemManager->signatures[type];

            // EntityID signature matches system signature - insert into set
            if ((EntityIDSignature & systemSignature) == systemSignature)
            {
                system->entities.insert(EntityID);
            }
                // EntityID signature does not match system signature - erase from set
            else
            {
                system->entities.erase(EntityID);
            }
        }
    }
protected:
    void registerSystem() {
        const char *typeName = typeid(*this).name();

        assert(systemManager->systems.find(typeName) == systemManager->systems.end() &&
               "Registering system more than once.");

        // Create a pointer to the system and return it, so it can be used externally
        auto system = std::make_shared<System>();
        systemManager->systems.insert({typeName, *this});
    }
};

