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
    
    GLESC::Mesh cube = GLESC::MeshFactory::cube(3);
    GLESC::VertexArray va;
    
    GLESC::VertexBuffer vb(cube.getVertices(), cube.getVertices().size());
    GLESC::IndexBuffer ib;
    GLESC::VertexBufferLayout layout;
    va.addBuffer(vb);
    
    GLESC::VertexBufferLayout layout;
    layout.push<float>(3);
    
    va.addLayout(layout);
    ib.bind();
    va.bind();
    
    for (int i = 0; i < 1000; ++i) {
        renderer.start();
        
        shader.bind();
        renderer.draw(va, ib, shader);
        window.update();
        
        renderer.end();
    }
    
}