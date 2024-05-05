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
#include "engine/ecs/frontend/component/CameraComponent.h"
#include "engine/ecs/frontend/component/PhysicsComponent.h"
#include "engine/ecs/frontend/component/TransformComponent.h"
#include "engine/ecs/frontend/component/InputComponent.h"
#include "engine/ecs/frontend/component/LightComponent.h"
#include "engine/ecs/frontend/component/SunComponent.h"
#include "engine/subsystems/renderer/mesh/MeshFactory.h"
#include "game/TerrainGenerator.h"


using namespace GLESC;
static std::vector<ECS::Entity> entities;


void generateEntitiesForMap(ECS::EntityFactory& entityFactory) {
    TerrainGenerator terrainGenerator;
    auto map = terrainGenerator.generateMap();

    std::vector<Vec2I> keys;
    std::vector<ECS::Entity> entities;
    keys.reserve(map.size());
    for (const auto& item : map) {
        keys.push_back(item.first);
        entities.push_back(entityFactory.createEntity("chunk" + item.first.toString()));
    }

#pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < keys.size(); ++i) {
        auto& chunkPosition = keys[i];
        auto& chunk = map[chunkPosition];
        Render::ColorMesh chunkMesh = MeshTerrain::generateChunkMeshFromMap(chunk, chunkPosition, map);
        ECS::Entity entity = entities.at(i);
        entity.addComponent(ECS::TransformComponent())
              .addComponent(ECS::RenderComponent());
        entity.getComponent<ECS::TransformComponent>().transform.setPosition({
            chunkPosition.getX() * CHUNK_SIZE, 0, chunkPosition.getY() * CHUNK_SIZE
        });
        entity.getComponent<ECS::RenderComponent>().mesh = chunkMesh;


        std::cout << "Created entity for chunk at position " << chunkPosition.toString() << std::endl;
    }
}

void Game::init() {
    ECS::Entity sun = entityFactory.createEntity("sun")
                                   .addComponent(ECS::TransformComponent())
                                   .addComponent(ECS::SunComponent());
    sun.getComponent<ECS::TransformComponent>().transform.setPosition(
        Transform::Position(0, 10, 0));

    int numOfEntities = 20;
    for (int i = 0; i < numOfEntities; i++) {
        ECS::Entity entity = entityFactory.createEntity("entity" + std::to_string(i))
                                          .addComponent(ECS::TransformComponent())
                                          .addComponent(ECS::RenderComponent());
        float increment = Math::clamp(0.1f * static_cast<float>(i), 0.0f, 1.0f);
        Transform::Position position = Transform::Position(i * 3, 0, 0);

        // Setting position
        entity.getComponent<ECS::TransformComponent>().transform.setPosition(position);

        // Setting scale
        entity.getComponent<ECS::TransformComponent>().transform.setScale(
            Transform::Scale(1 + i * 0.1, 1 + i * 0.1, 1 + i * 0.1));

        // Choosing a color
        Render::ColorRgba color = Render::ColorRgba(increment * 255, 255 - 255 * increment, 255 - 255 * increment,
                                                    255);


        // Setting mesh, cube, sphere, pyramid, in this order
        if (i % 3 == 0)
            entity.getComponent<ECS::RenderComponent>().mesh =
                Render::MeshFactory::cube(color);
        else if (i % 3 == 1)
            entity.getComponent<ECS::RenderComponent>().mesh =
                Render::MeshFactory::sphere(4 + i, 4 + i, color);
        else
            entity.getComponent<ECS::RenderComponent>().mesh =
                Render::MeshFactory::cube(color);

        // Put a light every 3 entities
        if (i % 3 == 0) {
            ECS::Entity light = entityFactory.createEntity("light" + std::to_string(i))
                                             .addComponent(ECS::TransformComponent())
                                             .addComponent(ECS::LightComponent());
            light.getComponent<ECS::TransformComponent>().transform.setPosition(
                Transform::Position(position + Transform::Position(0, 0, 1 + increment)));
        }


        // Setting material
        entity.getComponent<ECS::RenderComponent>().material.setShininess(increment);
        entity.getComponent<ECS::RenderComponent>().material.setSpecularColor(
            Render::ColorRgb(increment * 255, increment * 255, increment * 255));


        entities.push_back(entity);
    }

    generateEntitiesForMap(entityFactory);
}

void Game::update() {
    for (auto& entity : entities) {
        auto& transform = entity.getComponent<ECS::TransformComponent>().transform;
        transform.addRotation(Transform::Rotation(0.01, 0.01, 0.1));
    }
}
