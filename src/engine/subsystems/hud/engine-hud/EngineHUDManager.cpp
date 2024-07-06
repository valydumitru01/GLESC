
#include "engine/subsystems/hud/engine-hud/EngineHUDManager.h"

using namespace GLESC::HUD;

EngineHUDManager::EngineHUDManager(HUDManager& hudManager, Render::Renderer& renderer,
                                   TextureFactory& textureManager) :
#ifndef NDEBUG_GLESC
    debugConsoleHud(), debugEntityDataHud(),
    debugItemHud(renderer, textureManager),
#endif
    debugStatsHud(),
    crosshairHud() {
    hudManager.addWindow(crosshairHud);
    hudManager.addWindow(debugStatsHud);
#ifndef NDEBUG_GLESC
    hudManager.addWindow(debugConsoleHud);
    hudManager.addWindow(debugEntityDataHud);
    hudManager.addWindow(entityListHud);
    hudManager.addWindow(debugItemHud);
#endif
}

void EngineHUDManager::toggle() {
    debugStatsHud.toggleVisibility();
#ifndef NDEBUG_GLESC
    debugConsoleHud.toggleVisibility();
    debugEntityDataHud.toggleVisibility();
    debugItemHud.toggleVisibility();
    entityListHud.toggleVisibility();
#endif
}
