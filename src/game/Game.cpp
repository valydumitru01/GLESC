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
#include "engine/ecs/frontend/component/CameraComponent.h"
#include "engine/ecs/frontend/component/PhysicsComponent.h"
#include "engine/ecs/frontend/component/TransformComponent.h"
#include "engine/ecs/frontend/component/InputComponent.h"
#include "engine/ecs/frontend/component/LightComponent.h"
#include "engine/ecs/frontend/component/SunComponent.h"
#include "engine/subsystems/renderer/mesh/MeshFactory.h"
#include "game/PerlinNoise.hpp"

using namespace GLESC;
static std::vector<ECS::Entity> entities;

enum class TileType {
    GRASS,
    WATER,
    SAND,
    ROCK
};

// Function to decide tile type based on noise
TileType getTileType(double noiseValue) {
    if (noiseValue < 0.3) {
        return TileType::WATER;
    }
    else if (noiseValue >= 0.3 && noiseValue < 0.5) {
        return TileType::SAND;
    }
    else if (noiseValue >= 0.5 && noiseValue < 0.7) {
        return TileType::GRASS;
    }
    else {
        return TileType::ROCK;
    }
}

struct Tile {
    TileType type;
    int height;
};

#define CHUNK_SIZE 16
#define MAP_SIZE_IN_CHUNKS 1
using Chunk = std::array<std::array<Tile, CHUNK_SIZE>, CHUNK_SIZE>;
using Map = std::unordered_map<Vec2I, Chunk>;
static siv::PerlinNoise noiseGenerator(0); // Initialize PerlinNoise with a seed.

Chunk generateChunk(const Vec2I& chunkPosition) {
    Chunk chunk;
    double frequency = 1.0 / CHUNK_SIZE; // Adjust frequency to control the scale of noise.
    for (int y = 0; y < CHUNK_SIZE; y++) {
        for (int x = 0; x < CHUNK_SIZE; x++) {
            double noiseValue =
                noiseGenerator.octave2D_01(chunkPosition.getX() * CHUNK_SIZE + x,
                                           chunkPosition.getY() * CHUNK_SIZE + y, 8, frequency);
            chunk[y][x] = Tile{getTileType(noiseValue), static_cast<int>(noiseValue*2)};
        }
    }
    return chunk;
}

Map generateMap() {
    Map map;
    for (int y = 0; y < MAP_SIZE_IN_CHUNKS; y++) {
        for (int x = 0; x < MAP_SIZE_IN_CHUNKS; x++) {
            Vec2I chunkPosition(x, y);
            map[chunkPosition] = generateChunk(chunkPosition);
        }
    }
    return map;
}

// Function to get color based on TileType
Render::ColorRgb getColorForTileType(TileType type) {
    switch (type) {
    case TileType::GRASS: return {0.15f, 7.f, 0.1f}; // Green
    case TileType::WATER: return {0.1f, 0.1f, 0.8f}; // Blue
    case TileType::SAND: return {0.76f, 0.7f, 0.5f}; // Sandy
    case TileType::ROCK: return {0.5f, 0.5f, 0.5f}; // Gray
    default: return {1.f, 1.f, 1.f}; // White as default
    }
}

