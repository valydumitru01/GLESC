/**************************************************************************************************
 * @file   ComponentArrayAsserts.h
 * @author Valentin Dumitru
 * @date   05/03/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024$ Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

#include "engine/core/asserts/Asserts.h"

#define ASSERT_ENTITY_EXISTS(entity)\
    D_ASSERT_NOT_EQUAL(entityToIndexMap.left.find(entity), entityToIndexMap.left.end(), "Entity does not exist");