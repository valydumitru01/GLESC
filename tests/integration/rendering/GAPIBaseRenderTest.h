/**************************************************************************************************
 * @file   GAPIHelloTriangleRenderTest.h
 * @author Valentin Dumitru
 * @date   2023-11-20
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

#include <gtest/gtest.h>
#include "engine/core/low-level-renderer/graphic-api/Gapi.h"
#include "engine/core/window/WindowManager.h"
#include "integration/rendering/IBaseRenderTest.h"

class GAPIBaseRenderTest : public IBaseRenderTest {
public:
    GLESC::WindowManager windowManager;
    Vec2I backgroundPixelCoordinates;
    Vec2I trianglePixelCoordinates;
    
    GAPIBaseRenderTest() : windowManager(),
            backgroundPixelCoordinates(0, 0),
            trianglePixelCoordinates(windowManager.getWindowSize().width / 2,
                                     windowManager.getWindowSize().height / 2) {
    }
    
    virtual void prepareShaders() = 0;
    
    virtual void prepareBuffers() = 0;
    
    virtual void destroyRender() = 0;
    
    virtual void render() = 0;
    
    void checkBackgroundColor() {
        Logger::get().info("============Checking Background=============");
        GAPI::RGBColorNormalized
                color = gapi.readPixelColorNormalized(backgroundPixelCoordinates.x(),
                                                      backgroundPixelCoordinates.y());
        EXPECT_NEAR(backgroundColor.r, color.r, colorEpsilon);
        printExpectNear("color red", backgroundColor.r, color.r);
        EXPECT_NEAR(backgroundColor.g, color.g, colorEpsilon);
        printExpectNear("color green", backgroundColor.g, color.g);
        EXPECT_NEAR(backgroundColor.b, color.b, colorEpsilon);
        printExpectNear("color blue", backgroundColor.b, color.b);
        EXPECT_NEAR(backgroundColor.a, color.a, colorEpsilon);
        printExpectNear("color alpha", backgroundColor.a, color.a);
    }
    
    void checkTriangleColor() {
        Logger::get().info("============Checking Triangle color=============");
        GAPI::RGBColorNormalized readTriangleColor =
                gapi.readPixelColorNormalized(trianglePixelCoordinates.x(),
                                              trianglePixelCoordinates.y());
        EXPECT_NEAR(expectedTriangleColor.r, readTriangleColor.r, colorEpsilon);
        printExpectNear("color red", expectedTriangleColor.r, readTriangleColor.r);
        EXPECT_NEAR(expectedTriangleColor.g, readTriangleColor.g, colorEpsilon);
        printExpectNear("color green", expectedTriangleColor.g, readTriangleColor.g);
        EXPECT_NEAR(expectedTriangleColor.b, readTriangleColor.b, colorEpsilon);
        printExpectNear("color blue", expectedTriangleColor.b, readTriangleColor.b);
        EXPECT_NEAR(expectedTriangleColor.a, readTriangleColor.a, colorEpsilon);
        printExpectNear("color alpha", expectedTriangleColor.a, readTriangleColor.a);
    }
    
    void printExpectNear(const std::string &message, float expected, float actual) {
        Logger::get().info("\tChecking " + message + ": expected[ "
                           + std::to_string(expected) + " ] == read[ " +
                           std::to_string(actual) + " ]");
    }
    
    template<GAPI::BufferTypes type>
    void checkBufferData(GAPI::UInt buffer) {
        gapi.bindBuffer(type, buffer);
        
        if constexpr (type == GAPI::BufferTypes::Index) {
            Logger::get().info("============Checking indices=============");
            auto actualIndices = gapi.getBufferDataUI(buffer);
            EXPECT_EQ(actualIndices.size(), indices.size());
            for (size_t i = 0; i < actualIndices.size(); ++i) {
                printExpectNear("index", actualIndices[i], indices[i]);
                EXPECT_EQ(actualIndices[i], indices[i])
                                    << "Index data mismatch at index " << i;
            }
        } else if constexpr (type == GAPI::BufferTypes::Vertex) {
            Logger::get().info("============Checking vertices=============");
            auto actualVertices = gapi.getBufferDataF(buffer);
            EXPECT_EQ(actualVertices.size(), vertices.size());
            for (size_t i = 0; i < actualVertices.size(); ++i) {
                printExpectNear("vertex", actualVertices[i], vertices[i]);
                EXPECT_NEAR(actualVertices[i], vertices[i], dataEpsilon)
                                    << "Vertex data mismatch at index " << i;
            }
        }
    }


protected:

private:

}; // class GAPIHelloTriangleRenderTest