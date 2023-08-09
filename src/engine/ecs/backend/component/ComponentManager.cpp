/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/ecs/backend/component/ComponentManager.h"
using namespace GLESC;

void ComponentManager::entityDestroyed(EntityID entity) {
    for (auto const &pair : componentArrays) {
        auto const &component = pair.second;
        component.first->removeData(entity);
    }
}
