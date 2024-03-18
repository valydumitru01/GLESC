/**************************************************************************************************
 * @file   InGameWindow.h
 * @author Valentin Dumitru
 * @date   07/03/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024$ Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include <imgui/imgui.h>

#include "engine/core/math/Math.h"

enum class LayoutPosition {
    TopLeft,
    CenterLeft,
    BottomLeft,
    TopCenter,
    Center,
    BottomCenter,
    TopRight,
    CenterRight,
    BottomRight,
    Custom
};

enum class WindowCenter {
    TopLeft,
    CenterLeft,
    BottomLeft,
    TopCenter,
    Center,
    BottomCenter,
    TopRight,
    CenterRight,
    BottomRight
};

namespace GLESC {
    class InGameWindow {
    public:
        InGameWindow();
        virtual ~InGameWindow() = default;

        void setTitle(const std::string& title);
        void setMaxSize(ImVec2 size);
        void setMinSize(ImVec2 size);
        void setSizeFraction(ImVec2 fraction);
        void setPositionFraction(ImVec2 fraction);
        void setCenter(WindowCenter center);


        void addFlag(ImGuiWindowFlags_ flag) { windowFlags.push_back(flag); }
        bool isVisibile() { return isVisible; }
        void toggleVisibility() { isVisible = !isVisible; }

        void update();
        void setLayoutPosition(LayoutPosition position);

    protected:
        virtual void windowContent() = 0;
        ImVec2 calculateSize();
        ImVec2 calculatePosition(ImVec2 windowSize);
        ImGuiWindowFlags getFlags();
        bool isVisible = true;

    private:
        ImVec2 maxSize = ImVec2(999999, 999999);
        ImVec2 minSize = ImVec2(0, 0);
        ImVec2 sizeFraction = ImVec2(0.5f, 0.5f);
        ImVec2 positionFraction = ImVec2(0.5f, 0.5f);
        ImVec2 center = ImVec2(0.5f, 0.5f);
        float windowMarginFraction{0.02f};


        std::string title = "Window";
        ImVec2 size;
        ImVec2 position;
        std::vector<ImGuiWindowFlags_> windowFlags;
    }; // class Window
} // namespace GLESC
