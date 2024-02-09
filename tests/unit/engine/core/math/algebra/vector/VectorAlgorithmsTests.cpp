/**************************************************************************************************
 * @file   VectorAlgorithmsTests.cpp
 * @author Valentin Dumitru
 * @date   16/01/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/


#include <gtest/gtest.h>
#include "engine/core/math/algebra/vector/VectorAlgorithms.h"
#include "unit/engine/core/math/algebra/vector/VectorTestsHelper.cpp"
#include "unit/engine/core/math/MathCustomTestingFramework.cpp"
#ifdef ALGEBRA_TESTING
template <class Type>
class VectorAlgorithmsTests : public testing::Test {
protected:
    VectorAlgorithmsTests() = default;

    void SetUp() override {
        initVector1(this->vecA);
        initVector2(this->vecB);
    }

    void TearDown() override {}

    GLESC::Math::VectorData<typename Type::ValueType, Type::Size> vecA{};
    GLESC::Math::VectorData<typename Type::ValueType, Type::Size> vecB{};
    GLESC::Math::VectorData<typename Type::ValueType, Type::Size> expected{};
    GLESC::Math::VectorData<typename Type::ValueType, Type::Size> result{};
};


TYPED_TEST_SUITE(VectorAlgorithmsTests, VectorTypes);

// =============================================================================================================
// ============================================= Vector Init ===================================================
// =============================================================================================================


TYPED_TEST(VectorAlgorithmsTests, ZeroInitialization) {
    PREPARE_TEST();
    GLESC::Math::VectorAlgorithms::vectorZero(this->vecA);
    for (size_t i = 0; i < N; ++i) {
        EXPECT_EQ(this->vecA[i], Type(0));
    }
}

TYPED_TEST(VectorAlgorithmsTests, FillInitialization) {
    PREPARE_TEST();
    Type fillValue = Type(5);
    GLESC::Math::VectorAlgorithms::vectorFill(this->vecA, fillValue);
    for (size_t i = 0; i < N; ++i) {
        EXPECT_EQ(this->vecA[i], fillValue);
    }
}

TYPED_TEST(VectorAlgorithmsTests, RawArrayInitialization) {
    PREPARE_TEST();
    // Adjust size as per N
    Type rawArray[N] = {Type(1), Type(2)};
    GLESC::Math::VectorAlgorithms::vectorInitRawArray(this->vecA, rawArray);
    for (size_t i = 0; i < N; ++i) {
        EXPECT_EQ(this->vecA[i], rawArray[i]);
    }
}

TYPED_TEST(VectorAlgorithmsTests, CopyInitialization) {
    PREPARE_TEST();
    VecData copySource;
    // Initialize copySource with some values
    GLESC::Math::VectorAlgorithms::vectorCopy(copySource, this->result);
    EXPECT_EQ_VEC(this->result, copySource);
}

TYPED_TEST(VectorAlgorithmsTests, MoveInitialization) {
    PREPARE_TEST();
    VecData vectorToMove;
    initVector1(vectorToMove);
    VecData copySource = vectorToMove;
    // Initialize vectorToMove with some values
    GLESC::Math::VectorAlgorithms::vectorMove(this->result, vectorToMove);
    // Can't really check the state of vectorToMove after move, but can check result
    EXPECT_EQ_VEC(copySource, this->result); // Assuming move keeps the data
}

// =============================================================================================================
// ========================================= Arithmetic operations =============================================
// =============================================================================================================

TYPED_TEST(VectorAlgorithmsTests, VectorAddition) {
    PREPARE_TEST();
    GLESC::Math::VectorAlgorithms::vectorAdd(this->vecA, this->vecB, this->result);
    for (size_t i = 0; i < N; ++i) {
        this->expected[i] = this->vecA[i] + this->vecB[i];
    }
    EXPECT_EQ_VEC(this->result, this->expected);
}

TYPED_TEST(VectorAlgorithmsTests, VectorScalarAddition) {
    PREPARE_TEST();
    Type scalar = 5;
    GLESC::Math::VectorAlgorithms::vectorScalarAdd(this->vecA, scalar, this->result);
    for (size_t i = 0; i < N; ++i) {
        this->expected[i] = this->vecA[i] + scalar;
    }
    EXPECT_EQ_VEC(this->result, this->expected);
}

TYPED_TEST(VectorAlgorithmsTests, VectorSubtraction) {
    PREPARE_TEST();
    GLESC::Math::VectorAlgorithms::vectorSub(this->vecA, this->vecB, this->result);
    for (size_t i = 0; i < N; ++i) {
        this->expected[i] = this->vecA[i] - this->vecB[i];
    }
    EXPECT_EQ_VEC(this->result, this->expected);
}

TYPED_TEST(VectorAlgorithmsTests, VectorScalarSubtraction) {
    PREPARE_TEST();
    Type scalar = 5;
    GLESC::Math::VectorAlgorithms::vectorScalarSub(this->vecA, scalar, this->result);
    for (size_t i = 0; i < N; ++i) {
        this->expected[i] = this->vecA[i] - scalar;
    }
    EXPECT_EQ_VEC(this->result, this->expected);
}

TYPED_TEST(VectorAlgorithmsTests, VectorNegation) {
    PREPARE_TEST();
    GLESC::Math::VectorAlgorithms::vectorNegate(this->vecA, this->result);
    for (size_t i = 0; i < N; ++i) {
        this->expected[i] = -this->vecA[i];
    }
    EXPECT_EQ_VEC(this->result, this->expected);
}

TYPED_TEST(VectorAlgorithmsTests, VectorMultiplication) {
    PREPARE_TEST();
    GLESC::Math::VectorAlgorithms::vectorMul(this->vecA, this->vecB, this->result);
    for (size_t i = 0; i < N; ++i) {
        this->expected[i] = this->vecA[i] * this->vecB[i];
    }
    EXPECT_EQ_VEC(this->result, this->expected);
}

TYPED_TEST(VectorAlgorithmsTests, VectorScalarMultiplication) {
    PREPARE_TEST();
    Type scalar = 5;
    GLESC::Math::VectorAlgorithms::vectorScalarMul(this->vecA, scalar, this->result);
    for (size_t i = 0; i < N; ++i) {
        this->expected[i] = this->vecA[i] * scalar;
    }
    EXPECT_EQ_VEC(this->result, this->expected);
}

TYPED_TEST(VectorAlgorithmsTests, VectorDivision) {
    PREPARE_TEST();
    // Ensure that vecB does not contain zeroes to avoid division by zero
    GLESC::Math::VectorAlgorithms::vectorFill(this->vecB, Type(1)); // Example, replace with suitable values
    GLESC::Math::VectorAlgorithms::vectorDiv(this->vecA, this->vecB, this->result);
    for (size_t i = 0; i < N; ++i) {
        this->expected[i] = this->vecA[i] / this->vecB[i];
    }
    EXPECT_EQ_VEC(this->result, this->expected);
}

TYPED_TEST(VectorAlgorithmsTests, VectorScalarDivision) {
    PREPARE_TEST();
    Type scalar = 5;
    // Ensure scalar is not zero to avoid division by zero
    GLESC::Math::VectorAlgorithms::vectorScalarDiv(this->vecA, scalar, this->result);
    for (size_t i = 0; i < N; ++i) {
        this->expected[i] = this->vecA[i] / scalar;
    }
    EXPECT_EQ_VEC(this->result, this->expected);
}

// =============================================================================================================
// ========================================== Vector Comparations ==============================================
// =============================================================================================================

TYPED_TEST(VectorAlgorithmsTests, VectorEquality) {
    PREPARE_TEST();
    bool isEqual = GLESC::Math::VectorAlgorithms::eq(this->vecA, this->vecB);
    bool expectedResult = false; // Checking different vectors
    EXPECT_EQ(isEqual, expectedResult);

    isEqual = GLESC::Math::VectorAlgorithms::eq(this->vecA, this->vecA);
    expectedResult = true; // Checking same vectors
    EXPECT_EQ(isEqual, expectedResult);
}

TYPED_TEST(VectorAlgorithmsTests, VectorInequality) {
    PREPARE_TEST();
    // Checking different vectors
    bool isNotEqual = GLESC::Math::VectorAlgorithms::neq(this->vecA, this->vecB);
    bool expectedResult = true;
    EXPECT_EQ(isNotEqual, expectedResult);

    // Checking same vectors
    isNotEqual = GLESC::Math::VectorAlgorithms::neq(this->vecA, this->vecA);
    expectedResult = false;
    EXPECT_EQ(isNotEqual, expectedResult);

    // Checking vectors with 1 equal and rest different
    VecData vec1;
    GLESC::Math::VectorAlgorithms::vectorFill(vec1, Type(1));
    VecData vec2;
    GLESC::Math::VectorAlgorithms::vectorFill(vec2, Type(5));
    vec2[0] = Type(1);
    isNotEqual = GLESC::Math::VectorAlgorithms::neq(vec1, vec2);
    expectedResult = true;
    EXPECT_EQ(isNotEqual, expectedResult);

    // Checking vectors with 1 different and rest equal
    GLESC::Math::VectorAlgorithms::vectorFill(vec1, Type(1));
    GLESC::Math::VectorAlgorithms::vectorFill(vec2, Type(1));
    vec2[0] = Type(5);
    isNotEqual = GLESC::Math::VectorAlgorithms::neq(vec1, vec2);
    expectedResult = true;
    EXPECT_EQ(isNotEqual, expectedResult);


}

TYPED_TEST(VectorAlgorithmsTests, VectorLessThan) {
    PREPARE_TEST();
    // Less than checks the lenght of the vectors
    // First we initialize a vector with a lenght of 1
    GLESC::Math::VectorAlgorithms::vectorFill(this->vecA, Type(1));
    // Then we initialize a vector with a lenght of more than 1
    GLESC::Math::VectorAlgorithms::vectorFill(this->vecB, Type(2)); // For example, 2
    bool isLessThan = GLESC::Math::VectorAlgorithms::lt(this->vecA, this->vecB);
    bool expectedResult = true; // A is less than B
    EXPECT_EQ(isLessThan, expectedResult);

    // To check if it works, we swap the vectors and check the negative
    isLessThan = GLESC::Math::VectorAlgorithms::lt(this->vecB, this->vecA);
    expectedResult = false; // B is not less than A
    EXPECT_EQ(isLessThan, expectedResult);
}

// =============================================================================================================
// ========================================== Vector Opeartions ================================================
// =============================================================================================================

TYPED_TEST(VectorAlgorithmsTests, VectorIsZero) {
    PREPARE_TEST();
    bool isZero = GLESC::Math::VectorAlgorithms::isZero(this->vecA);
    bool expectedResult = false; // Assuming vecA is not zero
    EXPECT_EQ(isZero, expectedResult);

    // Test with zero vector
    GLESC::Math::VectorAlgorithms::vectorZero(this->vecA);
    isZero = GLESC::Math::VectorAlgorithms::isZero(this->vecA);
    expectedResult = true; // Assuming vecA is zero
    EXPECT_EQ(isZero, expectedResult);

    // Manually set the first element to a non-zero value
    this->vecA[0] = Type(1);
    isZero = GLESC::Math::VectorAlgorithms::isZero(this->vecA);
    EXPECT_FALSE(isZero);

    // Manually set all the elements to zero
    VecData zeroVec;
    for (size_t i = 0; i < N; ++i) {
        zeroVec[i] = Type(0);
    }
    isZero = GLESC::Math::VectorAlgorithms::isZero(zeroVec);
    EXPECT_TRUE(isZero);
}

TYPED_TEST(VectorAlgorithmsTests, VectorSum) {
    PREPARE_TEST();
    Type result = GLESC::Math::VectorAlgorithms::sum(this->vecA);
    Type expected = Type(0);
    for (size_t i = 0; i < N; ++i) {
        expected += this->vecA[i];
    }
    EXPECT_EQ_CUSTOM(result, expected);
}

TYPED_TEST(VectorAlgorithmsTests, Abs) {
    PREPARE_TEST();
    GLESC::Math::VectorAlgorithms::abs(this->vecA, this->result);
    for (size_t i = 0; i < N; ++i) {
        this->expected[i] = GLESC::Math::abs(this->vecA[i]);
    }
    EXPECT_EQ_VEC(this->result, this->expected);

    // Test with negative values
    GLESC::Math::VectorAlgorithms::vectorFill(this->vecA, Type(-1));
    GLESC::Math::VectorAlgorithms::abs(this->vecA, this->result);
    for (size_t i = 0; i < N; ++i) {
        this->expected[i] = GLESC::Math::abs(this->vecA[i]);
    }
    EXPECT_EQ_VEC(this->result, this->expected);
}

TYPED_TEST(VectorAlgorithmsTests, DotProduct) {
    PREPARE_TEST();
    // Assuming vecA and vecB are initialized by initializeVector
    Type result = GLESC::Math::VectorAlgorithms::dotProduct(this->vecA, this->vecB);
    Type expected = Type(0); // Placeholder, compute based on vecA and vecB
    for (size_t i = 0; i < N; ++i) {
        expected += this->vecA[i] * this->vecB[i];
    }
    EXPECT_EQ_CUSTOM(result, expected);
}

TYPED_TEST(VectorAlgorithmsTests, CrossProduct) {
    PREPARE_TEST();
    if constexpr (N == 3) {
        // Assuming vecA and vecB are initialized by initializeVector
        GLESC::Math::VectorAlgorithms::crossProduct(this->vecA, this->vecB, this->result);
        this->expected = {
            this->vecA[1] * this->vecB[2] - this->vecA[2] * this->vecB[1],
            this->vecA[2] * this->vecB[0] - this->vecA[0] * this->vecB[2],
            this->vecA[0] * this->vecB[1] - this->vecA[1] * this->vecB[0]
        };
        EXPECT_EQ_VEC(this->result, this->expected);
    }
}

TYPED_TEST(VectorAlgorithmsTests, VectorLength) {
    PREPARE_TEST();
    // Assuming vecA is initialized by initializeVector
    Type result = GLESC::Math::VectorAlgorithms::length(this->vecA);
    Type expected = GLESC::Math::sqrt(GLESC::Math::VectorAlgorithms::dotProduct(this->vecA, this->vecA));
    EXPECT_EQ_CUSTOM(result, expected);
}


TYPED_TEST(VectorAlgorithmsTests, VectorLengthSquared) {
    PREPARE_TEST();
    Type result = GLESC::Math::VectorAlgorithms::lengthSquared(this->vecA);
    Type expected = Type(0);
    for (size_t i = 0; i < N; ++i) {
        expected += this->vecA[i] * this->vecA[i];
    }
    EXPECT_EQ_CUSTOM(result, expected);
}


TYPED_TEST(VectorAlgorithmsTests, VectorDistance) {
    PREPARE_TEST();
    Type result = GLESC::Math::VectorAlgorithms::distance(this->vecA, this->vecB);
    VecData diff;
    for (size_t i = 0; i < N; ++i) {
        diff[i] = this->vecA[i] - this->vecB[i];
    }
    Type expected = GLESC::Math::VectorAlgorithms::length(diff);
    EXPECT_EQ_CUSTOM(result, expected);
}

TYPED_TEST(VectorAlgorithmsTests, VectorDistanceSquared) {
    PREPARE_TEST();
    Type result = GLESC::Math::VectorAlgorithms::distanceSquared(this->vecA, this->vecB);
    VecData diff;
    for (size_t i = 0; i < N; ++i) {
        diff[i] = this->vecA[i] - this->vecB[i];
    }
    Type expected = GLESC::Math::VectorAlgorithms::lengthSquared(diff);
    EXPECT_EQ_CUSTOM(result, expected);
}

TYPED_TEST(VectorAlgorithmsTests, VectorNormalize) {
    PREPARE_TEST();
    GLESC::Math::VectorAlgorithms::normalize(this->vecA, this->result);
    Type len = GLESC::Math::VectorAlgorithms::length(this->vecA);
    if (len != Type(0) && len != Type(1)) {
        for (size_t i = 0; i < N; ++i) {
            this->expected[i] = this->vecA[i] / len;
        }
    }
    else {
        this->expected = this->vecA;
    }
    EXPECT_EQ_VEC(this->result, this->expected);
}

TYPED_TEST(VectorAlgorithmsTests, VectorAngle) {
    PREPARE_TEST();
    Type result = GLESC::Math::VectorAlgorithms::angle(this->vecA, this->vecB);

    Type dot = GLESC::Math::VectorAlgorithms::dotProduct(this->vecA, this->vecB);
    Type lenA = GLESC::Math::VectorAlgorithms::length(this->vecA);
    Type lenB = GLESC::Math::VectorAlgorithms::length(this->vecB);
    Type expected = std::acos(dot / (lenA * lenB));
    EXPECT_EQ_CUSTOM(result, expected);
}


TYPED_TEST(VectorAlgorithmsTests, VectorProjection) {
    PREPARE_TEST();
    GLESC::Math::VectorAlgorithms::project(this->vecA, this->vecB, this->result);

    Type scalarProjection = GLESC::Math::VectorAlgorithms::dotProduct(this->vecA, this->vecB) /
        GLESC::Math::VectorAlgorithms::length(this->vecB);
    GLESC::Math::VectorAlgorithms::vectorScalarMul(this->vecB, scalarProjection, this->expected);
    EXPECT_EQ_VEC(this->result, this->expected);
}

TYPED_TEST(VectorAlgorithmsTests, AreParallel) {
    PREPARE_TEST();

    // Positive case: vectors are parallel
    VecData parallelVec1;
    VecData parallelVec2;
    Type scalar = Type(2);
    initVector1(parallelVec1);
    initVector1(parallelVec2);
    // parallelVec2 is a scalar multiple of parallelVec1
    GLESC::Math::VectorAlgorithms::vectorScalarMul(parallelVec2, scalar, parallelVec2);
    bool resultPositive = GLESC::Math::VectorAlgorithms::areParallel(parallelVec1, parallelVec2);
    EXPECT_TRUE(resultPositive);

    // Negative case: vectors are not parallel
    VecData notParallelVec1 = parallelVec1; // Same as parallelVec1
    VecData notParallelVec2 = parallelVec2;
    notParallelVec2[0] += Type(100); // Significantly alter the first element

    // Apply a change that alters the direction of the vector significantly
    if (N > 1) {
        notParallelVec2[1] += Type(100); // Also significantly alter the second element
    }

    bool resultNegative = GLESC::Math::VectorAlgorithms::areParallel(notParallelVec1, notParallelVec2);
    EXPECT_FALSE(resultNegative);
}

TYPED_TEST(VectorAlgorithmsTests, IsHomogeneous) {
    PREPARE_TEST();
    // Assuming vecA is initialized by initializeVector
    bool result = GLESC::Math::VectorAlgorithms::isHomogeneous(this->vecA);
    bool expected = (this->vecA[N - 1] == Type(1)); // Change based on expected result
    EXPECT_EQ_CUSTOM(result, expected);
}


TYPED_TEST(VectorAlgorithmsTests, Homogenize) {
    PREPARE_TEST();

    // Test homogenizing a vector
    GLESC::Math::VectorData<Type, N + 1> homogenized;
    GLESC::Math::VectorAlgorithms::homogenize(this->vecA, homogenized);

    GLESC::Math::VectorData<Type, N + 1> expectedHomogenized;
    for (size_t i = 0; i < N; ++i) { // Iterate up to N
        expectedHomogenized[i] = this->vecA[i];
    }
    expectedHomogenized[N] = Type(1); // Set index N to 1
    EXPECT_EQ_VEC(homogenized, expectedHomogenized);
}

TYPED_TEST(VectorAlgorithmsTests, Dehomogenize) {
    PREPARE_TEST();

    this->vecA[N - 1] = Type(1); // Ensure the last element (homogeneous coordinate) is not zero
    GLESC::Math::VectorData<Type, N - 1> dehomogenized;
    GLESC::Math::VectorAlgorithms::dehomogenize(this->vecA, dehomogenized);

    GLESC::Math::VectorData<Type, N - 1> expectedDehomogenized;
    Type wComponent = this->vecA[N - 1]; // The last element of the homogeneous vector
    for (size_t i = 0; i < N - 1; ++i) {
        expectedDehomogenized[i] = this->vecA[i] / wComponent;
    }
    EXPECT_EQ_VEC(dehomogenized, expectedDehomogenized);
}

TYPED_TEST(VectorAlgorithmsTests, AreOrthogonal) {
    PREPARE_TEST();

    // Positive case: vectors are orthogonal
    VecData orthogonalVec1;
    VecData orthogonalVec2;
    GLESC::Math::VectorAlgorithms::vectorZero(orthogonalVec1);
    GLESC::Math::VectorAlgorithms::vectorZero(orthogonalVec2);
    orthogonalVec1[0] = Type(1); // First vector is [1, 0, 0, ...]
    if (N > 1) {
        orthogonalVec2[1] = Type(1); // Second vector is [0, 1, 0, ...]
    }
    bool resultPositive = GLESC::Math::VectorAlgorithms::areOrthogonal(orthogonalVec1, orthogonalVec2);
    EXPECT_TRUE(resultPositive);

    // Negative case: vectors are not orthogonal
    VecData notOrthogonalVec1 = orthogonalVec1; // Same as orthogonalVec1
    VecData notOrthogonalVec2 = orthogonalVec1; // Same as orthogonalVec1, hence not orthogonal
    bool resultNegative = GLESC::Math::VectorAlgorithms::areOrthogonal(notOrthogonalVec1, notOrthogonalVec2);
    EXPECT_FALSE(resultNegative);

    // Negative case 2: vectors are not orthogonal (one is a scalar multiple of the other)
    VecData notOrthogonalVec3 = orthogonalVec1; // Same as orthogonalVec1
    // Scalar multiple of orthogonalVec1, hence not orthogonal
    VecData notOrthogonalVec4;
    GLESC::Math::VectorAlgorithms::vectorScalarAdd(notOrthogonalVec3, Type(1), notOrthogonalVec4);
    bool resultNegative2 = GLESC::Math::VectorAlgorithms::areOrthogonal(notOrthogonalVec3, notOrthogonalVec4);
    EXPECT_FALSE(resultNegative2);
}

TYPED_TEST(VectorAlgorithmsTests, GetOrthogonal) {
    PREPARE_TEST();
    if constexpr (N == 2 || N == 3 || N == 4) {
        // Assuming vecA is initialized by initializeVector
        GLESC::Math::VectorAlgorithms::getOrthogonal(this->vecA, this->result);
        // As the specific orthogonal vector might depend on the implementation details,
        // you can directly verify if the result vector is indeed orthogonal to vecA.
        EXPECT_TRUE(GLESC::Math::VectorAlgorithms::areOrthogonal(this->vecA, this->result));
    }
}

TYPED_TEST(VectorAlgorithmsTests, VectorCollinearity) {
    PREPARE_TEST();
    if constexpr (N == 3) {
        // Two vectors are always collinear
        std::vector<const VecData*> collinearVecs = {&this->vecA};
        EXPECT_TRUE(GLESC::Math::VectorMixedAlgorithms::areCollinear(this->vecA, collinearVecs));
        // Collinear vectors with a scalar multiple
        collinearVecs.clear();
        VecData collinearVec1 = this->vecA;
        VecData collinearVec2 = this->vecA;
        VecData collinearVec3 = this->vecA;
        GLESC::Math::VectorAlgorithms::vectorScalarMul(collinearVec1, Type(2), collinearVec1);
        GLESC::Math::VectorAlgorithms::vectorScalarMul(collinearVec2, Type(0.5), collinearVec2);
        GLESC::Math::VectorAlgorithms::vectorScalarMul(collinearVec3, Type(-1), collinearVec3);
        collinearVecs.push_back(&collinearVec1);
        collinearVecs.push_back(&collinearVec2);
        collinearVecs.push_back(&collinearVec3);
        EXPECT_TRUE(GLESC::Math::VectorMixedAlgorithms::areCollinear(this->vecA, collinearVecs));

        // Non-collinear vectors
        VecData nonCollinear = this->vecA;
        GLESC::Math::VectorAlgorithms::vectorScalarAdd(nonCollinear, Type(-1), nonCollinear);
        std::vector<const VecData*> nonCollinearVecs = {&nonCollinear, &this->vecA};
        EXPECT_FALSE(GLESC::Math::VectorMixedAlgorithms::areCollinear(this->vecA, nonCollinearVecs));
    }
}

#endif // ALGEBRA_TESTING
