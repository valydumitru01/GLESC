/**************************************************************************************************
 * @file   TerrainGeneratorGame.h
 * @author Valentin Dumitru
 * @date   13/05/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "TerrainGenerator.h"
#include "engine/ecs/frontend/component/RenderComponent.h"
#include "engine/ecs/frontend/component/TransformComponent.h"
#include "engine/ecs/frontend/entity/EntityFactory.h"
#include "engine/scene/Scene.h"
#include "engine/scene/SceneManager.h"

class TerrainGeneratorGame : public GLESC::Scene::Scene{
public:
    TerrainGeneratorGame(GLESC::WindowManager& windowManager,
                         GLESC::ECS::EntityFactory& entityFactory,
                         GLESC::Scene::SceneManager& sceneManager) : Scene(windowManager, entityFactory, sceneManager) {
    }

    void generateEntitiesForMap(GLESC::ECS::EntityFactory& entityFactory);

    void init() override;

    void update() override;

    void destroy() override;

    static const std::string getSceneName() { return "terrain-generator"; }

private:
}; // class TerrainGeneratorGame
