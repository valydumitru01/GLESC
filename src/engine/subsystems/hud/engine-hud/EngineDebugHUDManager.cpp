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

using namespace GLESC::HUD;

EngineDebugHUDManager::EngineDebugHUDManager(HUDManager& hudManager, Render::Renderer& renderer,
                                             TextureFactory& textureManager) :
    debugConsoleHud(), debugStatsHud(), debugEntityDataHud(), crosshairHud(),
    debugItemHud(renderer, textureManager) {
    hudManager.addWindow(debugConsoleHud);
    hudManager.addWindow(debugStatsHud);
    hudManager.addWindow(debugEntityDataHud);
    hudManager.addWindow(crosshairHud);
    hudManager.addWindow(entityListHud);
    hudManager.addWindow(debugItemHud);
}
