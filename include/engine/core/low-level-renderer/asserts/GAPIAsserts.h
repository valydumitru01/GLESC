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
#include "engine/Config.h"


#define D_ASSERT_GL_CORRECT_VERSION() \
    D_ASSERT_TRUE(isGLCorrectVersion(GLESC_GL_MAJOR_VERSION, GLESC_GL_MINOR_VERSION), \
    "OpenGL version is not supported")

#define D_ASSERT_GL_CALL_IS_CORRECT(isCorrect, message) \
    D_ASSERT_TRUE(isCorrect, \
    "OpenGL call is not correct \n" + std::string(message))

#define D_ASSERT_GLEW_OK(isGlewOk, message) \
    D_ASSERT_TRUE(isGlewOk,std::string("Unable to initialize GLEW: ")+ message)


[[maybe_unused]] inline bool isGLCorrectVersion(int glslMajorVersion, int glslMinorVersion){
    return glslMajorVersion >= GLESC_MINIMUM_MAJOR_VERSION
    && glslMinorVersion >= GLESC_MINIMUM_MINOR_VERSION;
}
