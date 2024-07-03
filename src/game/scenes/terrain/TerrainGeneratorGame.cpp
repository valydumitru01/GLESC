/**************************************************************************************************
 * @file   TerrainGeneratorGame.cpp
 * @author Valentin Dumitru
 * @date   13/05/2024
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

#include "game/scenes/terrain/TerrainGeneratorGame.h"

void TerrainGeneratorGame::generateEntitiesForMap(GLESC::ECS::EntityFactory& entityFactory) {
    TerrainGenerator terrainGenerator;
    auto map = terrainGenerator.generateMap();

    std::vector<Vec2I> keys;
    keys.reserve(map.size());
    for (const auto& item : map) {
        keys.push_back(item.first);
        createEntity("chunk", {GLESC::EntityType::Instance});
    }

#pragma omp parallel for schedule(static, 1) default(none) shared(keys, map, std::cout)
    for (int i = 0; i < keys.size(); ++i) {
        auto& chunkPosition = keys[i];
        auto& chunk = map[chunkPosition];
        GLESC::Render::ColorMesh chunkMesh = MeshTerrain::generateChunkMeshFromMap(chunk, chunkPosition, map);
        GLESC::ECS::EntityID entityID = getSceneEntities().at(i);
        GLESC::ECS::Entity entity = getEntity(entityID);
        entity.addComponent<GLESC::ECS::TransformComponent>()
              .addComponent<GLESC::ECS::RenderComponent>();
        entity.getComponent<GLESC::ECS::TransformComponent>().transform.setPosition({
            chunkPosition.getX() * CHUNK_SIZE, 0, chunkPosition.getY() * CHUNK_SIZE
        });
        entity.getComponent<GLESC::ECS::RenderComponent>().moveMesh(chunkMesh);


        std::cout << "Created entity for chunk at position " << chunkPosition.toString() << std::endl;
    }
}


void TerrainGeneratorGame::init() {
    getCamera().setForce(5);
    generateEntitiesForMap(entityFactory);
}

void TerrainGeneratorGame::update() {
}
