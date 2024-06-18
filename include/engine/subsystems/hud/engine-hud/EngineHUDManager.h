/**************************************************************************************************
 * @file   EngineHUDManager.h
 * @author Valentin Dumitru
 * @date   08/03/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "DebugItemsHUD.h"
#include "EntityListHUD.h"
#include "engine/subsystems/hud/HUDManager.h"

#include "engine/subsystems/hud/engine-hud/DebugEntityDataHUD.h"
#include "engine/subsystems/hud/engine-hud/DebugConsoleHUD.h"
#include "engine/subsystems/hud/engine-hud/DebugStatsHUD.h"
#include "engine/subsystems/hud/engine-hud/CrosshairHUD.h"
#include "engine/subsystems/renderer/Renderer.h"
#include "engine/subsystems/renderer/texture/TextureFactory.h"

namespace GLESC::HUD {
    class EngineHUDManager {
    public:
        explicit EngineHUDManager(HUDManager& hudManager, Render::Renderer& renderer,
                                       TextureFactory& textureManager);

        DebugStatsHUD& getDebugStats() { return debugStatsHud; }
        CrosshairHUD& getCrosshair() { return crosshairHud; }
#ifndef NDEBUG_GLESC
        DebugConsoleHUD& getConsole() { return debugConsoleHud; }
        DebugEntityData& getEntityData() { return debugEntityDataHud; }
#endif


        void toggle();

    private:
        DebugStatsHUD debugStatsHud;
        CrosshairHUD crosshairHud;
#ifndef NDEBUG_GLESC
        DebugConsoleHUD debugConsoleHud;
        DebugEntityData debugEntityDataHud;
        DebugItems debugItemHud;
        EntityListHUD entityListHud;
#endif
    }; // class EngineHUDManager
} // namespace GLESC::HUD
