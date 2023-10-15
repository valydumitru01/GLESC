/******************************************************************************
 * @file   Example.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#pragma once

#include <cmath>
#include <type_traits>
#include "engine/core/asserts/Asserts.h"


namespace GLESC::Math {
    constexpr float FLOAT_COMPARISON_EPSILON = 1e-6f;
    constexpr double DOUBLE_COMPARISON_EPSILON = 1e-10;
    constexpr float PI =
            3.1415926535897932384626433832795028841971693993751058209749445923f;
    
    template<typename LValueT, typename RValueT>
    constexpr inline bool eq(LValueT a, RValueT b) {
        if constexpr (std::is_floating_point_v<LValueT> &&
                      std::is_floating_point_v<RValueT>) {
            return std::fabs(a - b) < FLOAT_COMPARISON_EPSILON;
        } else {
            return a == b;
        }
    }

}
