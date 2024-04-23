/**************************************************************************************************
 * @file   EngineDebugHUDManager.h
 * @author Valentin Dumitru
 * @date   08/03/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024$ Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "DebugItemsHUD.h"
#include "engine/subsystems/hud/HUDManager.h"

#include "engine/subsystems/hud/engine-hud/DebugEntityDataHUD.h"
#include "engine/subsystems/hud/engine-hud/DebugConsoleHUD.h"
#include "engine/subsystems/hud/engine-hud/DebugStatsHUD.h"
#include "engine/subsystems/hud/engine-hud/CrosshairHUD.h"

namespace GLESC::HUD {
    class EngineDebugHUDManager {
    public:
        explicit EngineDebugHUDManager(HUDManager& hudManager, Render::Renderer& renderer,
                                       TextureFactory& textureManager);

        DebugConsoleHUD& getConsole() { return debugConsoleHud; }
        DebugStatsHUD& getDebugStats() { return debugStatsHud; }
        DebugEntityData& getEntityData() { return debugEntityDataHud; }
        CrosshairHUD& getCrosshair() { return crosshairHud; }

    private:
        DebugConsoleHUD debugConsoleHud;
        DebugStatsHUD debugStatsHud;
        DebugEntityData debugEntityDataHud;
        CrosshairHUD crosshairHud;
        DebugItems debugItemHud;
    }; // class EngineDebugHUDManager
} // namespace GLESC::HUD
