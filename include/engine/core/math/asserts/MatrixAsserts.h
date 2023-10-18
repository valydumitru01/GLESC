/******************************************************************************
 * @file   MatrixAsserts.h
 * @author Valentin Dumitru
 * @date   2023-10-14
 * @brief  Add description of this file if needed @todo 
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#pragma once

#include "engine/core/asserts/Asserts.h"

#define ASSERT_MAT_INIT_LIST_IS_OF_SIZE(N,M,list) \
    D_ASSERT_EQUAL(list.size(), N,              \
    "List size is incorrect, expected size"#N); \
    for (const auto& row : list) {              \
    D_ASSERT_EQUAL(row.size(), M,               \
    "List size is incorrect, expected size"#M); \
    }

#define S_ASSERT_MAT_IS_OF_SIZE(N, M, expectedN, expectedM) \
    S_ASSERT_EQUAL(N, expectedN, \
    "Matrix size is incorrect, expected size"#expectedN); \
    S_ASSERT_EQUAL(M, expectedM, \
    "Matrix size is incorrect, expected size"#expectedM);