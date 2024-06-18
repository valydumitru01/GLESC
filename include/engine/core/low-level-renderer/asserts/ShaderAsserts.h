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
#define D_ASSERT_SHADER_TOKEN_FOUND(shader)\
    D_ASSERT_TRUE(false, #shader "shader token not found in shader file.")

#define D_ASSERT_SHADER_CODE_FOUND(shader)\
    D_ASSERT_TRUE(false, #shader "shader code not found.")

#define D_ASSERT_COMPILATION_OK(shaderType) \
    char *infoLog = new char[512];\
    D_ASSERT_TRUE(getGAPI().compilationOK(shaderType, infoLog), \
        "Compilation failed, error message " + std::string(infoLog));\
    delete[] infoLog;


#define D_ASSERT_LINKING_OK(shaderProgram) \
    char *infoLog = new char[512];\
    D_ASSERT_TRUE(getGAPI().linkOK(shaderProgram, infoLog), \
        "Linking failed, error message " + std::string(infoLog));\
    delete[] infoLog;