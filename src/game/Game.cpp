/******************************************************************************
 * @file   Game.cpp
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

// Components
#include "game/Game.h"

#include "engine/ecs/frontend/component/RenderComponent.h"
#include "engine/scene/engine-scenes/Default.h"
#include "game/scenes/shoot-chicken/ShootTheChickenGame.h"
#include "game/scenes/terrain/TerrainGeneratorGame.h"


using namespace GLESC;

void Game::init() {
    registerScene<Default>(Default::getSceneName());
    registerScene<TerrainGeneratorGame>(TerrainGeneratorGame::getSceneName());
    registerScene<ShootTheChickenGame>(ShootTheChickenGame::getSceneName());
    switchScene(Default::getSceneName());
}

void Game::update() {
    if (sceneManager.getCurrentScene() != -1) {
        sceneContainer.getScene(sceneManager.getCurrentScene()).update();
    }
}
