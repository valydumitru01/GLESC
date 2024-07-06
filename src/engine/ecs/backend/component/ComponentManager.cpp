
#include "engine/ecs/backend/component/ComponentManager.h"
using namespace GLESC::ECS;

void ComponentManager::entityDestroyed(EntityID entity) {
    for (auto const &[name, array] : componentArrays) {
        array->entityDestroyed(entity);
    }
}

bool ComponentManager::isComponentRegistered(ComponentID componentID) const {
    return componentNames.find(componentID) != componentNames.end();
}

ComponentName ComponentManager::getComponentName(ComponentID componentID) const {
    D_ASSERT_TRUE(isComponentRegistered(componentID), "Component must be registered to get its name");

    return componentNames.at(componentID);
}

IComponent &ComponentManager::getComponent(EntityID entity, ComponentID componentID) const {
    ComponentName componentName = getComponentName(componentID);
    IComponentArrayPtr componentArray = componentArrays.at(componentName);
    IComponent& component = componentArray->getComponent(entity);
    return component;
}
