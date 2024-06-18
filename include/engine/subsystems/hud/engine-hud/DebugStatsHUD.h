/**************************************************************************************************
 * @file   DebugStatsHUD.h
 * @author Valentin Dumitru
 * @date   07/03/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include <imgui/imgui.h>
#include "engine/subsystems/hud/InGameWindow.h"

namespace GLESC::HUD {
    class DebugStatsHUD : public InGameWindow {
    public:
        DebugStatsHUD();

    private:
        void windowContent(float timeOfFrame) override;
        ImVec4 statsTextColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    }; // class EngineDataInterface
} // namespace GLESC::HUD