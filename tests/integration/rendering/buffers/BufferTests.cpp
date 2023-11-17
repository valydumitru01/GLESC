/**************************************************************************************************
 * @file   BufferTests.cpp
 * @author Valentin Dumitru
 * @date   2023-11-09
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#include <gtest/gtest.h>
#include <SDL2/SDL.h>
#include <engine/core/low-level-renderer/buffers/index/IndexBuffer.h>
#include <engine/core/low-level-renderer/buffers/vertex/VertexBuffer.h>
#include <engine/core/low-level-renderer/buffers/vertex/VertexArray.h>
#include <engine/core/window/WindowManager.h>
#include "engine/core/low-level-renderer/graphic-api/Gapi.h"
#include "../../../unit/engine/LoopHelper.h"

TEST(BufferTests, test) {
    GLESC::WindowManager windowManager;
    
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
    layout.push<GAPITypes::Float, DataTypeSize::SizeFloat, DataDimSize::Vec2>();
    
    va.addBuffer(vb, layout);
    
    
    ib.bind();
    va.bind();
    vb.unbind();
    
    LOOP(){
        gapi.clear({GAPIValues::ClearBitsColor, GAPIValues::ClearBitsDepth,
                    GAPIValues::ClearBitsStencil});
        gapi.clearColor(0.2f, 0.3f, 0.3f, 1.0f);
        
        
        gapi.swapBuffers(windowManager.getWindow());
    }
    
}