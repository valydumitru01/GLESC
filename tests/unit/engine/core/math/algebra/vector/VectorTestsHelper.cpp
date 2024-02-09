/**************************************************************************************************
 * @file   VectorTestsHelper.cpp
 * @author Valentin Dumitru
 * @date   31/01/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

#include <gtest/gtest.h>

#include "engine/core/math/algebra/vector/Vector.h"
#include "engine/core/math/algebra/vector/VectorAlgorithms.h"

template <typename Type, size_t N>
struct VectorType {
    using ValueType = Type;
    static const size_t Size = N;
};


using VectorTypes = ::testing::Types<
    // Define different types of vectors you want to test here
    VectorType<float, 2>,
    VectorType<double, 2>,
    VectorType<long double, 2>,
    VectorType<float, 3>,
    VectorType<double, 3>,
    VectorType<long double, 3>,
    VectorType<float, 4>,
    VectorType<double, 4>,
    VectorType<long double, 4>,
    VectorType<float, 5>,
    VectorType<double, 5>,
    VectorType<long double, 5>,
    VectorType<float, 10>,
    VectorType<double, 10>,
    VectorType<long double, 10>
>;

/**
 * @brief Generate next value for the vector: 1, 2, 3, 4, 5, ...
 * @details It will generate numbers for the vectors for the tests.
 * @tparam Type
 * @param i
 * @return The next value for the vector given the index
 */
template <typename Type>
static Type generateNextValue1(size_t i) {
    return Type(i + 1);
}


/**
 * @brief Generate next value for the vector: 11, 22, 33, 44, 55, ...
 * @details It will generate numbers for the vectors for the tests.
 * @tparam Type
 * @param i
 * @return The next value for the vector given the index
 */
template <typename Type>
static Type generateNextValue2(size_t i) {
    return Type(i + 1) * Type(10) + Type(i + 1);
}

template <typename Type, size_t N>
void initVector1(GLESC::Math::VectorData<Type, N>& v) {
    for (size_t i = 0; i < N; ++i)
        v[i] = generateNextValue1<Type>(i);
}

template <typename Type, size_t N>
void initVector2(GLESC::Math::VectorData<Type, N>& v) {
    for (size_t i = 0; i < N; ++i)
        v[i] = generateNextValue2<Type>(i);
}

template <typename Type, size_t N>
void initVector1(VectorT<Type, N>& v) {
    initVector1(v.data);
}

template <typename Type, size_t N>
void initVector2(VectorT<Type, N>& v) {
    initVector2(v.data);
}





#define PREPARE_TEST()\
    using Type = typename TypeParam::ValueType; \
    constexpr size_t N = TypeParam::Size; \
    using Vec = VectorT<Type, N>; \
    using VecData = GLESC::Math::VectorData<Type, N>;
