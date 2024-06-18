/******************************************************************************
 * @file   MatrixAsserts.h
 * @author Valentin Dumitru
 * @date   2023-10-14
 * @brief  @todo Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#pragma once

#include "engine/core/asserts/Asserts.h"

#define S_ASSERT_MAT_IS_OF_SIZE(N, M, expectedN, expectedM) \
    S_ASSERT_EQUAL(N, expectedN, \
    "Matrix size is incorrect, expected size"#expectedN); \
    S_ASSERT_EQUAL(M, expectedM, \
    "Matrix size is incorrect, expected size"#expectedM);

#define S_ASSERT_MAT_IS_SQUARE(N, M) \
    S_ASSERT_EQUAL(N, M, \
    "Matrix is not square");

#define S_ASSERT_ROTATION_NOT_AVAILABLE() \
    S_ASSERT_TRUE(false, \
        "Rotation is not available for this matrix" \
        ", only available for 3x3 and 4x4 matrices");