/**************************************************************************************************
 * @file   CrosshairHUD.h
 * @author Valentin Dumitru
 * @date   2024-04-13
 * @brief HUD for the crosshair.
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "engine/subsystems/hud/InGameWindow.h"
#include "engine/subsystems/renderer/RendererTypes.h"

namespace GLESC::HUD {
    /**
     * @brief Class to encapsulate the logic of the crosshair HUD.
     * @details The crosshair HUD is a simple crosshair that is displayed in the center of the screen.
     */
    class CrosshairHUD : public GLESC::InGameWindow {
    public:
        CrosshairHUD();

    private:
        float linesLength = 10.0f;
        GLESC::Render::ColorRgba linesColor = GLESC::Render::ColorRgba(255, 255, 255, 255);
        void windowContent(float timeOfFrame) override;
    }; // class Crosshair
} // namespace GLESC::HUD
