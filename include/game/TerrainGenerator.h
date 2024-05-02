/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <vector>
#include <array>
#include <unordered_map>

#include "PerlinNoise.hpp"
#include "engine/core/math/algebra/vector/Vector.h"
#include "engine/subsystems/renderer/RendererTypes.h"
#include "engine/subsystems/renderer/mesh/Mesh.h"
#define CHUNK_SIZE 16
#define MAP_SIZE_IN_CHUNKS 5
#define CHUNK_HEIGHT 20
#define DIRT_HEIGHT 3

#define SURFACE_NOISE_SCALE 0.01  // Lower scale for smoother large features
#define CAVE_START_HEIGHT 5        // Height from which caves start
#define CAVE_NOISE_SCALE 0.1       // Scale for cave generation

enum class TileType {
    GRASS,
    WATER,
    SAND,
    ROCK,
    DIRT,
    AIR // Representing no block
};

struct Tile {
    TileType type;
    bool isEmpty() const { return type == TileType::AIR; }
};

using Chunk = std::array<std::array<std::array<Tile, CHUNK_SIZE>, CHUNK_SIZE>, CHUNK_HEIGHT>;
using Map = std::unordered_map<Vec2I, Chunk>;

class TerrainGenerator {
    siv::PerlinNoise noiseGenerator;

public:
    TerrainGenerator() : noiseGenerator(0) {}

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

private:
    TileType getSurfaceTileType(double value) {
        if (value < 0.1) return TileType::WATER;
        if (value < 0.3) return TileType::SAND;
        if (value < 0.6) return TileType::GRASS;
        if (value < 0.8) return TileType::ROCK;
        return TileType::AIR;
    }

    TileType getCaveTileType(double value) {
        if (value < 0.5) return TileType::AIR;
        return TileType::ROCK;
    }

    Chunk generateChunk(const Vec2I& chunkPosition) {
        Chunk chunk;
        for (int x = 0; x < CHUNK_SIZE; x++) {
            for (int z = 0; z < CHUNK_SIZE; z++) {
                // Surface generation
                double wx = chunkPosition.getX() * CHUNK_SIZE + x;
                double wy = chunkPosition.getY() * CHUNK_SIZE + z;
                double surfaceHeight = noiseGenerator.octave2D_01(
                    wx * SURFACE_NOISE_SCALE,
                    wy * SURFACE_NOISE_SCALE, 8) * CHUNK_HEIGHT;
                // Fill the surface layer with the appropriate tile type
                chunk[x][static_cast<int>(surfaceHeight)][z] = Tile{getSurfaceTileType(surfaceHeight)};
                // Fill the rest of the column with air
                for (int y = static_cast<int>(surfaceHeight) + 1; y < CHUNK_HEIGHT; y++) {
                    chunk[x][y][z] = Tile{TileType::AIR};
                }
        /*
                // Fill up to surface height with potentially cave-filled terrain
                for (int y = surfaceHeight-1; y < 0; y--) {
                    double caveNoise = noiseGenerator.octave3D_01(
                        wx * CAVE_NOISE_SCALE,
                        wy * CAVE_NOISE_SCALE,
                        y * CAVE_NOISE_SCALE, 4);



                    // Fill up below the surface with caves
                    if (caveNoise < 0.1) {
                        // Fill up the surface crust with dirt
                        if (surfaceHeight - y < DIRT_HEIGHT) {
                            chunk[x][y][z] = Tile{TileType::DIRT};
                        } else {
                            chunk[x][y][z] = Tile{getCaveTileType(caveNoise)};
                        }
                    } else {
                        chunk[x][y][z] = Tile{TileType::AIR}; // Create caves
                    }
                }*/

                // Fill the remaining heights with air
                /*for (int y = static_cast<int>(surfaceHeight + 1); y < CHUNK_HEIGHT; y++) {
                    chunk[x][y][z] = Tile{TileType::AIR};
                }*/

            }
        }
        return chunk;
    }
};

