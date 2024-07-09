
#include "game/scenes/terrain/TerrainGeneratorGame.h"

#include "engine/ecs/frontend/component/FogComponent.h"
#include "engine/ecs/frontend/component/SunComponent.h"

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
    getEntity("fog").getComponent<GLESC::ECS::FogComponent>().fog.setDensity(0.2);
    getEntity("fog").getComponent<GLESC::ECS::FogComponent>().fog.setColor({200, 200, 170});
    getEntity("fog").getComponent<GLESC::ECS::FogComponent>().fog.setEnd(60);
    getEntity("sun").getComponent<GLESC::ECS::SunComponent>().sun.setIntensity(0.4f);
    getEntity("sun").getComponent<GLESC::ECS::SunComponent>().sun.setColor({255, 255, 200});
    getEntity("sun").getComponent<GLESC::ECS::SunComponent>().sun.setDirection({-0.5, -1, -0.5});
    getEntity("sun").getComponent<GLESC::ECS::SunComponent>().globalAmbientLight.setIntensity(0.5);
    getEntity("sun").getComponent<GLESC::ECS::SunComponent>().globalAmbientLight.setColor({255, 180, 165});
    generateEntitiesForMap(entityFactory);
}

void TerrainGeneratorGame::update() {
}
