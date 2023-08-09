/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "engine/ecs/frontend/entity/Entity.h"
#include "engine/ecs/backend/Coordinator.h"
#include "engine/core/logger/Logger.h"
#include <set>
#include <memory>

class System {
    friend class Entity;

public:
    System();
    
    template<class T>
    void addComponentRequirement() {
        GLESC::ECS::getECS()
                ->addComponentRequirementToSystem<T>(this->name());
    }
    
    [[nodiscard]] std::set<EntityID> getAssociatedEntities() const;


protected:
    [[nodiscard]] inline SystemName name() const { return typeid(*this).name(); }
    
    template<class T>
    inline T &getComponent(EntityID entityId) {
        return GLESC::ECS::getECS()->getComponent<T>(entityId);
    }
};
