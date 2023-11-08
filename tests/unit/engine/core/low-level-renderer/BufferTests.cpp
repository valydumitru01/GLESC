/******************************************************************************
 * @file   BufferTests.cpp
 * @author Valentin Dumitru
 * @date   2023-11-06
 * @brief  Add description of this file if needed @todo 
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#include <gtest/gtest.h>
#include <engine/subsystems/renderer/shaders/Shader.h>
#include "engine/core/low-level-renderer/buffers/vertex/VertexArray.h"
#include "engine/core/low-level-renderer/buffers/vertex/VertexBufferLayout.h"
#include "engine/subsystems/renderer/mesh/MeshFactory.h"
#include "engine/core/low-level-renderer/buffers/vertex/VertexBuffer.h"
#include "engine/core/low-level-renderer/buffers/index/IndexBuffer.h"
#include "engine/subsystems/renderer/Renderer.h"

TEST(BufferTests, test) {
    GLESC::WindowManager window;
    GLESC::Renderer renderer(window);
    GLESC::Shader shader("Shader.glsl");
    
    auto* positions = new GAPIfloat[12]{
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.5f,  0.5f,
        -0.5f,  0.5f
    };
    auto* indices = new GAPIuint[6]{
        0, 1, 2,
        2, 3, 0
    };
    
    
    
    GLESC::VertexArray va;
    GLESC::VertexBuffer vb(positions, 12);
    GLESC::IndexBuffer ib(indices, 6);
    
    GLESC::VertexBufferLayout layout;
    layout.push<ShaderDataType::Float, ShaderDataDim::Vec2>();
    
    va.addBuffer(vb, layout);
    
    
    ib.bind();
    va.bind();
    vb.unbind();
    shader.unbind();
    
    for (int i = 0; i < 1000; ++i) {
        gapi.clear({GAPIValues::ClearBitsColor, GAPIValues::ClearBitsDepth,
                    GAPIValues::ClearBitsStencil});
        gapi.clearColor(0.2f, 0.3f, 0.3f, 1.0f);
        shader.bind();
        shader.setVec3("color", {0.2f, 0.3f, 0.8f});
        
        gapi.swapBuffers(window.getWindow());
    }
    
}