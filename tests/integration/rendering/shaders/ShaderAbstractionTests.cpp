/**************************************************************************************************
 * @file   ShaderAbstractionTests.cpp
 * @author Valentin Dumitru
 * @date   2023-11-09
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#include <SDL2/SDL.h>
#include <gtest/gtest.h>

#include "LoopHelper.h"
#include "engine/core/low-level-renderer/buffers/index/IndexBuffer.h"
#include "engine/core/low-level-renderer/buffers/vertex/VertexArray.h"
#include "engine/core/low-level-renderer/buffers/vertex/VertexBuffer.h"
#include "engine/core/low-level-renderer/graphic-api/Gapi.h"
#include "engine/core/window/WindowManager.h"
#include "engine/subsystems/renderer/shaders/Shader.h"
#include "integration/rendering/GAPIBaseRenderTest.h"


class ShaderAbstractionTests : public GAPIBaseRenderTest {
protected:
    GLESC::WindowManager windowManager;
    // These are pointers because we don't want to call the constructor
    GLESC::VertexArray* vao;
    GLESC::VertexBuffer* vbo;
    GLESC::IndexBuffer* ibo;
    GLESC::Shader* shader;
    
    ShaderAbstractionTests() : GAPIBaseRenderTest() {
    }
    
    void prepareShaders() override {
        
        shader = new GLESC::Shader(vertexShaderSource, fragmentShaderSource);
    }
    
    void prepareBuffers() override {
        vao = new GLESC::VertexArray();
        vao->bind();
        vbo = new GLESC::VertexBuffer(vertices);
        ibo = new GLESC::IndexBuffer(indices);
        
        GLESC::VertexBufferLayout layout;
        layout.push(GAPI::Types::Vec2F);
        
        vao->addBuffer(*vbo, layout);
        
        
        vao->unbind();
        
    }
    
    void destroyRender() override {
        ibo->destroy();
        vbo->destroy();
        vao->destroy();
        
        delete ibo;
        delete vbo;
        delete vao;
        
        delete shader;
        gapi.deleteContext();
        windowManager.destroyWindow();
    }
    
    void render() override {
        gapi.clearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b,
                        backgroundColor.a);
        gapi.clear({GAPI::ClearBits::Color, GAPI::ClearBits::Depth,
                    GAPI::ClearBits::Stencil});
        vao->bind();
        shader->bind();
        shader->setUniform("uColor").u4F(expectedTriangleColor.r, expectedTriangleColor.g,
                                         expectedTriangleColor.b, expectedTriangleColor.a);
        gapi.drawTrianglesIndexed(indices.size());
        
        gapi.swapBuffers(windowManager.getWindow());
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

TEST_F(ShaderAbstractionTests, test) {
    checkBackgroundColor();
    checkTriangleColor();
    checkBufferData<GAPI::BufferTypes::Vertex>(vbo->getBufferID());
    checkBufferData<GAPI::BufferTypes::Index>(ibo->getBufferID());
}