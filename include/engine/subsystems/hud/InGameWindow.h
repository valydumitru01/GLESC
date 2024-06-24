/**************************************************************************************************
 * @file   InGameWindow.h
 * @author Valentin Dumitru
 * @date   07/03/2024
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include <imgui/imgui.h>
#include <string>
#include <vector>


namespace GLESC {
    enum class LayoutPos {
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

    /**
     * @brief Class to encapsulate the logic of an in-game window.
     * @details This class must be inherited by any class that wants to create a window in the game.
     * Allows setting the position, size, and layout of the window.
     */
    class InGameWindow {
    public:
        InGameWindow();
        virtual ~InGameWindow() = default;
        /**
         * @brief Set the max size of the window
         * @details If the window gets bigger this value, it will be clamped to this size
         */
        void setMaxSize(ImVec2 size);
        /**
         * @brief Set the min size of the window
         * @details If the window gets smaller this value, it will be clamped to this size
         */
        void setMinSize(ImVec2 size);
        /**
         * @brief Set the size of the window as a fraction of the screen size
         * @details The fraction is clamped between 0.0f and 1.0f
         */
        void setSizeFraction(ImVec2 fraction);
        /**
         * @brief Set the position of the window as a fraction of the screen size.
         * @details The fraction is clamped between 0.0f and 1.0f. The center of the window is set by the set center
         * function. The position will modify that center.
         */
        void setPositionFraction(ImVec2 fraction);
        /**
         * @brief Set the center of the window
         * @details The center is used to calculate the position of the window.
         */
        void setCenter(WindowCenter center);
        /**
         * @brief Set the layout position of the window
         * @details The layout position is used to calculate the position of the window.
         */
        void setLayoutPosition(LayoutPos position);

        const std::string& getTitle() const { return title; }


        void addFlag(ImGuiWindowFlags_ flag) {
            windowFlags.push_back(flag);
            windowFlagsCached = false;
        }

        [[nodiscard]] bool isVisibile() const { return isVisible; }
        void setVisible(bool visible) { isVisible = visible; }
        void toggleVisibility() { isVisible = !isVisible; }

        /**
         * @brief Update the window position and size
         * @details Updates the windows positions given it's layout configuration and the current window size
         */
        void update();
        /**
         * @brief Render the window
         * @details The time of frame is needed to interpolate hud items and allow for smooth rendering
         * @param timeOfFrame The time of the current frame
         */
        void render(float timeOfFrame);

    protected:
        void setTitle(const std::string& title);
        virtual void windowContent(float timeOfFrame) = 0;
        [[nodiscard]] ImVec2 calculateSize() const;
        [[nodiscard]] ImVec2 calculatePosition(ImVec2 windowSize) const;
        [[nodiscard]] ImGuiWindowFlags getFlags();
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
        ImGuiWindowFlags cachedFlags = 0;
        mutable bool windowFlagsCached = false;
    }; // class Window
} // namespace GLESC
