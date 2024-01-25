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

#include <iostream>
#include "unit/CustomTestingFramework.cpp"
#include "engine/core/math/algebra/matrix/Matrix.h"

template<typename T, size_t N, size_t M>
inline void preMatCheckPrint(const GLESC::Math::MatrixData<T, N, M> &a, const GLESC::Math::MatrixData<T, N, M> &b){
    
    std::cout << "Comparing matrices:\n";
    // Assuming 'toString' is part of the matrix infrastructure
    std::cout << "Left matrix: \n" << GLESC::Stringer::toString(a) << "\n";
    std::cout << "Right matrix: \n" << GLESC::Stringer::toString(b) << "\n";
    std::cout << "------------------ Matrix Values comparison: -------------------\n";
}

inline void postMatCheckPrint(){
    std::cout << "----------------------------------------------------------------\n";
    std::cout << "Matrices are equal\n";
}


// Matrix equality check
template<typename T, size_t N, size_t M>
inline void expectEqMat(const GLESC::Math::MatrixData<T, N, M> &a, const GLESC::Math::MatrixData<T, N, M> &b) {
    S_ASSERT_TRUE(N > 0 && M > 0, "Matrix dimensions must be positive");
    preMatCheckPrint(a, b);
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            std::cout << "Comparing element [" << i << "][" << j << "]\n";
            expectEqCustom(a[i][j], b[i][j]);
        }
    }
    postMatCheckPrint();
}

template<typename T, size_t N, size_t M>
inline void expectNeMat(const GLESC::Math::MatrixData<T, N, M> &a, const GLESC::Math::MatrixData<T, N, M> &b) {
    S_ASSERT_TRUE(N > 0 && M > 0, "Matrix dimensions must be positive");
    preMatCheckPrint(a, b);
    bool areEqual = true;
    for (size_t i = 0; i < N && areEqual; ++i) {
        for (size_t j = 0; j < M && areEqual; ++j) {
            std::cout << "Comparing element [" << i << "][" << j << "]\n";
            areEqual = GLESC::Math::eq(a[i][j], b[i][j]);
        }
    }
    postMatCheckPrint();
    EXPECT_FALSE(areEqual);
}

template<typename T, size_t N, size_t M>
inline void expectEqMat(const GLESC::Math::Matrix<T, N, M> &a, const GLESC::Math::Matrix<T, N, M> &b) {
    expectEqMat(a.data, b.data);
}

template<typename T, size_t N, size_t M>
inline void expectNeMat(const GLESC::Math::Matrix<T, N, M> &a, const GLESC::Math::Matrix<T, N, M> &b) {
    expectNeMat(a.data, b.data);
}


// Vector equality check
template<typename T, size_t N>
inline void expectEqVec(const GLESC::Math::VectorData<T, N> &a, const GLESC::Math::VectorData<T, N> &b) {
    std::cout << "Comparing vectors:\n";
    // Assuming 'toString' is part of the vector infrastructure
    std::cout << "Left vector: " << GLESC::Stringer::toString(a) << "\n";
    std::cout << "Right vector: " << GLESC::Stringer::toString(b) << "\n";
    std::cout << "------------------ Vector Values comparison: -------------------\n";
    for (size_t i = 0; i < N; ++i) {
        std::cout << "Comparing element [" << i << "]\n";
        expectEqCustom(a[i], b[i]);
    }
    std::cout << "----------------------------------------------------------------\n";
    std::cout << "Vectors are equal\n";
}

template<typename T, size_t N>
inline void expectEqVec(const GLESC::Math::Vector<T, N> &a, const GLESC::Math::Vector<T, N> &b) {
    expectEqVec(a.data, b.data);
}



// Macro for matrix equality check
#define EXPECT_EQ_MAT(a, b) \
    expectEqMat(a, b)
    
// Macro for matrix inequality check
#define EXPECT_NE_MAT(a, b) \
    expectNeMat(a, b)
    
// Macro for vector equality check
#define EXPECT_EQ_VEC(a, b) \
    expectEqVec(a, b)