/******************************************************************************
 * @file   Example.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "engine/core/asserts/Asserts.h"
#include "engine/ecs/frontend/component/IComponent.h"

#define ASSERT_IS_COMPONENT(component) \
    static_assert(std::is_base_of<IComponent, component>::value, \
    "T must inherit from Component")

#define ASSERT_IS_COMPONENT_REGISTERED(component) \
    D_ASSERT_TRUE(isComponentRegistered<component>(), \
    "Component is already registered, and must not be")

#define ASSERT_IS_COMPONENT_NOT_REGISTERED(component) \
    D_ASSERT_FALSE(isComponentRegistered<component>(), \
    "Component is not registered, and must be")

