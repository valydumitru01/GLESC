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

#define S_ASSERT_MAT_IS_OF_SIZE(matN, matM, expectedN, expectedM) \
    S_ASSERT(matN == expectedN && matM == expectedM, \
        "Matrix size is incorrect, actual size is " #matN "x" #matM \
        ", expected size is " #expectedN "x" #expectedM);
