/******************************************************************************
 * @file   GapiTypes.h
 * @author Valentin Dumitru
 * @date   2023-11-07
 * @brief  Add description of this file if needed @todo 
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#pragma once
#include "engine/Config.h"

#ifdef GLESC_OPENGL
#include <GL/glew.h>
using GAPIbool = GLboolean;
using GAPIuint = GLuint;
using GAPIfloat = GLfloat;
using GAPIint = GLint;
using GAPIsize = GLuint;
using GAPIchar = GLchar;
using GAPIvoid = GLvoid;
using GAPIenum = GLenum;
using GAPIbitfield = GLbitfield;
using GAPIbyte = GLbyte;

#define GAPI_FALSE GL_FALSE
#define GAPI_TRUE GL_TRUE


#endif

#ifdef GLESC_VULKAN

#endif

#ifdef GLESC_DIRECTX

#endif

