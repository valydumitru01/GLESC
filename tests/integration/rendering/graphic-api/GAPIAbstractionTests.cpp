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
    GAPIuint VBO{};
    GAPIuint EBO{};
    GAPIuint VAO{};
    GAPIuint shaderProgram{};
    
    void prepareShaders() override {
        shaderProgram = ShaderLoader::loadShader(vertexShaderSource, fragmentShaderSource);
        GLESC::Logger::get().success("Shader program created successfully");
    }
    
    void prepareBuffers() override {
        // Vertex Buffer Object (VBO)
        gapi.genBuffers(1, VBO);
        GLESC::Logger::get().success("VBO created!");
        
        gapi.bindBuffer(GAPIValues::BufferTypeVertex, VBO);
        GLESC::Logger::get().success("VBO bound!");
        
        gapi.setBufferData(vertices.data(), vertices.size() * sizeof(float),
                           GAPIValues::BufferTypeVertex,
                           GAPIValues::BufferUsageStaticDraw);
        GLESC::Logger::get().success("VBO data set!");
        
        // Vertex Array Object (VAO)
        gapi.genVertexArray(VAO);
        GLESC::Logger::get().success("VAO created!");
        
        gapi.bindVertexArray(VAO);
        GLESC::Logger::get().success("VAO bound!");
        
        // Set vertex attributes
        gapi.createVertexData(0, 2, GAPIType::Float, GAPI_FALSE, 2 * sizeof(float), 0);
        GLESC::Logger::get().success("Vertex attributes set!");
        
        gapi.enableVertexData(0);
        GLESC::Logger::get().success("Vertex attributes enabled!");
        
        // Vertex Element Buffer Object (EBO)
        gapi.genBuffers(1, EBO);
        GLESC::Logger::get().success("EBO created!");
        
        gapi.bindBuffer(GAPIValues::BufferTypeElement, EBO);
        GLESC::Logger::get().success("EBO bound!");
        
        gapi.setBufferData(indices.data(), indices.size() * sizeof(GAPIuint),
                           GAPIValues::BufferTypeElement,
                           GAPIValues::BufferUsageStaticDraw);
        
        
        
        gapi.unbindBuffer(GAPIValues::BufferTypeVertex);
        // Unbind VAO
        gapi.unbindVertexArray();
        GLESC::Logger::get().success("VAO unbound!");
    }
    
    void render() override {
        
        // Render
        gapi.clearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, 1.0f);
        GLESC::Logger::get().success("Clear color set!");
        gapi.clear({GAPIValues::ClearBitsColor, GAPIValues::ClearBitsDepth,
                    GAPIValues::ClearBitsStencil});
        GLESC::Logger::get().success("Clear values set!");
        
        // Use the shader
        gapi.useShaderProgram(shaderProgram);
        gapi.setUniform(shaderProgram, "uColor")->u4F(figureColor.r, figureColor.g,
                                                      figureColor.b, figureColor.a);
        GLESC::Logger::get().success("Shader color set!");
        // Draw the triangle
        gapi.bindVertexArray(VAO);
        GLESC::Logger::get().success("VAO bound!");
        
        gapi.drawTrianglesIndexed(6);
        GLESC::Logger::get().success("Triangle drawn!");
        
        gapi.unbindVertexArray();
        GLESC::Logger::get().success("VAO unbound!");
        
        gapi.swapBuffers(windowManager.getWindow());
        GLESC::Logger::get().success("Window swapped");
    }
    
    
    void destroyRender() override {
        // Cleanup
        gapi.deleteVertexArray(VAO);
        GLESC::Logger::get().success("VAO deleted!");
        gapi.deleteBuffer(VBO);
        GLESC::Logger::get().success("VBO deleted!");
        
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
        std::cout << "Vertex data " << i << ": " << actualVertices[i] << "\n";
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


