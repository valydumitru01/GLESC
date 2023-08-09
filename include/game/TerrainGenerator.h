/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

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
