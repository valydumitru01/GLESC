/**************************************************************************************************
 * @file   Hasher.h
 * @author Valentin Dumitru
 * @date   14/02/2024
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include <functional>
#include <cstddef>

namespace GLESC {
    namespace Hasher {
        using Hash = std::size_t;
        template <typename Hashable>
        static Hash hash(const Hashable& hashable) {
            return std::hash<Hashable>{}(hashable);
        }
        static void hashCombine(std::size_t seed, std::size_t hash) {
            seed = seed ^ (hash + 0x9e3779b9 + (seed << 6) + (seed >> 2));
        }

    }// class Hasher
} // namespace GLESC
