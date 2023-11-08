/**************************************************************************************************
 * @file   ShaderAsserts.h
 * @author Valentin Dumitru
 * @date   2023-11-08
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "engine/core/asserts/Asserts.h"
#define SHADER_TOKEN_NOT_FOUND(shader)\
    D_ASSERT_TRUE(false, #shader "shader token not found in shader file.")

#define SHADER_MISSING_CODE(shader)\
    D_ASSERT_TRUE(false, #shader "shader code not found.")