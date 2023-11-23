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
        RGBColorNormalized color = gapi.readPixelColorNormalized(backgroundPixelCoordinates.x(),
                                                                 backgroundPixelCoordinates.y());
        ASSERT_NEAR(backgroundColor.r, color.r, colorEpsilon);
        ASSERT_NEAR(backgroundColor.g, color.g, colorEpsilon);
        ASSERT_NEAR(backgroundColor.b, color.b, colorEpsilon);
        ASSERT_NEAR(backgroundColor.a, color.a, colorEpsilon);
    }
    
    void checkTriangleColor() {
        RGBColorNormalized color = gapi.readPixelColorNormalized(trianglePixelCoordinates.x(),
                                                                 trianglePixelCoordinates.y());
        ASSERT_NEAR(figureColor.r, color.r, colorEpsilon);
        ASSERT_NEAR(figureColor.g, color.g, colorEpsilon);
        ASSERT_NEAR(figureColor.b, color.b, colorEpsilon);
        ASSERT_NEAR(figureColor.a, color.a, colorEpsilon);
    }
    
    void checkBufferData(GAPIuint VBO){
        std::vector<float> actualVertices = gapi.getBufferDataF(VBO);
        ASSERT_EQ(actualVertices.size(), vertices.size());
        for (size_t i = 0; i < actualVertices.size(); ++i) {
            std::cout<< "Vertex data " << i << ": " << actualVertices[i] << "\n";
            EXPECT_NEAR(actualVertices[i], vertices[i], dataEpsilon)
                                << "Vertex data mismatch at index " << i;
        }
    }


protected:

private:

}; // class GAPIHelloTriangleRenderTest