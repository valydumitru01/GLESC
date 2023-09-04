/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "engine/ecs/frontend/entity/Entity.h"
#include "engine/ecs/backend/ECS.h"
#include "engine/core/logger/Logger.h"
#include <set>
#include <memory>

class System {
    friend class Entity;

public:
    explicit System(GLESC::ECS& ecs, const SystemName& name);
    
    template<class T>
    void addComponentRequirement() {
        ecs.addComponentRequirementToSystem<T>(name);
    }
    
    [[nodiscard]] std::set<EntityID> getAssociatedEntities() const;


protected:
    template<class T>
    inline T &getComponent(EntityID entityId) {
        return ecs.getComponent<T>(entityId);
    }
private:
    GLESC::ECS& ecs;
    SystemName name;
};
