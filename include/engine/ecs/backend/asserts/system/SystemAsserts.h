/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "engine/core/asserts/Asserts.h"

#define ASSERT_SYSTEM_IS_REGISTERED(name) \
    D_ASSERT(isSystemRegistered(name), \
    "System " + std::string(name) + " is not registered, and must be")

#define ASSERT_SYSTEM_IS_NOT_REGISTERED(name) \
    D_ASSERT_FALSE(isSystemRegistered(name), \
    "System " + std::string(name) + " is already registered, and must not be")

#define ASSERT_ENTITY_IS_ASSOCIATED_WITH_SYSTEM(systemName, entity) \
    D_ASSERT(isEntityAssociatedWithSystem(systemName, entity), \
    "Entity " + std::to_string(entity) + " is not in any system, and must be")

#define ASSERT_ENTITY_IS_NOT_ASSOCIATED_WITH_SYSTEM(systemName, entity) \
    D_ASSERT_FALSE(isEntityAssociatedWithSystem(systemName, entity), \
    "Entity " + std::to_string(entity) + " is already in a system, and must not be")

#define ASSERT_COMPONENT_IS_REQUIRED_BY_SYSTEM(systemName, componentID) \
    D_ASSERT(isComponentRequiredBySystem(systemName, componentID), \
    "System " + std::string(systemName) + " does not have component " + std::to_string(componentID) + ", and must have")

#define ASSERT_COMPONENT_IS_NOT_REQUIRED_BY_SYSTEM(systemName, componentID) \
    D_ASSERT_FALSE(isComponentRequiredBySystem(systemName,componentID), \
    "System " + std::string(systemName) + " has component " + std::to_string(componentID) + ", and must not have")