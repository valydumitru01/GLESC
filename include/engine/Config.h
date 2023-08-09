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

#define GLESC_WINDOW_X SDL_WINDOWPOS_CENTERED
#define GLESC_WINDOW_Y SDL_WINDOWPOS_CENTERED

#define GLESC_WINDOW_TITLE "Game Engine"
#define GLESC_WINDOW_FULLSCREEN false

// ####################################################################################
// #################################### RENDER API ####################################

#define GLESC_RENDER_OPENGL
#define GLESC_GL_MAJOR_VERSION 4
#define GLESC_GL_MINOR_VERSION 60
#define GLESC_GL_CORE_PROFILE true

// #define GLESC_RENDER_VULKAN
// #define GLESC_VULKAN_VERSION_MAJOR 1
// #define GLESC_VULKAN_VERSION_MINOR 2

// #define GLESC_RENDER_DIRECTX
// #define GLESC_DIRECTX_VERSION_MAJOR 12
// #define GLESC_DIRECTX_VERSION_MINOR 0

// ####################################################################################
// ################################ ENTITY COMPONENT SYSTEM ###########################

#define GLESC_ECS_MAX_ENTITIES 5000
#define GLESC_ECS_MAX_COMPONENTS 32