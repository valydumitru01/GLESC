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
#include "engine/subsystems/hud/HUDManager.h"

#include "engine/subsystems/hud/engine-hud/DebugConsoleHUD.h"
#include "engine/subsystems/hud/engine-hud/DebugEntityDataHUD.h"
#include "engine/subsystems/hud/engine-hud/DebugStatsHUD.h"

class EngineDebugHUDManager {
public:
    explicit EngineDebugHUDManager(HUDManager& hudManager);

    DebugConsoleHUD& getConsole() { return debugConsoleHud; }
    DebugStatsHUD& getDebugStats() { return debugStatsHud; }
    DebugEntityDataHUD& getEntityData() { return debugEntityDataHud; }

private:
    DebugConsoleHUD debugConsoleHud;
    DebugStatsHUD debugStatsHud;
    DebugEntityDataHUD debugEntityDataHud;
}; // class EngineDebugHUDManager
