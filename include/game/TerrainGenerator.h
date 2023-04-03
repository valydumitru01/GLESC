#pragma once

#include <vector>
#include <array>

class TerrainGenerator {
public:
    TerrainGenerator(/* args */);

    ~TerrainGenerator();

private:
    std::vector<float> vertices;
    std::vector<int> terrain;
};

enum TerrainBlocks {
    GRASS,
    WATER,
    DIRT,
    STONE
};

TerrainGenerator::TerrainGenerator() {
}

TerrainGenerator::~TerrainGenerator() {
}
