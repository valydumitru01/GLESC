/**************************************************************************************************
 * @file   Gapi.h
 * @author Valentin Dumitru
 * @date   2023-11-07
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "engine/Config.h"


#ifdef GLESC_OPENGL
#include "engine/core/low-level-renderer/graphic-api/concrete-apis/opengl/OpenGLAPI.h"
inline GLESC::OpenGLAPI& getGAPI() {
    static GLESC::OpenGLAPI gapi;
    return gapi;
}
#endif

#ifdef GLESC_VULKAN
#include "engine/core/low-level-renderer/graphic-api/concrete-apis/vulkan/VulkanAPI.h"
inline GLESC::VulkanAPI& GetGAPI() {
    static GLESC::VulkanAPI gapi;
    return gapi;
}
#endif

#ifdef GLESC_DIRECTX
#include "engine/core/low-level-renderer/graphic-api/concrete-apis/directx/DirectXAPI.h"
inline GLESC::DirectXAPI& GetGAPI() {
    static GLESC::DirectXAPI gapi;
    return gapi;
}
#endif

