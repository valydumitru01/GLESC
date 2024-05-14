/******************************************************************************
 * @file   Game.cpp
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include <omp.h>

// Components
#include "game/Game.h"

#include "engine/ecs/frontend/component/RenderComponent.h"
#include "game/scenes/shoot-chicken/ShootTheChickenGame.h"
#include "game/scenes/terrain/TerrainGeneratorGame.h"


using namespace GLESC;

void Game::init() {
    sceneManager.registerScene<ShootTheChickenGame>(ShootTheChickenGame::getSceneName());
    sceneManager.registerScene<TerrainGeneratorGame>(TerrainGeneratorGame::getSceneName());
    sceneManager.switchScene(ShootTheChickenGame::getSceneName());
}

void Game::update() {

}
