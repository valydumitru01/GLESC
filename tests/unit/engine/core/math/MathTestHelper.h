/******************************************************************************
 * @file   MathTestHelper.h
 * @author Valentin Dumitru
 * @date   2023-10-26
 * @brief  @todo Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#pragma once

#include <gtest/gtest.h>
#include <algorithm>
#include <type_traits>
#include <limits>
#include <cmath>
#include "engine/core/debugger/Stringer.h"
#include "engine/core/math/Math.h"
#include "engine/core/math/algebra/matrix/Matrix.h"

template<typename Type1, typename Type2>
bool expectEqCustom(const Type1 &a, const Type2 &b) {
    if constexpr (std::is_floating_point_v<decltype(a)> || std::is_floating_point_v<decltype(b)>) {
        constexpr auto epsilon1 = std::is_floating_point_v<decltype(a)> ? GLESC::Math::epsilon<decltype(a)>() : 0.0;
        constexpr auto epsilon2 = std::is_floating_point_v<decltype(b)> ? GLESC::Math::epsilon<decltype(b)>() : 0.0;
        const auto maxEpsilon = std::max(static_cast<double>(epsilon1), static_cast<double>(epsilon2));
        EXPECT_NEAR(a, b, maxEpsilon);
    } else {
        EXPECT_EQ(a, b);
    }
}

// Matrix equality check
template<typename T, size_t N, size_t M>
void expectEqMat(const GLESC::Math::MatrixData<T, N, M> &a, const GLESC::Math::MatrixData<T, N, M> &b) {
    std::cout << "Comparing matrices:\n";
    // Assuming 'toString' is part of the matrix infrastructure
    std::cout << "Left matrix: \n" << GLESC::Stringer::toString(a);
    std::cout << "Right matrix: \n" << GLESC::Stringer::toString(b);
    std::cout << "------------------ Matrix Values comparison: -------------------\n";
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            expectEqCustom(a[i][j], b[i][j]);
        }
    }
    std::cout << "----------------------------------------------------------------\n";
    std::cout << "Matrices are equal\n";
}
template<typename T, size_t N, size_t M>
bool expectEqMat(const GLESC::Math::Matrix<T, N, M> &a, const GLESC::Math::Matrix<T, N, M> &b) {
    expectEqMat(a.data, b.data);
}


// Vector equality check
template<typename T, size_t N>
void expectEqVec(const GLESC::Math::VectorData<T, N> &a, const GLESC::Math::VectorData<T, N> &b) {
    std::cout << "Comparing vectors:\n";
    // Assuming 'toString' is part of the vector infrastructure
    std::cout << "Left vector: " << GLESC::Stringer::toString(a) << "\n";
    std::cout << "Right vector: " << GLESC::Stringer::toString(b) << "\n";
    std::cout << "------------------ Vector Values comparison: -------------------\n";
    for (size_t i = 0; i < N; ++i) {
        expectEqCustom(a[i], b[i]);
    }
    std::cout << "----------------------------------------------------------------\n";
    std::cout << "Vectors are equal\n";
}

template<typename T, size_t N>
bool expectEqVec(const GLESC::Math::Vector<T, N> &a, const GLESC::Math::Vector<T, N> &b) {
    expectEqVec(a.data, b.data);
}

// Macro for flexible equality check
#define EXPECT_EQ_CUSTOM(a, b) \
    expectEqCustom(a, b)

// Macro for matrix equality check
#define EXPECT_EQ_MAT(a, b) \
    expectEqMat(a, b)
// Macro for vector equality check
#define EXPECT_EQ_VEC(a, b) \
    expectEqVec(a, b)


