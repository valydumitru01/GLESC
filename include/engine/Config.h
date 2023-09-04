/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

/*
 * This file contains the configuration of the engine.
 *
 * You must choose a rendering API. You can choose between OpenGL, Vulkan and DirectX.
 * Comment and uncomment the following lines to choose the rendering API.
 * You can also choose the version of the API.
 *
 * It's also needed to choose the version of the shader language.
 * The shader language in use is GLSL. Therefore, the version of the shader language is the same as the
 * version of OpenGL. So, if you choose to render with OpenGL, the shader language version will be the same as the
 * OpenGL version. But if you choose to render with Vulkan or DirectX, you must choose the version of the shader
 * language, leaving the GL version uncommented.
 */

// ####################################################################################
// #################################### WINDOW CONFIG #################################

// Default values for the window configuration
#define GLESC_WINDOW_WIDTH 800
#define GLESC_WINDOW_HEIGHT 450

// More info: https://wiki.libsdl.org/SDL_CreateWindow
#define GLESC_WINDOW_X SDL_WINDOWPOS_CENTERED
#define GLESC_WINDOW_Y SDL_WINDOWPOS_CENTERED

#define GLESC_WINDOW_TITLE "Game Engine"
#define GLESC_WINDOW_FULLSCREEN SDL_FALSE

// ####################################################################################
// #################################### RENDER API ####################################

#define GLESC_RENDER_API OpenGLAPI
// The minimum version of OpenGL supported by the engine
// Do not change this values unless you know what you are doing,
// and you rewrite the code to support the new version
// This will change the assert in the GAPIAsserts.h file
// It will allow the engine to run even if the OpenGL version is not supported
#define GLESC_MINIMUM_MAJOR_VERSION 4
#define GLESC_MINIMUM_MINOR_VERSION 3

#define GLESC_GL_MAJOR_VERSION 4
#define GLESC_GL_MINOR_VERSION 6
#define GLESC_GL_CORE_PROFILE true

// #define GLESC_RENDER_API VulkanAPI
// #define GLESC_VULKAN_VERSION_MAJOR 1
// #define GLESC_VULKAN_VERSION_MINOR 2

// #define GLESC_RENDER_API DirectXAPI
// #define GLESC_DIRECTX_VERSION_MAJOR 12
// #define GLESC_DIRECTX_VERSION_MINOR 0


// Are the same as the OpenGL version
#define GLESC_GLSL_MAJOR_VERSION GLESC_GL_MAJOR_VERSION
#define GLESC_GLSL_MINOR_VERSION GLESC_GL_MINOR_VERSION
#define GLESC_GLSL_CORE_PROFILE GLESC_GL_CORE_PROFILE
// ####################################################################################
// ################################ ENTITY COMPONENT SYSTEM ###########################

#define GLESC_ECS_MAX_ENTITIES 5000
#define GLESC_ECS_MAX_COMPONENTS 32

