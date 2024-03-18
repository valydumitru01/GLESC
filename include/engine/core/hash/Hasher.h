/**************************************************************************************************
 * @file   Hasher.h
 * @author Valentin Dumitru
 * @date   14/02/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include <cstddef>

namespace GLESC {
    class Hasher {
    public:
        static void hashCombine(std::size_t seed, std::size_t hash) {
            seed = seed ^ (hash + 0x9e3779b9 + (seed << 6) + (seed >> 2));
        }
    }; // class Hasher
} // namespace GLESC
