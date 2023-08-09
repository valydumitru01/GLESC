/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "engine/core/asserts/Asserts.h"

#define ASSERT_SYSTEM_IS_REGISTERED(name, systems) \
    ASSERT_FALSE(systems.find(name) == systems.end(), \
    "System " + std::string(name) + " is not registered, and must be");

#define ASSERT_SYSTEM_IS_NOT_REGISTERED(name, systems) \
    ASSERT(systems.find(name) == systems.end(), \
    "System " + std::string(name) + " is already registered, and must not be");