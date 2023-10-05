/******************************************************************************
 * @file   Example.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/ecs/backend/component/ComponentManager.h"
using namespace GLESC;

void ComponentManager::entityDestroyed(EntityID entity) {
    for (auto const &[name, array] : componentArrays) {
        array->removeData(entity);
    }
}
