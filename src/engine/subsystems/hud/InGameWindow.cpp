/**************************************************************************************************
 * @file   InGameWindow.cpp
 * @author Valentin Dumitru
 * @date   08/03/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/


#include "engine/subsystems/hud/InGameWindow.h"
#include "engine/core/asserts/Asserts.h"
#include "engine/subsystems/ingame-debug/Console.h"
using namespace GLESC;

InGameWindow::InGameWindow() : isVisible(false) {
}

void InGameWindow::setTitle(const std::string& title) {
    D_ASSERT_FALSE(title.empty(), "Title cannot be empty");
    D_ASSERT_FALSE(title.size() > 100, "Title is too long");
    this->title = title;
}

void InGameWindow::setMinSize(ImVec2 minSize) {
    D_ASSERT_TRUE(minSize.x >= 0.0f && minSize.y >= 0.0f, "Invalid min size");
    this->minSize = minSize;
}

void InGameWindow::setMaxSize(ImVec2 maxSize) {
    D_ASSERT_TRUE(maxSize.x >= 0.0f && maxSize.y >= 0.0f, "Invalid max size");
    this->maxSize = maxSize;
}

void InGameWindow::setSizeFraction(ImVec2 fraction) {
    D_ASSERT_TRUE(fraction.x >= 0.0f && fraction.x <= 1.0f, "Invalid fraction x");
    D_ASSERT_TRUE(fraction.y >= 0.0f && fraction.y <= 1.0f, "Invalid fraction y");
    // We need the min between 1.0f - margin and fraction to avoid the window going off margins
    sizeFraction.x = std::min(fraction.x, 1.0f - windowMarginFraction * 2);
    sizeFraction.y = std::min(fraction.y, 1.0f - windowMarginFraction * 2);
}

void InGameWindow::setPositionFraction(ImVec2 fraction) {
    D_ASSERT_TRUE(fraction.x >= 0.0f && fraction.x <= 1.0f, "Invalid fraction x");
    D_ASSERT_TRUE(fraction.y >= 0.0f && fraction.y <= 1.0f, "Invalid fraction y");
    positionFraction = fraction;
}

void InGameWindow::setCenter(WindowCenter center) {
    if (center == WindowCenter::TopLeft) {
        this->center = ImVec2(0.0f, 0.0f);
    }
    else if (center == WindowCenter::CenterLeft) {
        this->center = ImVec2(0.0f, 0.5f);
    }
    else if (center == WindowCenter::BottomLeft) {
        this->center = ImVec2(0.0f, 1.0f);
    }
    else if (center == WindowCenter::TopCenter) {
        this->center = ImVec2(0.5f, 0.0f);
    }
    else if (center == WindowCenter::Center) {
        this->center = ImVec2(0.5f, 0.5f);
    }
    else if (center == WindowCenter::BottomCenter) {
        this->center = ImVec2(0.5f, 1.0f);
    }
    else if (center == WindowCenter::TopRight) {
        this->center = ImVec2(1.0f, 0.0f);
    }
    else if (center == WindowCenter::CenterRight) {
        this->center = ImVec2(1.0f, 0.5f);
    }
    else if (center == WindowCenter::BottomRight) {
        this->center = ImVec2(1.0f, 1.0f);
    }
    else {
        D_ASSERT_TRUE(false, "Invalid center");
    }
}


ImGuiWindowFlags InGameWindow::getFlags() {
    if (!windowFlagsCached) {
        cachedFlags = 0;
        for (auto& flag : windowFlags) {
            cachedFlags |= flag;
        }
        windowFlagsCached = true;
    }
    return cachedFlags;
}

void InGameWindow::setLayoutPosition(LayoutPos position) {
    if (position == LayoutPos::TopLeft) {
        positionFraction.x = windowMarginFraction;
        positionFraction.y = windowMarginFraction;
    }
    else if (position == LayoutPos::TopCenter) {
        positionFraction.x = 0.5f;
        positionFraction.y = windowMarginFraction;
    }
    else if (position == LayoutPos::TopRight) {
        positionFraction.x = 1.0f - windowMarginFraction;
        positionFraction.y = windowMarginFraction;
    }
    else if (position == LayoutPos::BottomLeft) {
        positionFraction.x = windowMarginFraction;
        positionFraction.y = 1.0f - windowMarginFraction;
    }
    else if (position == LayoutPos::BottomCenter) {
        positionFraction.x = 0.5f;
        positionFraction.y = 1.0f - windowMarginFraction;
    }
    else if (position == LayoutPos::BottomRight) {
        positionFraction.x = 1.0f - windowMarginFraction;
        positionFraction.y = 1.0f - windowMarginFraction;
    }
    else if (position == LayoutPos::CenterLeft) {
        positionFraction.x = windowMarginFraction;
        positionFraction.y = 0.5f;
    }
    else if (position == LayoutPos::Center) {
        positionFraction.x = 0.5f;
        positionFraction.y = 0.5f;
    }
    else if (position == LayoutPos::CenterRight) {
        positionFraction.x = 1.0f - windowMarginFraction;
        positionFraction.y = 0.5f;
    }
    else if (position == LayoutPos::Custom) {
        // Do nothing, use the already set position
    }
    else {
        D_ASSERT_TRUE(false, "Invalid layout position");
    }
}


ImVec2 InGameWindow::calculatePosition(ImVec2 windowSize) const {
    float screenWidth = ImGui::GetIO().DisplaySize.x;
    float screenHeight = ImGui::GetIO().DisplaySize.y;

    // Calculate position based on fractions of screen width and height, correctly centering the window
    float posX = (screenWidth * positionFraction.x) - (windowSize.x * center.x);
    float posY = (screenHeight * positionFraction.y) - (windowSize.y * center.y);

    // Ensure the position respects the screen boundaries
    posX = std::max(posX, windowMarginFraction * screenWidth);
    posY = std::max(posY, windowMarginFraction * screenHeight);
    posX = std::min(posX, screenWidth - windowSize.x - windowMarginFraction * screenWidth);
    posY = std::min(posY, screenHeight - windowSize.y - windowMarginFraction * screenHeight);

    return {posX, posY};
}

ImVec2 InGameWindow::calculateSize() const {
    float screenWidth = ImGui::GetIO().DisplaySize.x;
    float screenHeight = ImGui::GetIO().DisplaySize.y;

    // Calculate size based on fractions of screen width and height
    ImVec2 calculatedSize = ImVec2(screenWidth * sizeFraction.x, screenHeight * sizeFraction.y);

    // Apply minimum size constraints
    calculatedSize.x = std::max(calculatedSize.x, minSize.x);
    calculatedSize.y = std::max(calculatedSize.y, minSize.y);

    // Apply maximum size constraints
    calculatedSize.x = std::min(calculatedSize.x, maxSize.x > 0 ? maxSize.x : screenWidth);
    calculatedSize.y = std::min(calculatedSize.y, maxSize.y > 0 ? maxSize.y : screenHeight);

    return calculatedSize;
}

void InGameWindow::render(float timeOfFrame) {
    if (!isVisible) return;
    ImGui::SetNextWindowPos(position, ImGuiCond_Always);
    ImGui::SetNextWindowSize(size, ImGuiCond_Always);

    // Debugging output
    Console::log(title + " window Position: (" + std::to_string(position.x) + ", " + std::to_string(position.y) + ")");
    Console::log(title + " window Size: (" + std::to_string(size.x) + ", " + std::to_string(size.y) + ")");

    if (ImGui::Begin(title.c_str(), &isVisible, getFlags())) {
        windowContent(timeOfFrame);
        ImGui::End();
    }
}


void InGameWindow::update() {
    size = calculateSize();
    position = calculatePosition(size);
}
