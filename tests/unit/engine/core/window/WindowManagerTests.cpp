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
    auto [width, height] = windowManager.getWindowSize();
    EXPECT_EQ_CUSTOM(width, 800);
    EXPECT_EQ_CUSTOM(height, 600);
    
    // Checking the viewport has changed
    auto [vpX, vpY, vpWidth, vpHeight] = gapi.getViewport();
    EXPECT_EQ_CUSTOM(vpWidth, 800);
    EXPECT_EQ_CUSTOM(vpHeight, 600);
    
    windowManager.setSize(200, 200);
    std::tie(width, height) = windowManager.getWindowSize();
    EXPECT_EQ_CUSTOM(width, 200);
    EXPECT_EQ_CUSTOM(height, 200);
    
    // Checking the viewport has changed
    std::tie(vpX, vpY, vpWidth, vpHeight) = gapi.getViewport();
    EXPECT_EQ_CUSTOM(vpWidth, 200);
    EXPECT_EQ_CUSTOM(vpHeight, 200);
    
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