Render::ColorMesh generateChunkMeshFromMap(const Chunk& chunk) {
    Render::ColorMesh mesh;
    int chunkHeight = chunk.size();
    int chunkWidth = chunk[0].size();

    for (int y = 0; y < chunkHeight; y++) {
        for (int x = 0; x < chunkWidth; x++) {
            TileType tileType = chunk[y][x].type;
            int height = chunk[y][x].height;
            Render::ColorRgb color = getColorForTileType(tileType);

            // Position indices of the current voxel
            int posX = x;
            int posY = height;
            int posZ = y;

            // Generate each face only if there is no adjacent block at that face
            // Check top face
            if (y == chunkHeight - 1 || chunk[y + 1][x].height < height) {
                // No block above or block above is lower
                Render::Position p1 = {posX, posY + 1, posZ};
                Render::Position p2 = {posX + 1, posY + 1, posZ};
                Render::Position p3 = {posX + 1, posY + 1, posZ + 1};
                Render::Position p4 = {posX, posY + 1, posZ + 1};
                Render::Normal faceNormal = (p1.normalize() + p2.normalize() + p3.normalize() + p4.normalize()) / 4.0f;
                mesh.addQuad(
                    Render::ColorMesh::Vertex(p4, color, faceNormal),
                    Render::ColorMesh::Vertex(p3, color, faceNormal),
                    Render::ColorMesh::Vertex(p2, color, faceNormal),
                    Render::ColorMesh::Vertex(p1, color, faceNormal)
                );
            }

            // Check bottom face
            if (y == 0 || chunk[y - 1][x].height < height) {
                Render::Position p1 = {posX, posY - 1, posZ};
                Render::Position p2 = {posX + 1, posY - 1, posZ};
                Render::Position p3 = {posX + 1, posY - 1, posZ + 1};
                Render::Position p4 = {posX, posY - 1, posZ + 1};
                Render::Normal faceNormal = (p1.normalize() + p2.normalize() + p3.normalize() + p4.normalize()) / 4.0f;

                // No block below or block below is lower
                mesh.addQuad(
                    Render::ColorMesh::Vertex(p1, color, faceNormal),
                    Render::ColorMesh::Vertex(p2, color, faceNormal),
                    Render::ColorMesh::Vertex(p3, color, faceNormal),
                    Render::ColorMesh::Vertex(p4, color, faceNormal)
                );
            }

            // Similarly add checks and quads for left, right, front, back
            // Left face check
            if (x == 0 || chunk[y][x - 1].height < height) {
                Render::Position p1 = {posX, posY, posZ};
                Render::Position p2 = {posX, posY, posZ + 1};
                Render::Position p3 = {posX, posY - 1, posZ + 1};
                Render::Position p4 = {posX, posY - 1, posZ};
                Render::Normal faceNormal = (p1.normalize() + p2.normalize() + p3.normalize() + p4.normalize()) / 4.0f;
                mesh.addQuad(
                    Render::ColorMesh::Vertex(p4, color, faceNormal),
                    Render::ColorMesh::Vertex(p3, color, faceNormal),
                    Render::ColorMesh::Vertex(p2, color, faceNormal),
                    Render::ColorMesh::Vertex(p1, color, faceNormal)
                );
            }

            // Right face check
            if (x == chunkWidth - 1 || chunk[y][x + 1].height < height) {
                Render::Position p1 = {posX + 1, posY, posZ};
                Render::Position p2 = {posX + 1, posY, posZ + 1};
                Render::Position p3 = {posX + 1, posY - 1, posZ + 1};
                Render::Position p4 = {posX + 1, posY - 1, posZ};
                Render::Normal faceNormal = (p1.normalize() + p2.normalize() + p3.normalize() + p4.normalize()) / 4.0f;
                mesh.addQuad(
                    Render::ColorMesh::Vertex(p1, color, faceNormal),
                    Render::ColorMesh::Vertex(p2, color, faceNormal),
                    Render::ColorMesh::Vertex(p3, color, faceNormal),
                    Render::ColorMesh::Vertex(p4, color, faceNormal)
                );
            }

            // Front face check
            if (chunk[y][x - 1].height < height) {
                Render::Position p1 = {posX, posY, posZ};
                Render::Position p2 = {posX + 1, posY, posZ};
                Render::Position p3 = {posX + 1, posY - 1, posZ};
                Render::Position p4 = {posX, posY - 1, posZ};
                Render::Normal faceNormal = (p1.normalize() + p2.normalize() + p3.normalize() + p4.normalize()) / 4.0f;
                mesh.addQuad(
                    Render::ColorMesh::Vertex(p1, color, faceNormal),
                    Render::ColorMesh::Vertex(p2, color, faceNormal),
                    Render::ColorMesh::Vertex(p3, color, faceNormal),
                    Render::ColorMesh::Vertex(p4, color, faceNormal)
                );
            }

            // Back face check
            if (chunk[y][x + 1].height < height) {
                Render::Position p1 = {posX, posY, posZ + 1};
                Render::Position p2 = {posX + 1, posY, posZ + 1};
                Render::Position p3 = {posX + 1, posY - 1, posZ + 1};
                Render::Position p4 = {posX, posY - 1, posZ + 1};
                Render::Normal faceNormal = (p1.normalize() + p2.normalize() + p3.normalize() + p4.normalize()) / 4.0f;
                mesh.addQuad(
                    Render::ColorMesh::Vertex(p4, color, faceNormal),
                    Render::ColorMesh::Vertex(p3, color, faceNormal),
                    Render::ColorMesh::Vertex(p2, color, faceNormal),
                    Render::ColorMesh::Vertex(p1, color, faceNormal)
                );
            }
        }
    }
    return mesh;
}

void generateEntitiesForMap(ECS::EntityFactory& entityFactory, const Map& map) {
    for (const auto& [chunkPosition, chunk] : map) {
        Render::ColorMesh chunkMesh = generateChunkMeshFromMap(chunk);
        ECS::Entity entity = entityFactory.createEntity(
                                              "chunk" + std::to_string(chunkPosition.getX()) + "_" + std::to_string(
                                                  chunkPosition.getY()))
                                          .addComponent(ECS::TransformComponent())
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
        Render::ColorRgba color = Render::ColorRgba(increment * 255, 255 - 255 * increment, 255 - 255 * increment, 255);


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

    Map map = generateMap();
    generateEntitiesForMap(entityFactory, map);
}

void Game::update() {
    for (auto& entity : entities) {
        auto& transform = entity.getComponent<ECS::TransformComponent>().transform;
        transform.addRotation(Transform::Rotation(0.01, 0.01, 0.1));
    }
}
