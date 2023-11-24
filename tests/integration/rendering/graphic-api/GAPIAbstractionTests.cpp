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
#include "LoopHelper.h"
#include "engine/core/low-level-renderer/graphic-api/Gapi.h"
#include "engine/core/window/WindowManager.h"
#include "engine/subsystems/renderer/shaders/ShaderLoader.h"
#include "integration/rendering/IBaseRenderTest.h"
#include "unit/engine/core/math/MathTestHelper.h"

class GAPIHelloTriangleTests : public IBaseRenderTest {
protected:
    GAPI::UInt VBO{};
    GAPI::UInt EBO{};
    GAPI::UInt VAO{};
    GAPI::UInt shaderProgram{};
    
    void prepareShaders() override {
        shaderProgram = ShaderLoader::loadShader(vertexShaderSource, fragmentShaderSource);
    }
    
    void prepareBuffers() override {
        // Vertex Array Object (VAO)
        gapi.genVertexArray(VAO);
        
        gapi.bindVertexArray(VAO);
        
        
        
        // Vertex Buffer Object (VBO)
        gapi.genBuffers(1, VBO);
        
        gapi.bindBuffer(GAPI::BufferTypes::Vertex, VBO);
        
        gapi.setBufferData(vertices.data(), vertices.size(),
                           GAPI::BufferTypes::Vertex,
                           GAPI::BufferUsages::StaticDraw);
        
        
        

        
        
        // Vertex Element Buffer Object (EBO)
        gapi.genBuffers(1, EBO);
        
        gapi.bindBuffer(GAPI::BufferTypes::Element, EBO);
        
        gapi.setBufferData(indices.data(), indices.size(),
                           GAPI::BufferTypes::Element,
                           GAPI::BufferUsages::StaticDraw);
        
        
        // Set vertex attributes for the currently bound VBO
        gapi.createVertexData(0, 2, GAPI::Types::Float, GAPI::Bool::False, 2 * sizeof(float), 0);
        
        gapi.enableVertexData(0);
        
        
        
        // Unbind VAO
        gapi.unbindVertexArray();
    }
    
    void render() override {
        // Render
        gapi.clearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, 1.0f);
        GLESC::Logger::get().success("Clear color set!");
        gapi.clear({GAPI::ClearBits::Color, GAPI::ClearBits::Depth,
                    GAPI::ClearBits::Stencil});
        
        // Use the shader
        gapi.useShaderProgram(shaderProgram);
        gapi.setUniform(shaderProgram, "uColor")->u4F(figureColor.r, figureColor.g,
                                                      figureColor.b, figureColor.a);
        // Draw the triangle
        gapi.bindVertexArray(VAO);
        
        gapi.drawTrianglesIndexed(6);
        
        gapi.unbindVertexArray();
        
        gapi.swapBuffers(windowManager.getWindow());
    }
    
    
    void destroyRender() override {
        // Cleanup
        gapi.deleteVertexArray(VAO);
        gapi.deleteBuffer(VBO);
        
        // Cleanup
        gapi.destroyShaderProgram(shaderProgram);
        gapi.deleteContext();
        windowManager.destroyWindow();
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

private:
    GLESC::WindowManager windowManager{};
};


TEST_F(GAPIHelloTriangleTests, test) {
    std::vector<float> actualVertices = gapi.getBufferDataF(VBO);
    ASSERT_EQ(actualVertices.size(), vertices.size());
    for (size_t i = 0; i < actualVertices.size(); ++i) {
        EXPECT_NEAR(actualVertices[i], vertices[i], dataEpsilon)
                            << "Vertex data mismatch at index " << i;
    }
    
    // Check if the background color is correct
    auto rgb = gapi.readPixelColorNormalized(10, 10);
    EXPECT_NEAR(rgb.r, backgroundColor.r, colorEpsilon);
    EXPECT_NEAR(rgb.g, backgroundColor.g, colorEpsilon);
    EXPECT_NEAR(rgb.b, backgroundColor.b, colorEpsilon);
    
    // Check if the triangle is drawn correctly
    // The shader program is set to draw a triangle with the color red
    auto rgb1 = gapi.readPixelColorNormalized(400, 300);
    EXPECT_NEAR(rgb1.r, figureColor.r, colorEpsilon);
    EXPECT_NEAR(rgb1.g, figureColor.g, colorEpsilon);
    EXPECT_NEAR(rgb1.b, figureColor.b, colorEpsilon);
}


