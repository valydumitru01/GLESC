/**************************************************************************************************
 * @file   Gapi.h
 * @author Valentin Dumitru
 * @date   2023-11-07
 * @brief Abstracts the graphic API used by the engine.
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "engine/Config.h"


#ifdef GLESC_OPENGL
#include "engine/core/low-level-renderer/graphic-api/concrete-apis/opengl/OpenGLAPI.h"
#endif
#ifdef GLESC_VULKAN
#include "engine/core/low-level-renderer/graphic-api/concrete-apis/vulkan/VulkanAPI.h"
#endif
#ifdef GLESC_DIRECTX
#include "engine/core/low-level-renderer/graphic-api/concrete-apis/directx/DirectXAPI.h"
#endif
/**
 * @brief Returns the graphic API used by the engine.
 * @details The graphic API is chosen at compile time based on the GLESC_OPENGL, GLESC_VULKAN, and GLESC_DIRECTX macros.
 * @return The graphic API used by the engine.
 */
inline auto& getGAPI() {
#ifdef GLESC_OPENGL
    static GLESC::GAPI::OpenGLAPI gapi;
#endif
#ifdef GLESC_VULKAN
    static GLESC::GAPI::VulkanAPI gapi;
#endif
#ifdef GLESC_DIRECTX
    static GLESC::GAPI::DirectXAPI gapi;
#endif
    return gapi;
}
