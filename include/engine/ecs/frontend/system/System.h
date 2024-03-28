/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "engine/ecs/backend/ECS.h"
#include <set>

namespace GLESC::ECS {
    class System {
        friend class Entity;

    public:
        explicit System(ECSCoordinator &ecs, const SystemName &name);

        template<class Component>
        void addComponentRequirement() {
            ecs.addComponentRequirementToSystem<Component>(name);
        }

        [[nodiscard]] const std::set<EntityID> &getAssociatedEntities() const;

        [[nodiscard]] boost::bimap<EntityName, EntityID> getAllEntities() const;

        [[nodiscard]] std::vector<IComponent*> getComponents(EntityID entityId) const;

        const EntityName& getEntityName(EntityID entityId) const;

    protected:
        template<class Component>
        Component &getComponent(EntityID entityId) {
            return ecs.getComponent<Component>(entityId);
        }

    private:
        ECSCoordinator &ecs;
        SystemName name;
    };
}
