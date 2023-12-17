/**************************************************************************************************
 * @file   RenderingTestHelper.h
 * @author Valentin Dumitru
 * @date   05/12/2023
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

#include <gtest/gtest.h>
#include "engine/core/low-level-renderer/graphic-api/Gapi.h"
#include "engine/core/low-level-renderer/graphic-api/GapiStructs.h"
#include "engine/Config.h"

static constexpr auto colorEpsilon = 0.05f;
static constexpr auto dataEpsilon = 0.001f;
static GAPI::RGBAColorNormalized backgroundColor = {0.2f, 0.3f, 0.3f, 1.0f};
static GAPI::RGBAColorNormalized expectedFigureColor = {1.0f, 0.0f, 0.0f, 1.0f};
static std::string vertexShaderSourceColor = R"glsl(
        layout (location = 0) in vec3 position;
        void main() {
            gl_Position = vec4(position, 1.0);
        }
        )glsl";

static std::string fragmentShaderSourceColor = R"glsl(
        uniform vec4 uColor; // Uniform for color
        layout (location = 0) out vec4 color;
        void main() {
            color = uColor;
        }
    )glsl";

static std::vector<GAPI::Float> positionOnlyVertices = {
        /* x      y   */
        -0.5f, -0.5f, // bottom left
        0.5f, -0.5f,  // bottom right
        0.5f, 0.5f,   // top right
        -0.5f, 0.5f,  // top left
};

static std::string vertexShaderSourceTexture = R"glsl(
        layout (location = 0) in vec3 position;
        layout (location = 1) in vec2 uv;
        out vec2 v_UV;
        void main() {
            gl_Position = vec4(position, 1.0);
            v_UV = uv;
        }
        )glsl";

static std::string fragmentShaderSourceTexture = R"glsl(
        in vec2 v_UV;
        uniform sampler2D uTexture; // Uniform for texture
        layout (location = 0) out vec4 color;
        void main() {
            vec4 texColor = texture(uTexture, v_UV);
            color = texColor;
        }
        
        )glsl";
static std::vector<GAPI::Float> positionAndUVVertices = {
        /* x      y      u     v */
        -0.5f, -0.5f, 0.0f, 0.0f, // bottom left
        0.5f, -0.5f, 1.0f, 0.0f,  // bottom right
        0.5f, 0.5f, 1.0f, 1.0f,  // top right
        -0.5f, 0.5f, 0.0f, 1.0f  // top left
};

static std::vector<GAPI::UInt> indices = {0, 1, 2, 2, 3, 0};

template<typename Type>
inline void printExpectNear(const std::string &message, Type expected, Type actual) {
    Logger::get().info("\tChecking " + message + ": expected[ "
                       + std::to_string(expected) + " ] == read[ " +
                       std::to_string(actual) + " ]");
}


inline void
checkPixelColor(GAPI::RGBAColorNormalized expected, GAPI::UInt xCoord, GAPI::UInt yCoord,
                std::string message) {
    Logger::get().info("============" + message + "=============");
    GAPI::RGBAColorNormalized readTriangleColor =
            getGAPI().readPixelColorNormalized(xCoord, yCoord);
    EXPECT_NEAR(expected.r, readTriangleColor.r, colorEpsilon);
    printExpectNear("color red", expected.r, readTriangleColor.r);
    EXPECT_NEAR(expected.g, readTriangleColor.g, colorEpsilon);
    printExpectNear("color green", expected.g, readTriangleColor.g);
    EXPECT_NEAR(expected.b, readTriangleColor.b, colorEpsilon);
    printExpectNear("color blue", expected.b, readTriangleColor.b);
    EXPECT_NEAR(expected.a, readTriangleColor.a, colorEpsilon);
    printExpectNear("color alpha", expected.a, readTriangleColor.a);
}

inline void checkBackgroundColor() {
    checkPixelColor(backgroundColor, 0, 0, "Checking Background color");
}

inline void checkCenterColor(GAPI::RGBAColorNormalized expected) {
    checkPixelColor(expected, GLESC_WINDOW_WIDTH / 2, GLESC_WINDOW_HEIGHT / 2,
                    "Checking Center color");
}

inline void checkVertices(GAPI::UInt bufferID, std::vector<GAPI::Float> &expectedVertices) {
    Logger::get().info("============Checking vertices=============");
    auto actualVertices = getGAPI().getBufferDataF(bufferID);
    EXPECT_EQ(expectedVertices.size(), actualVertices.size());
    for (size_t i = 0; i < expectedVertices.size(); ++i) {
        printExpectNear("vertex", expectedVertices[i], actualVertices[i]);
        EXPECT_NEAR(expectedVertices[i], actualVertices[i], dataEpsilon)
                            << "Vertex data mismatch at index " << i;
    }
}

inline void checkIndices(GAPI::UInt bufferID, std::vector<GAPI::UInt> &expectedIndices) {
    Logger::get().info("============Checking indices=============");
    auto actualIndices = getGAPI().getBufferDataUI(bufferID);
    EXPECT_EQ(expectedIndices.size(), actualIndices.size());
    for (size_t i = 0; i < expectedIndices.size(); ++i) {
        printExpectNear("index", expectedIndices[i], actualIndices[i]);
        EXPECT_EQ(expectedIndices[i], actualIndices[i])
                            << "Index data mismatch at index " << i;
    }
}

inline void checkTextureData(GAPI::UInt textureID, const std::vector<GAPI::UByte> &expectedData) {
    Logger::get().info("============Checking texture data=============");
    auto actualData = getGAPI().getTextureData(textureID);
    EXPECT_EQ(expectedData.size(), actualData.size());
    for (size_t i = 0; i < expectedData.size(); ++i) {
        printExpectNear("texture data", expectedData[i], actualData[i]);
        EXPECT_EQ(expectedData[i], actualData[i])
                            << "Texture data mismatch at index " << i;
    }
}