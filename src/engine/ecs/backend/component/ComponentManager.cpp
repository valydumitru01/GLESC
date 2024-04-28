/******************************************************************************
 * @file   ComponentManager.cpp
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/ecs/backend/component/ComponentManager.h"
using namespace GLESC::ECS;

void ComponentManager::entityDestroyed(EntityID entity) {
    for (auto const &[name, array] : componentArrays) {
        array->removeData(entity);
    }
}

bool ComponentManager::isComponentRegistered(ComponentID componentID) const {
    return componentNames.find(componentID) != componentNames.end();
}

ComponentName ComponentManager::getComponentName(ComponentID componentID) const {
    ASSERT_IS_COMPONENT_REGISTERED_BY_ID(componentID);

    return componentNames.at(componentID);
}

IComponent &ComponentManager::getComponent(EntityID entity, ComponentID componentID) const {
    ComponentName componentName = getComponentName(componentID);
    IComponentArrayPtr componentArray = componentArrays.at(componentName);
    IComponent& component = componentArray->getComponent(entity);
    return component;
}
