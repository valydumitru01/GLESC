/**************************************************************************************************
 * @file   WindowManagerTests.cpp
 * @author Valentin Dumitru
 * @date   2023-11-09
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/


#include <gtest/gtest.h>
#include <engine/core/low-level-renderer/graphic-api/GapiStructs.h>
#include <engine/core/low-level-renderer/graphic-api/Gapi.h>
#include "engine/core/window/WindowManager.h"
#include "../math/MathTestHelper.h"

class WindowManagerTest : public ::testing::Test {
protected:
    GLESC::WindowManager windowManager;
    
    void SetUp() override {
        windowManager.setFullscreen(false);
        windowManager.setMouseRelative(false);
        windowManager.setPosition(0,0);
        windowManager.setResizable(true);
        windowManager.setSize(200, 200);
    }
    
    void TearDown() override {
        windowManager.destroyWindow();
    }
};

TEST_F(WindowManagerTest, Size) {
    windowManager.setResizable(true);
    windowManager.setSize(800, 600);
    GAPI::Viewport vp;
    GLESC::WindowDimensions windowDimensions;
    windowDimensions= windowManager.getWindowSize();
    EXPECT_EQ_CUSTOM(windowDimensions.width, 800);
    EXPECT_EQ_CUSTOM(windowDimensions.height, 600);
    
    // Checking the viewport has changed
    vp = gapi.getViewport();
    EXPECT_EQ_CUSTOM(vp.width, 800);
    EXPECT_EQ_CUSTOM(vp.height, 600);
    
    windowManager.setSize(200, 200);
    windowDimensions = windowManager.getWindowSize();
    EXPECT_EQ_CUSTOM(windowDimensions.width, 200);
    EXPECT_EQ_CUSTOM(windowDimensions.height, 200);
    
    // Checking the viewport has changed
    vp = gapi.getViewport();
    EXPECT_EQ_CUSTOM(vp.width, 200);
    EXPECT_EQ_CUSTOM(vp.height, 200);
    
}

TEST_F(WindowManagerTest, Position) {
    windowManager.setResizable(true);
    windowManager.setPosition(100, 100);
    auto vec = windowManager.getPosition();
    EXPECT_EQ_CUSTOM(vec.x(), 100);
    EXPECT_EQ_CUSTOM(vec.y(), 100);
    
    windowManager.setPosition(0, 0);
    vec = windowManager.getPosition();
    EXPECT_EQ_CUSTOM(vec.x(), 0);
    EXPECT_EQ_CUSTOM(vec.y(), 0);
}

TEST_F(WindowManagerTest, Fullscreen) {
    windowManager.setFullscreen(true);
    EXPECT_TRUE(windowManager.isFullscreen());
    
    windowManager.setFullscreen(false);
    EXPECT_FALSE(windowManager.isFullscreen());
}

TEST_F(WindowManagerTest, MouseRelativeMode) {
    windowManager.setMouseRelative(true);
    EXPECT_TRUE(windowManager.getMouseRelative());
    
    windowManager.setMouseRelative(false);
    EXPECT_FALSE(windowManager.getMouseRelative());
}

TEST_F(WindowManagerTest, Borderless) {
    windowManager.setBorderlessWindow(true);
    EXPECT_TRUE(windowManager.isBorderlessWindow());
    
    windowManager.setBorderlessWindow(false);
    EXPECT_FALSE(windowManager.isBorderlessWindow());
}

TEST_F(WindowManagerTest, FullscreenBorderless){
    windowManager.setFullscreenBorderless(true);
    EXPECT_TRUE(windowManager.isFullscreenBorderless());
    
    windowManager.setFullscreenBorderless(false);
    EXPECT_FALSE(windowManager.isFullscreenBorderless());
}

TEST_F(WindowManagerTest, Resizable){
    windowManager.setResizable(true);
    EXPECT_TRUE(windowManager.isResizable());
    
    windowManager.setResizable(false);
    EXPECT_FALSE(windowManager.isResizable());
}