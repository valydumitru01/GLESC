/**************************************************************************************************
 * @file   RenderingTest.cpp
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
#include "engine/core/low-level-renderer/graphic-api/Gapi.h"
#include "engine/core/low-level-renderer/shader/ShaderLoader.h"
#include "engine/core/window/WindowManager.h"
#include "integration/rendering/RenderingTestHelper.h"
#include "unit/engine/core/math/MathCustomTestingFramework.cpp"

class GAPIAbstractionTests : public ::testing::Test {
protected:
    UInt VBO{};
    UInt IBO{};
    UInt VAO{};
    UInt shaderProgram{};


    void prepareShaders() {
        shaderProgram = ShaderLoader::loadShader(vertexShaderSourceColor, fragmentShaderSourceColor);
    }

    void prepareBuffers() {
        // Vertex Array Object (VAO)
        getGAPI().genVertexArray(VAO);

        getGAPI().bindVertexArray(VAO);


        // Vertex Buffer Object (VBO)
        getGAPI().genBuffers(1, VBO);

        getGAPI().bindBuffer(Enums::BufferTypes::Vertex, VBO);

        getGAPI().setBufferData(positionOnlyVertices.data(), positionOnlyVertices.size(),
                                positionOnlyVertices.size() * sizeof(float),
                                Enums::BufferTypes::Vertex, Enums::BufferUsages::StaticDraw);


        // Vertex Element Buffer Object (EBO)
        getGAPI().genBuffers(1, IBO);

        getGAPI().bindBuffer(Enums::BufferTypes::Index, IBO);

        getGAPI().setIndexBufferData(indices.data(), indices.size(), Enums::BufferUsages::StaticDraw);


        // Set vertex attributes for the currently bound VBO
        getGAPI().createVertexData(0, 2, Enums::Types::Float, Bool::False, 2 * sizeof(float), 0);

        getGAPI().enableVertexData(0);


        // Unbind VAO
        getGAPI().unbindVertexArray();
    }

    void render() {
        // Render
        getGAPI().clearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, 1.0f);
        Logger::get().success("Clear color set!");
        getGAPI().clear({
            Enums::ClearBits::Color, Enums::ClearBits::Depth,
            Enums::ClearBits::Stencil
        });

        // Use the shader
        getGAPI().useShaderProgram(shaderProgram);
        getGAPI().setUniform(getGAPI().getUniformLocation("uColor"),
                             Vec4F{
                                 expectedFigureColor.r, expectedFigureColor.g,
                                 expectedFigureColor.b, expectedFigureColor.a
                             });
        // Draw the triangle
        getGAPI().bindVertexArray(VAO);

        getGAPI().drawTrianglesIndexed(6);

        getGAPI().unbindVertexArray();

        getGAPI().swapBuffers(windowManager.getWindow());
        getGAPI().swapBuffers(windowManager.getWindow());
    }


    void destroyRender() const {
        // Cleanup
        getGAPI().deleteVertexArray(VAO);
        getGAPI().deleteBuffer(VBO);

        // Cleanup
        getGAPI().destroyShaderProgram(shaderProgram);
        getGAPI().deleteContext();
        SDL_Quit();
    }

    void SetUp() override {
        prepareShaders();
        prepareBuffers();

        LOOP() {
            render();
        }
    }

    void TearDown() override {
        destroyRender();
    }

protected:
    GLESC::WindowManager windowManager{};
};


TEST_F(GAPIAbstractionTests, test) {
    checkBackgroundColor();
    checkCenterColor(expectedFigureColor);

    checkIndices(IBO, indices);
    checkVertices(VBO, positionOnlyVertices);
}
