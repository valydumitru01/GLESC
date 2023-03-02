#pragma once

#include "core/SystemContainer.h"
#include "core/EntityContainer.h"
#include "core/ComponentContainer.h"
#include "core/Types.h"
#include "EntityContainer.h"
#include <memory>
class ECSFactory {
public:
    static std::shared_ptr<ComponentContainer> getComponentContainer(){
        if(componentContainer== nullptr) {
            componentContainer = std::make_shared<ComponentContainer>();
        }
    }

    static std::shared_ptr<EntityContainer> getEntityContainer(){
        if(entityManager== nullptr) {
            entityManager = std::make_shared<EntityContainer>();
        }
    }

    static std::shared_ptr<SystemContainer> getSystemContainer(){
        if(systemContainer== nullptr) {
            systemContainer =std::make_shared<SystemContainer>();
        }
        return systemContainer;
    }


private:
	static std::shared_ptr<ComponentContainer> componentContainer;
    static std::shared_ptr<EntityContainer> entityManager;
    static std::shared_ptr<SystemContainer> systemContainer;
};
