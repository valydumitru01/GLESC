/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once
#include "engine/core/asserts/Asserts.h"


#define ASSERT_GL_CORRECT_VERSION() \
    ASSERT(isGLCorrectVersion(GLESC_GL_MAJOR_VERSION, GLESC_GL_MINOR_VERSION), "OpenGL version is not supported")

[[maybe_unused]] inline bool isGLCorrectVersion(int glslMajorVersion, int glslMinorVersion){
    return glslMajorVersion >= GLESC_MINIMUM_MAJOR_VERSION
    && glslMinorVersion >= GLESC_MINIMUM_MINOR_VERSION;
}
