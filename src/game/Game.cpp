
// Components
#include "game/Game.h"

#include "engine/scene/engine-scenes/Default.h"
#include "game/scenes/shoot-chicken/ShootTheChickenGame.h"
#include "game/scenes/terrain/TerrainGeneratorGame.h"


using namespace GLESC;

void Game::init() {
    registerScene<Default>(Default::getSceneName());
    registerScene<TerrainGeneratorGame>(TerrainGeneratorGame::getSceneName());
    registerScene<ShootTheChickenGame>(ShootTheChickenGame::getSceneName());
    sceneManager.switchScene(ShootTheChickenGame::getSceneName());
}

void Game::update() {
    // Is necessary to call the init after letting a full frame pass
    // This is because it creates entities and entities are not destroyed until the end of the frame
    // I.e. there is an entity player in the old scene and the new scene, calling destroy and init consecutively
    // will result in a crash due to entity repetition
    if (sceneManager.isChangingScene()) {
        // We need this check because if we're chaging scenes, the init of the next scene will be called first
        // and we want the destroy of the old to be called first
        if (sceneManager.hasOldSceneBeenDestroyed() || sceneManager.getOldScene() == -1){
            sceneContainer.getScene(sceneManager.getCurrentScene()).init();
            sceneManager.finishSwitchingScene();
        }
    }
    if (sceneManager.getCurrentScene() != -1) {
        sceneContainer.getScene(sceneManager.getCurrentScene()).update();
    }
    if (sceneManager.isChangingScene()) {
        if (sceneManager.getOldScene() != -1) {
            sceneContainer.getScene(sceneManager.getOldScene()).destroy();
            sceneManager.setOldSceneDestroyed(true);
        }
    }
}
