#pragma once

#include <set>
#include <memory>
#include "core/ECSFactory.h"

class System : public std::enable_shared_from_this<System> {
    friend class Entity;
private:
    std::set<EntityID> entities;

public:
    virtual void update() = 0;

protected:
    System() {
        const char *typeName = typeid(*this).name();

        assert(ECSFactory::getSystemContainer()->systems.find(typeName) ==
               ECSFactory::getSystemContainer()->systems.end() && "Registering system more than once.");


        ECSFactory::getSystemContainer()->systems.insert({typeName, shared_from_this()});
    }

    template<class T>
    void addComponentRequirement() {
        const char *typeName = typeid(T).name();

        Signature newSignature;
        newSignature.set(ECSFactory::getComponentContainer()->getComponentID<T>());

        // Modify the old signature
        ECSFactory::getSystemContainer()->signatures[typeName] |= newSignature;
    }
};

