/**************************************************************************************************
 * @file   TerrainGenerator.h
 * @author Valentin Dumitru
 * @date   2024-04-17
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

#pragma once

#include <array>
#include <unordered_map>

#include "PerlinNoise.hpp"
#include "engine/core/math/algebra/vector/Vector.h"
#include "engine/subsystems/renderer/RendererTypes.h"
#include "engine/subsystems/renderer/mesh/Mesh.h"
#define CHUNK_SIZE 50
#define MAP_SIZE_IN_CHUNKS 10
#define CHUNK_HEIGHT 100
#define DIRT_HEIGHT 3

#define SURFACE_NOISE_SCALE 0.01  // Lower scale for smoother large features
#define CAVE_START_HEIGHT 5        // Height from which caves start
#define CAVE_NOISE_SCALE 0.1       // Scale for cave generation

enum class TileType {
    GRASS = 0,
    WATER,
    SAND,
    ROCK,
    DIRT,
    AIR // Representing no block
};

struct Tile {
    TileType type;
    [[nodiscard]] bool isEmpty() const { return type == TileType::AIR; }
};

using Chunk = std::array<std::array<std::array<Tile, CHUNK_HEIGHT>, CHUNK_SIZE>, CHUNK_SIZE>;
using Map = std::unordered_map<Vec2I, Chunk>;

class TerrainGenerator {
    siv::PerlinNoise noiseGenerator;

public:
    TerrainGenerator() : noiseGenerator(0) {
    }

    Map generateMap() {
        Map map;
        for (int x = 0; x < MAP_SIZE_IN_CHUNKS; x++) {
            for (int z = 0; z < MAP_SIZE_IN_CHUNKS; z++) {
                Vec2I chunkPosition(x, z);
                map[chunkPosition] = generateChunk(chunkPosition);
            }
        }
        return map;
    }

private:
    static TileType getSurfaceTileType(double value) {
        if (value < 0.3 * CHUNK_HEIGHT) return TileType::WATER;
        if (value < 0.4 * CHUNK_HEIGHT) return TileType::SAND;
        if (value < 0.8 * CHUNK_HEIGHT) return TileType::GRASS;
        return TileType::ROCK;
    }

    static TileType getCaveTileType(double value) {
        if (value < 0.5) return TileType::AIR;
        return TileType::ROCK;
    }

    Chunk generateChunk(const Vec2I& chunkPosition) {
        Chunk chunk;
        int chunkX = chunkPosition.getX() * CHUNK_SIZE;
        int chunkZ = chunkPosition.getY() * CHUNK_SIZE;
        for (int x = 0; x < CHUNK_SIZE; x++) {
            for (int z = 0; z < CHUNK_SIZE; z++) {
                // Surface generation
                double wx = chunkX + x;
                double wy = chunkZ + z;
                double baseLayer = noiseGenerator.octave2D_01(
                    wx * SURFACE_NOISE_SCALE,
                    wy * SURFACE_NOISE_SCALE, 4) * CHUNK_HEIGHT * 0.8; // Large, smooth hills
                double detailLayer = noiseGenerator.octave2D_01(
                    wx * SURFACE_NOISE_SCALE * 5,
                    wy * SURFACE_NOISE_SCALE * 5,
                    6) * CHUNK_HEIGHT * 0.2; // Detailed features
                double surfaceHeight = baseLayer + detailLayer;
                int ySurface = static_cast<int>(surfaceHeight);

                // Fill the whole chunk with air
                for (int y = ySurface + 1; y < CHUNK_HEIGHT; y++) {
                    chunk[x][z][y] = Tile{TileType::AIR};
                }
                // Fill the surface layer with the appropriate tile type
                chunk[x][z][ySurface] = Tile{getSurfaceTileType(surfaceHeight)};

                // Fill terrain with blocks
                for (int y = 0; y < ySurface; y++) {
                    chunk[x][z][y] = chunk[x][z][ySurface];
                }
            }
        }

        return chunk;
    }
};

class MeshTerrain {
public:
    static GLESC::Render::ColorMesh generateChunkMeshFromMap(const Chunk& chunk, Vec2I chunkPosition,
                                                             const Map& map) {
        GLESC::Render::ColorMesh mesh;
        mesh.startBuilding();
        const Chunk& leftChunk = chunkPosition.getX() > 0
                                     ? map.at({chunkPosition.getX() - 1, chunkPosition.getY()})
                                     : chunk;
        const Chunk& rightChunk = chunkPosition.getX() < MAP_SIZE_IN_CHUNKS - 1
                                      ? map.at({chunkPosition.getX() + 1, chunkPosition.getY()})
                                      : chunk;
        const Chunk& frontChunk = chunkPosition.getY() < MAP_SIZE_IN_CHUNKS - 1
                                      ? map.at({chunkPosition.getX(), chunkPosition.getY() + 1})
                                      : chunk;
        const Chunk& backChunk = chunkPosition.getY() > 0
                                     ? map.at({chunkPosition.getX(), chunkPosition.getY() - 1})
                                     : chunk;
#pragma omp parallel for collapse(3) schedule(dynamic)
        for (int x = 0; x < CHUNK_SIZE; x++) {
            for (int z = 0; z < CHUNK_SIZE; z++) {
                for (int y = 0; y < CHUNK_HEIGHT; y++) {
                    bool isBlockOnChunkLeftEdge = x == 0;
                    bool isBlockOnChunkRightEdge = x == CHUNK_SIZE - 1;
                    bool isBlockOnChunkFrontEdge = z == CHUNK_SIZE - 1;
                    bool isBlockOnChunkBackEdge = z == 0;
                    Tile currentTile = chunk[x][z][y];
                    if (currentTile.isEmpty()) continue; // Skip air blocks

                    GLESC::Render::ColorRgb color = getColorForTileType(currentTile.type);

                    // Also, if the block is on the edge of the chunk, we need to check the neighboring chunks


                    bool isThereAirOnTop = y < CHUNK_HEIGHT - 1 ? chunk[x][z][y + 1].isEmpty() : true;
                    bool isThereAirOnBottom = y > 0 ? chunk[x][z][y - 1].isEmpty() : false;


                    bool isThereAirOnRight = isBlockOnChunkRightEdge
                                                 ? rightChunk[0][z][y].isEmpty()
                                                 : chunk[x + 1][z][y].isEmpty();
                    bool isThereAirOnLeft = isBlockOnChunkLeftEdge
                                                ? leftChunk[CHUNK_SIZE - 1][z][y].isEmpty()
                                                : chunk[x - 1][z][y].isEmpty();

                    bool isThereAirOnFront = isBlockOnChunkFrontEdge
                                                 ? frontChunk[x][0][y].isEmpty()
                                                 : chunk[x][z + 1][y].isEmpty();
                    bool isThereAirOnBack = isBlockOnChunkBackEdge
                                                ? backChunk[x][CHUNK_SIZE - 1][y].isEmpty()
                                                : chunk[x][z - 1][y].isEmpty();

                    // Y axis
                    if (isThereAirOnTop) {
                        putTopFace(mesh, color, x, y, z);
                    }
                    if (isThereAirOnBottom) {
                        putBottomFace(mesh, color, x, y, z);
                    }


                    // X axis
                    if (isThereAirOnRight) {
                        putBackFace(mesh, color, x, y, z);
                    }
                    if (isThereAirOnLeft) {
                        putFrontFace(mesh, color, x, y, z);
                    }

                    // Z axis
                    if (isThereAirOnBack) {
                        putLeftFace(mesh, color, x, y, z);
                    }
                    if (isThereAirOnFront) {
                        putRightFace(mesh, color, x, y, z);
                    }
                }
            }
        }
        mesh.finishBuilding();
        return mesh;
    }

private:
    static GLESC::Render::ColorRgb getColorForTileType(TileType type) {
        switch (type) {
        case TileType::GRASS:
            return {255 * 0.15, 255 * 0.8, 255 * 0.1}; // Green
        case TileType::WATER:
            return {255 * 0.1, 255 * 0.1, 255 * 0.8}; // Blue
        case TileType::SAND:
            return {255 * 1, 255 * 0.9, 255 * 0.2}; // Yellow
        case TileType::ROCK:
            return {255 * 0.5, 255 * 0.5, 255 * 0.5}; // Gray
        case TileType::DIRT:
            return {255 * 0.6, 255 * 0.3, 255 * 0.1}; // Brown
        default: // Pink for debugging
            return {255 * 1, 255 * 0, 255 * 1};
        }
    }

    static void putFace(GLESC::Render::ColorMesh& mesh,
                        const GLESC::Render::ColorRgb& color, const GLESC::Render::Position& p1,
                        const GLESC::Render::Position& p2, const GLESC::Render::Position& p3,
                        const GLESC::Render::Position& p4, bool isTopFace) {
        if (isTopFace) {
            mesh.addQuad(
                {p1, color},
                {p2, color},
                {p3, color},
                {p4, color}
            );
        }
        else {
            mesh.addQuad(
                {p4, color},
                {p3, color},
                {p2, color},
                {p1, color}
            );
        }
    }

    static void putFrontFace(GLESC::Render::ColorMesh& mesh,
                             const GLESC::Render::ColorRgb& color, int posX, int posY, int posZ) {
        GLESC::Render::Position p1 = {posX - 0.5, posY + 0.5, posZ - 0.5};
        GLESC::Render::Position p2 = {posX - 0.5, posY + 0.5, posZ + 0.5};
        GLESC::Render::Position p3 = {posX - 0.5, posY - 0.5, posZ + 0.5};
        GLESC::Render::Position p4 = {posX - 0.5, posY - 0.5, posZ - 0.5};
        putFace(mesh, color, p1, p2, p3, p4, false);
    }

    static void putBackFace(GLESC::Render::ColorMesh& mesh,
                            const GLESC::Render::ColorRgb& color, int posX, int posY, int posZ) {
        GLESC::Render::Position p1 = {posX + 0.5, posY + 0.5, posZ - 0.5};
        GLESC::Render::Position p2 = {posX + 0.5, posY + 0.5, posZ + 0.5};
        GLESC::Render::Position p3 = {posX + 0.5, posY - 0.5, posZ + 0.5};
        GLESC::Render::Position p4 = {posX + 0.5, posY - 0.5, posZ - 0.5};
        putFace(mesh, color, p1, p2, p3, p4, true);
    }

    static void putLeftFace(GLESC::Render::ColorMesh& mesh,
                            const GLESC::Render::ColorRgb& color, int posX, int posY, int posZ) {
        GLESC::Render::Position p1 = {posX - 0.5, posY + 0.5, posZ - 0.5};
        GLESC::Render::Position p2 = {posX + 0.5, posY + 0.5, posZ - 0.5};
        GLESC::Render::Position p3 = {posX + 0.5, posY - 0.5, posZ - 0.5};
        GLESC::Render::Position p4 = {posX - 0.5, posY - 0.5, posZ - 0.5};
        putFace(mesh, color, p1, p2, p3, p4, true);
    }

    static void putRightFace(GLESC::Render::ColorMesh& mesh,
                             const GLESC::Render::ColorRgb& color, int posX, int posY, int posZ) {
        GLESC::Render::Position p1 = {posX - 0.5, posY + 0.5, posZ + 0.5};
        GLESC::Render::Position p2 = {posX + 0.5, posY + 0.5, posZ + 0.5};
        GLESC::Render::Position p3 = {posX + 0.5, posY - 0.5, posZ + 0.5};
        GLESC::Render::Position p4 = {posX - 0.5, posY - 0.5, posZ + 0.5};
        putFace(mesh, color, p1, p2, p3, p4, false);
    }

    static void putTopFace(GLESC::Render::ColorMesh& mesh,
                           const GLESC::Render::ColorRgb& color, int posX, int posY, int posZ) {
        GLESC::Render::Position p1 = {posX - 0.5, posY + 0.5, posZ - 0.5};
        GLESC::Render::Position p2 = {posX + 0.5, posY + 0.5, posZ - 0.5};
        GLESC::Render::Position p3 = {posX + 0.5, posY + 0.5, posZ + 0.5};
        GLESC::Render::Position p4 = {posX - 0.5, posY + 0.5, posZ + 0.5};
        putFace(mesh, color, p1, p2, p3, p4, false);
    }

    static void putBottomFace(GLESC::Render::ColorMesh& mesh,
                              const GLESC::Render::ColorRgb& color, int posX, int posY, int posZ) {
        GLESC::Render::Position p1 = {posX - 0.5, posY - 0.5, posZ - 0.5};
        GLESC::Render::Position p2 = {posX + 0.5, posY - 0.5, posZ - 0.5};
        GLESC::Render::Position p3 = {posX + 0.5, posY - 0.5, posZ + 0.5};
        GLESC::Render::Position p4 = {posX - 0.5, posY - 0.5, posZ + 0.5};
        putFace(mesh, color, p1, p2, p3, p4, true);
    }

    std::array<GLESC::Render::ColorMesh, MAP_SIZE_IN_CHUNKS * MAP_SIZE_IN_CHUNKS> chunkMeshes;
};
