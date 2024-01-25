/**************************************************************************************************
 * @file   CustomFramework.h
 * @author Valentin Dumitru
 * @date   25/01/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include <gtest/gtest.h>
#include <algorithm>
#include <type_traits>
#include <limits>
#include <cmath>
#include "engine/core/debugger/Stringer.h"
#include "engine/core/math/Math.h"


template<typename Type1, typename Type2>
inline void expectEqCustom(const Type1 &a, const Type2 &b) {
    if constexpr (std::is_floating_point_v<decltype(a)> || std::is_floating_point_v<decltype(b)>) {
        constexpr auto epsilon1 = std::is_floating_point_v<decltype(a)> ? GLESC::Math::epsilon<decltype(a)>() : 0.0;
        constexpr auto epsilon2 = std::is_floating_point_v<decltype(b)> ? GLESC::Math::epsilon<decltype(b)>() : 0.0;
        const auto maxEpsilon = std::max(static_cast<double>(epsilon1), static_cast<double>(epsilon2));
        EXPECT_NEAR(a, b, maxEpsilon);
    } else {
        EXPECT_EQ(a, b);
    }
}

template<typename Type1, typename Type2>
inline void expectNeCustom(const Type1 &a, const Type2 &b) {
    EXPECT_FALSE(GLESC::Math::eq(a, b));
}

#define EXPECT_NE_CUSTOM(a, b) \
    expectNeCustom(a, b)

// Macro for flexible equality check
#define EXPECT_EQ_CUSTOM(a, b) \
    expectEqCustom(a, b)


