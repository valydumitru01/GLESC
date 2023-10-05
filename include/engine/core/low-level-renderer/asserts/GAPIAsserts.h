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


#define ASSERT_GL_CORRECT_VERSION() \
    ASSERT(isGLCorrectVersion(GLESC_GL_MAJOR_VERSION, GLESC_GL_MINOR_VERSION), \
    "OpenGL version is not supported")

#define ASSERT_GL_CALL_IS_CORRECT(isCorrect, message) \
    ASSERT(isCorrect, \
    "OpenGL call is not correct")

[[maybe_unused]] inline bool isGLCorrectVersion(int glslMajorVersion, int glslMinorVersion){
    return glslMajorVersion >= GLESC_MINIMUM_MAJOR_VERSION
    && glslMinorVersion >= GLESC_MINIMUM_MINOR_VERSION;
}
