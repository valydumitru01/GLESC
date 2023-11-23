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
#include "LoopHelper.h"
#include "engine/core/low-level-renderer/buffers/index/IndexBuffer.h"
#include "engine/core/low-level-renderer/buffers/vertex/VertexArray.h"
#include "engine/core/low-level-renderer/buffers/vertex/VertexBuffer.h"
#include "engine/core/low-level-renderer/graphic-api/Gapi.h"
#include "engine/core/window/WindowManager.h"
#include "engine/subsystems/renderer/shaders/ShaderLoader.h"
#include "integration/rendering/GAPIBaseRenderTest.h"


class BufferTests : public GAPIBaseRenderTest {
protected:
    GLESC::WindowManager windowManager;
    // These are pointers because we don't want to call the constructor
    GLESC::VertexArray* va;
    GLESC::VertexBuffer* vb;
    GLESC::IndexBuffer* ib;
    GAPIuint shaderProgram{};
    
    void prepareShaders() override {
        shaderProgram = ShaderLoader::loadShader(vertexShaderSource, fragmentShaderSource);
        GLESC::Logger::get().success("Shader program created successfully");
    }
    
    void prepareBuffers() override {
        GLESC::Logger::get().success("Creating buffers...");
        va = new GLESC::VertexArray();
        GLESC::Logger::get().success("Vertex array created!");
        vb = new GLESC::VertexBuffer(vertices);
        GLESC::Logger::get().success("Vertex buffer created!");
        ib = new GLESC::IndexBuffer(indices);
        GLESC::Logger::get().success("Index buffer created!");
        
        GLESC::VertexBufferLayout layout;
        layout.push(GAPIType::Vec2F, 2);
        GLESC::Logger::get().success("Vertex buffer layout created!");
        
        va->addBuffer(*vb, layout);
        GLESC::Logger::get().success("Vertex buffer added to vertex array!");
        
    }
    
    void destroyRender() override {
        ib->destroy();
        vb->destroy();
        va->destroy();
        
        delete ib;
        delete vb;
        delete va;
        
        gapi.destroyShaderProgram(shaderProgram);
        gapi.deleteContext();
        windowManager.destroyWindow();
    }
    
    void render() override {
        gapi.clear({GAPIValues::ClearBitsColor, GAPIValues::ClearBitsDepth,
                    GAPIValues::ClearBitsStencil});
        gapi.clearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b,
                         backgroundColor.a);
        va->bind();
        gapi.drawTrianglesIndexed(indices.size());
        
        gapi.swapBuffers(windowManager.getWindow());
    }
    
    void SetUp() override {
        prepareShaders();
        prepareBuffers();
        
        LOOP() {
            render();
        }
    }
    
    void TearDown() override {
    }
    
private:
};

TEST_F(BufferTests, test) {
    checkBackgroundColor();
    checkTriangleColor();
    checkBufferData(vb->getBufferID());
    checkBufferData(ib->getBufferID());
}