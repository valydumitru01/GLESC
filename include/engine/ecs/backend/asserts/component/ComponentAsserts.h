/******************************************************************************
 * @file   ComponentAsserts.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "engine/core/asserts/Asserts.h"
#include "../../component/IComponent.h"

#define ASSERT_IS_COMPONENT(component) \
    static_assert(std::is_base_of<IComponent, component>::value, \
    "T must inherit from Component")

#define ASSERT_IS_COMPONENT_REGISTERED(component) \
    D_ASSERT_TRUE(isComponentRegistered<component>(), \
    "Component is already registered, and must not be")

#define ASSERT_IS_COMPONENT_NOT_REGISTERED(component) \
    D_ASSERT_FALSE(isComponentRegistered<component>(), \
    "Component is not registered, and must be")

#define ASSERT_IS_COMPONENT_REGISTERED_BY_ID(componentID) \
    D_ASSERT_TRUE(isComponentRegistered(componentID), \
    "Component is already registered, and must not be")

#define ASSERT_ENTITY_HAS_COMPONENT(entity, component) \
    D_ASSERT_TRUE(getComponentArray<Component>()->hasComponent(entity), "Entity does not have the component");