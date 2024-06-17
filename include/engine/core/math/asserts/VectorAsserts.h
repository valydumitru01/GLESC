/******************************************************************************
 * @file   VectorAsserts.h
 * @author Valentin Dumitru
 * @date   2023-10-14
 * @brief  Contains custom asserts for vectors
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#pragma once

#include <cstddef>
#include "engine/core/asserts/Asserts.h"


#define S_ASSERT_VEC_IS_OF_SIZE_OR_BIGGER(expectedSize) \
    S_ASSERT_GREATER_OR_EQUAL(N, expectedSize,             \
        "Vector size is incorrect, expected size" #expectedSize  \
        " or bigger")

#define S_ASSERT_VEC_IS_OF_SIZE(expectedSize)           \
    S_ASSERT_EQUAL(N, expectedSize,                        \
        "Vector size is incorrect, expected size"#expectedSize)
    
#define D_ASSERT_VEC_IS_HOMOGENEOUS(vec)                          \
    D_ASSERT_TRUE(vec.isHomogeneous(),                            \
    "Vector is not homogenous")