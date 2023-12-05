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
    GAPI::RGBColorNormalized backgroundColor = {0.2f, 0.3f, 0.3f, 1.0f};
    GAPI::RGBColorNormalized expectedTriangleColor = {1.0f, 0.0f, 0.0f, 1.0f};
    // Square
    std::vector<GAPI::Float> vertices = {
           /* x      y   */
            -0.5f, -0.5f,  // bottom left
             0.5f, -0.5f,  // bottom right
             0.5f,  0.5f,  // top right
            -0.5f,  0.5f,  // top left
    };
    std::vector<GAPI::UInt> indices = {0, 1, 2, 2, 3, 0};
    
    const char *vertexShaderSource = R"glsl(
        layout (location = 0) in vec3 position;
        layout (location = 1) in vec2 uv;


        out vec2 v_UV;
        void main() {
            gl_Position = vec4(position, 1.0);
        }
    
        )glsl";
    
    const char *fragmentShaderSource = R"glsl(
        in vec2 v_UV;

        uniform vec4 uColor; // Uniform for color (not used in this test)
        uniform sampler2D uTexture; // Uniform for texture

        layout (location = 0) out vec4 color;

        void main() {
            vec4 texColor = texture(uTexture, v_UV);
            // Texture is "not set", use the solid color
            color = uColor;
        }
        
        )glsl";
    
    virtual void prepareShaders() = 0;
    
    virtual void prepareBuffers() = 0;
    
    virtual void destroyRender() = 0;
    
    virtual void render() = 0;


protected:
};