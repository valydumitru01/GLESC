/**************************************************************************************************
 * @file   DebugConsoleHUD.h
 * @author Valentin Dumitru
 * @date   07/03/2024
 * @brief  HUD for the debug console.
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include <imgui/imgui.h>
#include "engine/subsystems/hud/InGameWindow.h"
#ifndef NDEBUG_GLESC
namespace GLESC::HUD {
    /**
     * @brief Class to encapsulate the logic of the debug console HUD.
     * @details The debug console HUD is a window that displays debug information.
     * Allows visualizing the data contained in the debug console.
     */
    class DebugConsoleHUD : public InGameWindow {
    public:
        DebugConsoleHUD();

    private:
        void windowContent(float timeOfFrame) override;
        ImVec4 errorColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
        ImVec4 warningColor = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
        ImVec4 infoColor = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
    }; // class DebugConsoleHUD
} // namespace GLESC::HUD
#endif