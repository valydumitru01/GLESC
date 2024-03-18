/**************************************************************************************************
 * @file   EngineDebugHUDManager.cpp
 * @author Valentin Dumitru
 * @date   08/03/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024$ Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

#include "engine/subsystems/hud/engine-hud/EngineDebugHUDManager.h"

EngineDebugHUDManager::EngineDebugHUDManager(HUDManager& hudManager) {
    hudManager.addWindow(debugConsoleHud);
    hudManager.addWindow(debugStatsHud);
    hudManager.addWindow(debugEntityDataHud);
}
