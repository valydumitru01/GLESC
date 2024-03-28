/**************************************************************************************************
 * @file   RendererTypes.h
 * @author Valentin Dumitru
 * @date   21/02/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "engine/core/low-level-renderer/buffers/vertex/VertexArray.h"

enum class RenderType {
    Static,
    Dynamic,
    InstancedStatic,
    InstancedDynamic
};

inline GAPI::BufferUsages getBufferUsage(RenderType renderType) {
    if (renderType == RenderType::Static) {
        return GAPI::BufferUsages::StaticDraw;
    }
    if (renderType == RenderType::Dynamic) {
        return GAPI::BufferUsages::DynamicDraw;
    }
    if (renderType == RenderType::InstancedStatic) {
        return GAPI::BufferUsages::StaticDraw;
    }
    if (renderType == RenderType::InstancedDynamic) {
        return GAPI::BufferUsages::DynamicDraw;
    }
    D_ASSERT_TRUE(false, "Unknown render type");
}

/**
 * @brief Vertex Array Object
 * @details We make the unique because we only want the renderer to own the VAOs
 */
using VertexArrayPtr = std::unique_ptr<GLESC::VertexArray>;

using Color = Vec4F;
using UV = Vec2F;
using Normal = Vec3F;
using Position = Vec3F;

using Model = Mat4F;
using View = Mat4F;
using Projection = Mat4F;
using VP = Mat4F;
using MVP = Mat4F;