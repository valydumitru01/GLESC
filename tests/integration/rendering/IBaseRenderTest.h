/**************************************************************************************************
 * @file   IRenderTest.h
 * @author Valentin Dumitru
 * @date   2023-11-18
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

#include <gtest/gtest.h>
#include "engine/core/low-level-renderer/graphic-api/GapiStructs.h"

class IBaseRenderTest : public ::testing::Test {
public:
    static constexpr auto colorEpsilon = 0.05f;
    static constexpr auto dataEpsilon = 0.001f;
    RGBColorNormalized backgroundColor = {0.2f, 0.3f, 0.3f, 1.0f};
    RGBColorNormalized figureColor = {1.0f, 0.0f, 0.0f, 1.0f};
    // Square
    std::vector<GAPIfloat> vertices = {
            -0.5f, -0.5f, // bottom left
            0.5f, -0.5f, // bottom right
            0.5f, 0.5f, // top right
            -0.5f, 0.5f // top left
    };
   std::vector<GAPIuint> indices = {0, 1, 2, 2, 3, 0};
    
    const char* vertexShaderSource = R"glsl(
        layout (location = 0) in vec3 position;
        void main() {
            gl_Position = vec4(position, 1.0);
        }
        )glsl";
    
    const char* fragmentShaderSource = R"glsl(
        out vec4 color;
        uniform vec4 uColor; // Uniform for color
        void main() {
            color = uColor;
        }
        )glsl";
    
    virtual void prepareShaders() = 0;
    
    virtual void prepareBuffers() = 0;
    
    virtual void destroyRender() = 0;
    
    virtual void render() = 0;
    
    

protected:
};