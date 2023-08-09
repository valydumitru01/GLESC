/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/ecs/frontend/system/System.h"

using namespace GLESC;

System::System() {
    ECS::getECS()->registerSystem(name());
}

std::set<EntityID> System::getAssociatedEntities() const {
    return ECS::getECS()->getAssociatedEntities(this->name());
}