class MeshTerrain {
public:
    static GLESC::Render::ColorMesh generateChunkMeshFromMap(const Chunk& chunk) {
        GLESC::Render::ColorMesh mesh;
        mesh.startBuilding();
        int chunkHeight = CHUNK_HEIGHT;
        int chunkWidth = CHUNK_SIZE;
        int chunkDepth = CHUNK_SIZE;

        for (int x = 0; x < chunkWidth; x++) {
            for (int y = 0; y < chunkWidth; y++) {
                for (int z = 0; z < chunkDepth; z++) {
                    Tile currentTile = chunk[x][y][z];
                    if (currentTile.isEmpty()) continue; // Skip air blocks

                    GLESC::Render::ColorRgb color = getColorForTileType(currentTile.type);

                    // Add faces based on visibility (no adjacent solid block)
                    if (y == 0 || chunk[x][y-1][z].isEmpty()) {
                        putBottomFace(mesh, color, x, y, z);
                    }
                    if (y == chunkHeight - 1 || chunk[x][y+1][z].isEmpty()) {
                        putTopFace(mesh, color, x, y, z);
                    }
                    if (x == 0 || chunk[x-1][y][z].isEmpty()) {
                        putLeftFace(mesh, color, x, y, z);
                    }
                    if (x == chunkWidth - 1 || chunk[x+1][y][z].isEmpty()) {
                        putRightFace(mesh, color, x, y, z);
                    }
                    if (z == 0 || chunk[x][y][z-1].isEmpty()) {
                        putFrontFace(mesh, color, x, y, z);
                    }
                    if (z == chunkDepth - 1 || chunk[x][y][z+1].isEmpty()) {
                        putBackFace(mesh, color, x, y, z);
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
            return {255*0.15, 255*0.8, 255*0.1}; // Green
        case TileType::WATER:
            return {255*0.1, 255*0.1, 255*0.8}; // Blue
        case TileType::SAND:
            return {255*1, 255*0.9, 255*0.2}; // Yellow
        case TileType::ROCK:
            return {255*0.5, 255*0.5, 255*0.5}; // Gray
        case TileType::DIRT:
            return {255*0.6, 255*0.3, 255*0.1}; // Brown
        default: // Pink for debugging
            return {255*1, 255*0, 255*1};

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

    static void putLeftFace(GLESC::Render::ColorMesh& mesh,
                            const GLESC::Render::ColorRgb& color, int posX, int posY, int posZ) {
        GLESC::Render::Position p1 = {posX, posY, posZ};
        GLESC::Render::Position p2 = {posX, posY, posZ + 1};
        GLESC::Render::Position p3 = {posX, posY - 1, posZ + 1};
        GLESC::Render::Position p4 = {posX, posY - 1, posZ};
        putFace(mesh, color, p1, p2, p3, p4, false);
    }

    static void putRightFace(GLESC::Render::ColorMesh& mesh,
                             const GLESC::Render::ColorRgb& color, int posX, int posY, int posZ) {
        GLESC::Render::Position p1 = {posX + 1, posY, posZ};
        GLESC::Render::Position p2 = {posX + 1, posY, posZ + 1};
        GLESC::Render::Position p3 = {posX + 1, posY - 1, posZ + 1};
        GLESC::Render::Position p4 = {posX + 1, posY - 1, posZ};
        putFace(mesh, color, p1, p2, p3, p4, true);
    }

    static void putFrontFace(GLESC::Render::ColorMesh& mesh,
                             const GLESC::Render::ColorRgb& color, int posX, int posY, int posZ) {
        GLESC::Render::Position p1 = {posX, posY, posZ};
        GLESC::Render::Position p2 = {posX + 1, posY, posZ};
        GLESC::Render::Position p3 = {posX + 1, posY - 1, posZ};
        GLESC::Render::Position p4 = {posX, posY - 1, posZ};
        putFace(mesh, color, p1, p2, p3, p4, true);
    }

    static void putBackFace(GLESC::Render::ColorMesh& mesh,
                            const GLESC::Render::ColorRgb& color, int posX, int posY, int posZ) {
        GLESC::Render::Position p1 = {posX, posY, posZ + 1};
        GLESC::Render::Position p2 = {posX + 1, posY, posZ + 1};
        GLESC::Render::Position p3 = {posX + 1, posY - 1, posZ + 1};
        GLESC::Render::Position p4 = {posX, posY - 1, posZ + 1};
        putFace(mesh, color, p1, p2, p3, p4, false);
    }

    static void putTopFace(GLESC::Render::ColorMesh& mesh,
                           const GLESC::Render::ColorRgb& color, int posX, int posY, int posZ) {
        GLESC::Render::Position p1 = {posX, posY , posZ};
        GLESC::Render::Position p2 = {posX + 1, posY , posZ};
        GLESC::Render::Position p3 = {posX + 1, posY , posZ + 1};
        GLESC::Render::Position p4 = {posX, posY , posZ + 1};
        putFace(mesh, color, p1, p2, p3, p4, false);
    }

    static void putBottomFace(GLESC::Render::ColorMesh& mesh,
                              const GLESC::Render::ColorRgb& color, int posX, int posY, int posZ) {
        GLESC::Render::Position p1 = {posX, posY - 1, posZ};
        GLESC::Render::Position p2 = {posX + 1, posY - 1, posZ};
        GLESC::Render::Position p3 = {posX + 1, posY - 1, posZ + 1};
        GLESC::Render::Position p4 = {posX, posY - 1, posZ + 1};
        putFace(mesh, color, p1, p2, p3, p4, true);
    }

    std::array<GLESC::Render::ColorMesh, MAP_SIZE_IN_CHUNKS * MAP_SIZE_IN_CHUNKS> chunkMeshes;
};
