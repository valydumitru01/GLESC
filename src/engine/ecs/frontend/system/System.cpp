/******************************************************************************
 * @file   System.cpp
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/ecs/frontend/system/System.h"

using namespace GLESC::ECS;

System::System(ECSCoordinator &ecs, const SystemName& name) : ecs(ecs), name(name) {
    ecs.registerSystem(name);
}

const std::set<EntityID>& System::getAssociatedEntities() const {
    return ecs.getAssociatedEntities(name);
}

 boost::bimap<EntityName, EntityID> System::getAllEntities() const {
    return ecs.getAllEntities();
}

std::vector<IComponent*> System::getComponents(EntityID entityId) const {
    return ecs.getComponents(entityId);
}

const EntityName& System::getEntityName(EntityID entityId) const {
    return ecs.getEntityName(entityId);
}