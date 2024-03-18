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

std::set<EntityID> System::getAssociatedEntities() const {
    return ecs.getAssociatedEntities(name);
}