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

#include "LoopHelper.cpp"
#include "engine/core/low-level-renderer/buffers/index/IndexBuffer.h"
#include "engine/core/low-level-renderer/buffers/vertex/VertexArray.h"
#include "engine/core/low-level-renderer/buffers/vertex/VertexBuffer.h"
#include "engine/core/low-level-renderer/graphic-api/Gapi.h"
#include "engine/core/window/WindowManager.h"
#include "engine/subsystems/renderer/shaders/Shader.h"
#include "integration/rendering/RenderingTestHelper.h"


class ShaderAbstractionTests : public ::testing::Test {
protected:
    GLESC::WindowManager windowManager;
    // These are pointers because we don't want to call the constructor
    GLESC::VertexArray* vao;
    GLESC::VertexBuffer* vbo;
    GLESC::IndexBuffer* ibo;
    GLESC::Shader* shader;
    
    ShaderAbstractionTests(){
    }
    
    void prepareShaders() {
        
        shader = new GLESC::Shader(vertexShaderSourceColor, fragmentShaderSourceColor);
    }
    
    void prepareBuffers() {
        vao = new GLESC::VertexArray();
        vao->bind();
        vbo = new GLESC::VertexBuffer(positionOnlyVertices.data(), positionOnlyVertices.size(),
            positionOnlyVertices.size() * sizeof(float), GAPI::BufferUsages::StaticDraw);
        ibo = new GLESC::IndexBuffer(indices);
        
        GLESC::VertexBufferLayout layout;
        layout.push(GAPI::Types::Vec2F);
        
        vao->addBuffer(*vbo, layout);
        
        
        vao->unbind();
        
    }
    
    void render() {
        getGAPI().clearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b,
                        backgroundColor.a);
        getGAPI().clear({GAPI::ClearBits::Color, GAPI::ClearBits::Depth,
                    GAPI::ClearBits::Stencil});
        vao->bind();
        shader->bind();
        shader->setUniform("uColor").u4F(expectedFigureColor.r, expectedFigureColor.g,
                                         expectedFigureColor.b, expectedFigureColor.a);
        getGAPI().drawTrianglesIndexed(indices.size());
        
        getGAPI().swapBuffers(windowManager.getWindow());
        getGAPI().swapBuffers(windowManager.getWindow());
    }
    
    void SetUp() override {
        prepareShaders();
        prepareBuffers();
        
        render();
    }
    
    void TearDown() override {
        ibo->destroy();
        vbo->destroy();
        vao->destroy();
        
        delete ibo;
        delete vbo;
        delete vao;
        
        delete shader;
        windowManager.destroyWindow();
    }

private:
};

TEST_F(ShaderAbstractionTests, test) {
    checkBackgroundColor();
    checkCenterColor(expectedFigureColor);
    checkIndices(ibo->getBufferID(),indices);
    checkVertices(vbo->getBufferID(),positionOnlyVertices);
}