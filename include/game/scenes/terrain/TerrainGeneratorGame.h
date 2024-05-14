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

    static void generateEntitiesForMap(GLESC::ECS::EntityFactory& entityFactory) {
        TerrainGenerator terrainGenerator;
        auto map = terrainGenerator.generateMap();

        std::vector<Vec2I> keys;
        std::vector<GLESC::ECS::Entity> entities;
        keys.reserve(map.size());
        for (const auto& item : map) {
            keys.push_back(item.first);
            entities.push_back(entityFactory.createEntity("chunk" + item.first.toString()));
        }

#pragma omp parallel for schedule(static, 1)
        for (int i = 0; i < keys.size(); ++i) {
            auto& chunkPosition = keys[i];
            auto& chunk = map[chunkPosition];
            GLESC::Render::ColorMesh chunkMesh = MeshTerrain::generateChunkMeshFromMap(chunk, chunkPosition, map);
            GLESC::ECS::Entity entity = entities.at(i);
            entity.addComponent(GLESC::ECS::TransformComponent())
                  .addComponent(GLESC::ECS::RenderComponent());
            entity.getComponent<GLESC::ECS::TransformComponent>().transform.setPosition({
                chunkPosition.getX() * CHUNK_SIZE, 0, chunkPosition.getY() * CHUNK_SIZE
            });
            entity.getComponent<GLESC::ECS::RenderComponent>().mesh = chunkMesh;


            std::cout << "Created entity for chunk at position " << chunkPosition.toString() << std::endl;
        }
    }

    void init() override {
        generateEntitiesForMap(entityFactory);
    }

    void update() override {
    }

    void destroy() override {
    }

    static const std::string getSceneName() { return "terrain-generator"; }

private:
}; // class TerrainGeneratorGame
