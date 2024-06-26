/**************************************************************************************************
 * @file   TerrainGeneratorGame.h
 * @author Valentin Dumitru
 * @date   13/05/2024
 * @brief  @TODO Add description of this file if needed
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

class TerrainGeneratorGame : public GLESC::Scene::Scene {
public:
    SCENE_DEFINITION(TerrainGeneratorGame)
    void generateEntitiesForMap(GLESC::ECS::EntityFactory& entityFactory);
    void init() override;
    void update() override;
}; // class TerrainGeneratorGame
