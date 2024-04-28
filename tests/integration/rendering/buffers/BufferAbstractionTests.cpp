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

#include "LoopHelper.cpp"
#include "engine/core/low-level-renderer/buffers/IndexBuffer.h"
#include "engine/core/low-level-renderer/buffers/VertexArray.h"
#include "engine/core/low-level-renderer/buffers/VertexBuffer.h"
#include "engine/core/low-level-renderer/graphic-api/Gapi.h"
#include "engine/core/low-level-renderer/shader/ShaderLoader.h"
#include "engine/core/window/WindowManager.h"
#include "integration/rendering/RenderingTestHelper.h"


class BufferAbstractionTests : public ::testing::Test {
protected:
    GLESC::WindowManager windowManager;
    // These are pointers because we don't want to call the constructor
    VertexArray *vao{};
    VertexBuffer *vbo{};
    IndexBuffer *ibo{};
    UInt shaderProgram{};

    BufferAbstractionTests() = default;

    void prepareShaders() {
        shaderProgram = ShaderLoader::loadShader(vertexShaderSourceColor, fragmentShaderSourceColor);
    }

    void prepareBuffers() {
        vao = new VertexArray();
        vao->bind();
        vbo = new VertexBuffer(positionOnlyVertices.data(), positionOnlyVertices.size(),
                                            positionOnlyVertices.size() * sizeof(Float),
                                            Enums::BufferUsages::StaticDraw);
        ibo = new IndexBuffer(indices);

        VertexBufferLayout layout;
        layout.push(Enums::Types::Vec2F);

        vao->addBuffer(*vbo, layout);


        vao->unbind();
    }

    void render() {
        getGAPI().clearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b,
                             backgroundColor.a);
        getGAPI().clear({
            Enums::ClearBits::Color, Enums::ClearBits::Depth,
            Enums::ClearBits::Stencil
        });
        vao->bind();
        getGAPI().useShaderProgram(shaderProgram);
        getGAPI().setUniform(getGAPI().getUniformLocation("uColor"),
            Vec4F{expectedFigureColor.r, expectedFigureColor.g,expectedFigureColor.b, expectedFigureColor.a});
        getGAPI().drawTrianglesIndexed(indices.size());

        getGAPI().swapBuffers(windowManager.getWindow());
        getGAPI().swapBuffers(windowManager.getWindow());
    }

    void SetUp() override {
        prepareShaders();
        prepareBuffers();

        LOOP() {
            render();
        }
    }

    void TearDown() override {
        ibo->destroy();
        vbo->destroy();
        vao->destroy();

        delete ibo;
        delete vbo;
        delete vao;

        getGAPI().destroyShaderProgram(shaderProgram);
        getGAPI().deleteContext();
        windowManager.destroyWindow();
    }
};

TEST_F(BufferAbstractionTests, test) {
    checkBackgroundColor();
    checkCenterColor(expectedFigureColor);
    checkIndices(ibo->getBufferID(), indices);
    checkVertices(vbo->getBufferID(), positionOnlyVertices);
}
