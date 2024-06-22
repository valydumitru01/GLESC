/**************************************************************************************************
 * @file   VectorAlgorithmsTests.cpp
 * @author Valentin Dumitru
 * @date   16/01/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once


#include "TestsConfig.h"
#ifdef MATH_ALGEBRA_UNIT_TESTING
#include <gtest/gtest.h>
#include <engine/core/math/algebra/vector/VectorMixedAlgorithms.h>
#include "engine/core/math/algebra/matrix/Matrix.h"
#include "engine/subsystems/input/InputKeys.h"
#include "unit/engine/core/math/algebra/vector/VectorTestsHelper.h"
#include "unit/engine/core/math/MathCustomTestingFramework.h"

template <typename Type>
class VectorTests : public ::testing::Test {
protected:
    VectorTests() = default;

    void SetUp() override {
        initVector1(this->v1);
        initVector2(this->v2);
    }

    void TearDown() override {
    }

    VectorT<typename Type::ValueType, Type::Size> v1;
    VectorT<typename Type::ValueType, Type::Size> v2;
    VectorT<typename Type::ValueType, Type::Size> expected{};
    VectorT<typename Type::ValueType, Type::Size> result{};
};

TYPED_TEST_SUITE(VectorTests, VectorTypes);


TYPED_TEST(VectorTests, Accesors) {
    PREPARE_TEST();

    TEST_SECTION("Vector Size")
    {
        EXPECT_EQ(this->v1.size(), N);
    }

    TEST_SECTION("Vector get()")
    {
        for (size_t i = 0; i < N; ++i)
            EXPECT_EQ_CUSTOM(this->v1.get(i), generateNextValue1<Type>(i));
    }

    TEST_SECTION("Vector []")
    {
        for (size_t i = 0; i < N; ++i)
            EXPECT_EQ_CUSTOM(this->v1[i], generateNextValue1<Type>(i));
    }

    TEST_SECTION("Vector x(), y(), z(), w()")
    {
        Vec v3;
        initVector1(v3);
        if constexpr (N >= 1) {
            EXPECT_EQ_CUSTOM(this->v1.x(), generateNextValue1<Type>(0));
            EXPECT_EQ_CUSTOM(this->v1.getX(), generateNextValue1<Type>(0));

            v3.x(generateNextValue1<Type>(0) + Type(1));
            EXPECT_EQ_CUSTOM(v3.x(), generateNextValue1<Type>(0) + Type(1));
            v3.setX(generateNextValue1<Type>(0) + Type(2));
            EXPECT_EQ_CUSTOM(v3.x(), generateNextValue1<Type>(0) + Type(2));
        }
        if constexpr (N >= 2) {
            EXPECT_EQ_CUSTOM(this->v1.y(), generateNextValue1<Type>(1));
            EXPECT_EQ_CUSTOM(this->v1.getY(), generateNextValue1<Type>(1));

            v3.y(generateNextValue1<Type>(1) + Type(1));
            EXPECT_EQ_CUSTOM(v3.y(), generateNextValue1<Type>(1) + Type(1));

            v3.setY(generateNextValue1<Type>(1) + Type(2));
            EXPECT_EQ_CUSTOM(v3.y(), generateNextValue1<Type>(1) + Type(2));
        }
        if constexpr (N >= 3) {
            EXPECT_EQ_CUSTOM(this->v1.z(), generateNextValue1<Type>(2));
            EXPECT_EQ_CUSTOM(this->v1.getZ(), generateNextValue1<Type>(2));

            v3.z(generateNextValue1<Type>(2) + Type(1));
            EXPECT_EQ_CUSTOM(v3.z(), generateNextValue1<Type>(2) + Type(1));

            v3.setZ(generateNextValue1<Type>(2) + Type(2));
            EXPECT_EQ_CUSTOM(v3.z(), generateNextValue1<Type>(2) + Type(2));
        }
        if constexpr (N >= 4) {
            EXPECT_EQ_CUSTOM(this->v1.w(), generateNextValue1<Type>(3));
            EXPECT_EQ_CUSTOM(this->v1.getW(), generateNextValue1<Type>(3));

            v3.w(generateNextValue1<Type>(3) + Type(1));
            EXPECT_EQ_CUSTOM(v3.w(), generateNextValue1<Type>(3) + Type(1));

            v3.setW(generateNextValue1<Type>(3) + Type(2));
            EXPECT_EQ_CUSTOM(v3.w(), generateNextValue1<Type>(3) + Type(2));
        }
    }
}

TYPED_TEST(VectorTests, Constructors) {
    PREPARE_TEST();
    TEST_SECTION("Default Constructor")
    {
        Vec defaultConstruct;
        Vec expectDefaultConstruct;
        for (size_t i = 0; i < N; ++i)
            expectDefaultConstruct.set(i, Type());
        EXPECT_EQ_VEC(defaultConstruct, expectDefaultConstruct);
    }
    TEST_SECTION("Variadic Constructor")
    {
        // Variadic constructor
        if constexpr (N == 2) {
            Vec variadicConstruct(generateNextValue1<Type>(0), generateNextValue1<Type>(1));
            EXPECT_EQ_VEC(variadicConstruct, this->v1);
        }
        if constexpr (N == 3) {
            Vec variadicConstruct(generateNextValue1<Type>(0), generateNextValue1<Type>(1),
                                  generateNextValue1<Type>(2));
            EXPECT_EQ_VEC(variadicConstruct, this->v1);
        }
        if constexpr (N == 4) {
            Vec variadicConstruct
            (generateNextValue1<Type>(0), generateNextValue1<Type>(1), generateNextValue1<Type>(2),
             generateNextValue1<Type>(3));
            EXPECT_EQ_VEC(variadicConstruct, this->v1);
        } // Enough with the variadic constructors, it could go on forever
    }

    TEST_SECTION("Array constructor")
    {
        // Array constructor
        Type arr[N];
        for (size_t i = 0; i < N; ++i)
            arr[i] = generateNextValue1<Type>(i);
        Vec arrayConstruct(arr);
        EXPECT_EQ_VEC(arrayConstruct, this->v1);
    }
    TEST_SECTION("Initializer List Constructor")
    {
        // Initializer list constructor
        if constexpr (N == 2) {
            Vec initListConstruct{generateNextValue1<Type>(0), generateNextValue1<Type>(1)};
            EXPECT_EQ_VEC(initListConstruct, this->v1);
        }
        if constexpr (N == 3) {
            Vec initListConstruct{
                generateNextValue1<Type>(0), generateNextValue1<Type>(1),
                generateNextValue1<Type>(2)
            };
            EXPECT_EQ_VEC(initListConstruct, this->v1);
        }
        if constexpr (N == 4) {
            Vec initListConstruct
            {
                generateNextValue1<Type>(0), generateNextValue1<Type>(1), generateNextValue1<Type>(2),
                generateNextValue1<Type>(3)
            };
            EXPECT_EQ_VEC(initListConstruct, this->v1);
        } // Enough with the initializers, it could go on forever
    }
    TEST_SECTION("Fill Constructor")
    {
        // Fill constructor
        Type fillValue = Type(1);
        Vec fillConstruct(fillValue);
        Vec expectFillConstruct;
        GLESC::Math::VectorAlgorithms::vectorFill(expectFillConstruct.data, fillValue);
        EXPECT_EQ_VEC(fillConstruct, expectFillConstruct);
    }
    TEST_SECTION("Copy Constructor")
    {
        // Copy constructor
        Vec copyConstruct;
        initVector1(copyConstruct);
        Vec copyConstruct2(copyConstruct);
        EXPECT_EQ_VEC(copyConstruct2, copyConstruct);
        EXPECT_EQ_VEC(copyConstruct2, this->v1); // Must be equal to the initial vector
    }
    TEST_SECTION("Move Constructor")
    {
        // Move constructor
        Vec moveConstruct;
        initVector1(moveConstruct);
        Vec moveConstruct2(std::move(moveConstruct));
        EXPECT_EQ_VEC(moveConstruct2, this->v1);
    }
}

TYPED_TEST(VectorTests, CopyAssignment) {
    PREPARE_TEST();
    // Copy assignment
    Vec copyAssign;
    copyAssign = this->v1;
    EXPECT_EQ_VEC(copyAssign, this->v1); // Must be equal to the initial vector
}

TYPED_TEST(VectorTests, MoveAssignment) {
    PREPARE_TEST();
    // Move assignment
    Vec moveAssign;
    Vec moveAssign2;
    initVector1(moveAssign);
    moveAssign2 = std::move(moveAssign);
    EXPECT_EQ_VEC(moveAssign2, this->v1);
}

TYPED_TEST(VectorTests, ArrayAssignment) {
    PREPARE_TEST();
    // Array assignment
    Type arr[N];
    for (size_t i = 0; i < N; ++i)
        arr[i] = generateNextValue1<Type>(i);
    Vec arrayAssign;
    arrayAssign = arr;
    EXPECT_EQ_VEC(arrayAssign, this->v1);
}

TYPED_TEST(VectorTests, InitializerListAssignment) {
    PREPARE_TEST();
    // Initializer list assignment
    if constexpr (N == 2) {
        Vec initListAssign;
        initListAssign = {generateNextValue1<Type>(0), generateNextValue1<Type>(1)};
        EXPECT_EQ_VEC(initListAssign, this->v1);
    }
    if constexpr (N == 3) {
        Vec initListAssign;
        initListAssign = {
            generateNextValue1<Type>(0), generateNextValue1<Type>(1),
            generateNextValue1<Type>(2)
        };
        EXPECT_EQ_VEC(initListAssign, this->v1);
    }
    if constexpr (N == 4) {
        Vec initListAssign;
        initListAssign =
        {
            generateNextValue1<Type>(0), generateNextValue1<Type>(1), generateNextValue1<Type>(2),
            generateNextValue1<Type>(3)
        };
        EXPECT_EQ_VEC(initListAssign, this->v1);
    } // Enough with the initializers, it could go on forever
}


// =============================================================================================================
// ========================================= Arithmetic operations =============================================
// =============================================================================================================

TYPED_TEST(VectorTests, AdditionAssignment) {
    PREPARE_TEST();
    // Addition assignment with another vector
    Vec addAssign = this->v1;
    addAssign += this->v1;
    Vec expectAddAssign;
    GLESC::Math::VectorAlgorithms::vectorAdd(this->v1.data, this->v1.data, expectAddAssign.data);
    EXPECT_EQ_VEC(addAssign, expectAddAssign);
}

TYPED_TEST(VectorTests, AdditionAssignmentScalar) {
    PREPARE_TEST();
    // Addition assignment with a scalar
    Vec addAssignScalar = this->v1;
    const Type scalarAdd = Type(10);
    addAssignScalar += scalarAdd;
    Vec expectAddAssignScalar = this->v1;
    GLESC::Math::VectorAlgorithms::vectorScalarAdd(this->v1.data, scalarAdd, expectAddAssignScalar.data);
    EXPECT_EQ_VEC(addAssignScalar, expectAddAssignScalar);
}

TYPED_TEST(VectorTests, SubtractionAssignment) {
    PREPARE_TEST();
    // Subtraction assignment with another vector
    Vec subAssign = this->v1;
    subAssign -= this->v2;
    Vec expectSubAssign;
    GLESC::Math::VectorAlgorithms::vectorSub(this->v1.data, this->v2.data, expectSubAssign.data);
    EXPECT_EQ_VEC(subAssign, expectSubAssign);
}

TYPED_TEST(VectorTests, SubtractionAssignmentScalar) {
    PREPARE_TEST();
    // Subtraction assignment with a scalar
    Vec subAssignScalar = this->v1;
    const Type scalarSub = Type(10);
    subAssignScalar -= scalarSub;
    Vec expectSubAssignScalar;
    GLESC::Math::VectorAlgorithms::vectorScalarSub(this->v1.data, scalarSub, expectSubAssignScalar.data);
    EXPECT_EQ_VEC(subAssignScalar, expectSubAssignScalar);
}

TYPED_TEST(VectorTests, MultiplicationAssignment) {
    PREPARE_TEST();
    // Multiplication assignment with another vector
    Vec mulAssign = this->v1;
    mulAssign *= this->v1;
    Vec expectMulAssign;
    GLESC::Math::VectorAlgorithms::vectorMul(this->v1.data, this->v1.data, expectMulAssign.data);
    EXPECT_EQ_VEC(mulAssign, expectMulAssign);
}

TYPED_TEST(VectorTests, MultiplicationAssignmentScalar) {
    PREPARE_TEST();
    // Multiplication assignment with a scalar
    Vec mulAssignScalar = this->v1;
    const Type scalarMul = Type(10);
    mulAssignScalar *= scalarMul;
    Vec expectMulAssignScalar;
    GLESC::Math::VectorAlgorithms::vectorScalarMul(this->v1.data, scalarMul, expectMulAssignScalar.data);
    EXPECT_EQ_VEC(mulAssignScalar, expectMulAssignScalar);
}

TYPED_TEST(VectorTests, DivisionAssignment) {
    PREPARE_TEST();
    // Division assignment with another vector
    Vec divAssign = this->v1;
    divAssign /= this->v2;

    Vec expectDivAssign;
    GLESC::Math::VectorAlgorithms::vectorDiv(this->v1.data, this->v2.data, expectDivAssign.data);
    EXPECT_EQ_VEC(divAssign, expectDivAssign);
}

TYPED_TEST(VectorTests, DivisionAssignmentScalar) {
    PREPARE_TEST();
    // Division assignment with a scalar
    Vec divAssignScalar = this->v1;
    const Type scalarDiv = Type(10);
    divAssignScalar /= scalarDiv;

    Vec expectDivAssignScalar;
    GLESC::Math::VectorAlgorithms::vectorScalarDiv(this->v1.data, scalarDiv, expectDivAssignScalar.data);

    EXPECT_EQ_VEC(divAssignScalar, expectDivAssignScalar);
}


TYPED_TEST(VectorTests, AddArithmeticOperator) {
    PREPARE_TEST();

    // Addition with another vector
    Vec add;
    add = this->v1 + this->v2;

    Vec expectAdd;
    GLESC::Math::VectorAlgorithms::vectorAdd(this->v1.data, this->v2.data, expectAdd.data);
    EXPECT_EQ_VEC(add, expectAdd);
}

TYPED_TEST(VectorTests, AddScalarAritmeticOperator) {
    PREPARE_TEST();
    // Addition with a scalar
    Vec addScalar;
    const Type scalarAdd = Type(10);
    addScalar = this->v1 + scalarAdd;

    Vec expectAddScalar;
    GLESC::Math::VectorAlgorithms::vectorScalarAdd(this->v1.data, scalarAdd, expectAddScalar.data);
    EXPECT_EQ_VEC(addScalar, expectAddScalar);
}

TYPED_TEST(VectorTests, SubArithmeticOperator) {
    PREPARE_TEST();
    // Subtraction with another vector
    Vec sub;
    sub = this->v1 - this->v2;
    Vec expectSub;
    GLESC::Math::VectorAlgorithms::vectorSub(this->v1.data, this->v2.data, expectSub.data);
    EXPECT_EQ_VEC(sub, expectSub);
}

TYPED_TEST(VectorTests, SubScalarAritmeticOperator) {
    PREPARE_TEST();
    // Subtraction with a scalar
    Vec subScalar;
    const Type scalarSub = Type(10);
    subScalar = this->v1 - scalarSub;
    Vec expectSubScalar;
    GLESC::Math::VectorAlgorithms::vectorScalarSub(this->v1.data, scalarSub, expectSubScalar.data);
    EXPECT_EQ_VEC(subScalar, expectSubScalar);
}

TYPED_TEST(VectorTests, UnaryMinusOperators) {
    PREPARE_TEST();
    // Unary minus
    Vec unaryMinus;
    unaryMinus = -this->v1;
    Vec expectUnaryMinus;
    GLESC::Math::VectorAlgorithms::vectorNegate(this->v1.data, expectUnaryMinus.data);
    EXPECT_EQ_VEC(unaryMinus, expectUnaryMinus);
}

TYPED_TEST(VectorTests, MultiplicationOperators) {
    PREPARE_TEST();
    // Multiplication with another vector
    Vec mul;
    mul = this->v1 * this->v2;
    Vec expectMul;
    GLESC::Math::VectorAlgorithms::vectorMul(this->v1.data, this->v2.data, expectMul.data);
    EXPECT_EQ_VEC(mul, expectMul);
}

TYPED_TEST(VectorTests, MultiplicationScalarOperators) {
    PREPARE_TEST();
    // Multiplication with a scalar
    Vec mulScalar;
    const Type scalarMul = Type(10);
    mulScalar = this->v1 * scalarMul;
    Vec expectMulScalar;
    GLESC::Math::VectorAlgorithms::vectorScalarMul(this->v1.data, scalarMul, expectMulScalar.data);
    EXPECT_EQ_VEC(mulScalar, expectMulScalar);
}

TYPED_TEST(VectorTests, DivisionOperators) {
    PREPARE_TEST();
    // Division with another vector
    Vec div;
    div = this->v1 / this->v2;
    Vec expectDiv;
    GLESC::Math::VectorAlgorithms::vectorDiv(this->v1.data, this->v2.data, expectDiv.data);
    EXPECT_EQ_VEC(div, expectDiv);
}

TYPED_TEST(VectorTests, DivisionScalarOperators) {
    PREPARE_TEST();
    // Division with a scalar
    Vec divScalar;
    const Type scalarDiv = Type(10);
    divScalar = this->v1 / scalarDiv;
    Vec expectDivScalar;
    GLESC::Math::VectorAlgorithms::vectorScalarDiv(this->v1.data, scalarDiv, expectDivScalar.data);
    EXPECT_EQ_VEC(divScalar, expectDivScalar);
}

// =============================================================================================================
// ========================================== Vector Comparations ==============================================
// =============================================================================================================

TYPED_TEST(VectorTests, EqualityOperator) {
    PREPARE_TEST();

    // Equality
    Vec eq = this->v1;
    EXPECT_TRUE(eq == this->v1);

    Vec eq2 = this->v2;
    EXPECT_FALSE(eq2 == this->v1);
}

TYPED_TEST(VectorTests, InequalityOperator) {
    PREPARE_TEST();
    // Inequality
    Vec rightNeq = this->v1;
    Vec leftNeq = this->v2;
    EXPECT_TRUE(leftNeq != rightNeq);

    Vec rightNeq2 = this->v2;
    Vec leftNeq2 = this->v2;
    EXPECT_FALSE(leftNeq2 != rightNeq2);
}

TYPED_TEST(VectorTests, LessThanOperator) {
    PREPARE_TEST();
    // Less than
    Vec lt = this->v1;
    EXPECT_FALSE(lt < this->v1);

    lt -= Type(100);
    EXPECT_TRUE(lt < this->v1);

    lt = this->v1;
    lt += Type(100);
    EXPECT_FALSE(lt < this->v1);
}

TYPED_TEST(VectorTests, LessThanOrEqualOperator) {
    PREPARE_TEST();
    // Less than or equal
    Vec lte = this->v1;
    EXPECT_TRUE(lte <= this->v1);

    lte -= Type(100);
    EXPECT_TRUE(lte <= this->v1);

    lte = this->v1;
    lte += Type(100);
    EXPECT_FALSE(lte <= this->v1);
}

TYPED_TEST(VectorTests, GreaterThanOperator) {
    PREPARE_TEST();
    // Greater than
    Vec gt = this->v1;
    EXPECT_FALSE(gt > this->v1);

    gt += Type(100);
    EXPECT_TRUE(gt > this->v1);

    gt = this->v1;
    gt -= Type(100);
    EXPECT_FALSE(gt > this->v1);
}

TYPED_TEST(VectorTests, GreaterThanOrEqualOperator) {
    PREPARE_TEST();
    // Greater than or equal
    Vec gte = this->v1;
    EXPECT_TRUE(gte >= this->v1);

    gte += Type(100);
    EXPECT_TRUE(gte >= this->v1);

    gte = this->v1;
    gte -= Type(100);
    EXPECT_FALSE(gte >= this->v1);
}

// =============================================================================================================
// ========================================== Vector Opeartions ================================================
// =============================================================================================================

TYPED_TEST(VectorTests, VectorIsZero) {
    PREPARE_TEST();
    // Zero vector
    Vec zero;
    GLESC::Math::VectorAlgorithms::vectorFill(zero.data, Type());
    EXPECT_TRUE(zero.isZero());

    // Non-zero vector
    Vec nonZero = this->v1;
    EXPECT_FALSE(nonZero.isZero());
}

TYPED_TEST(VectorTests, VectorClamp) {
    PREPARE_TEST();

    TEST_SECTION("Vector clamp with values");
    Type min = Type(1);
    Type max = Type(5);

    this->result = Vec(7);
    this->result = this->result.clamp(min, max);

    this->expected = Vec(7);
    GLESC::Math::VectorAlgorithms::clampWithValues(this->expected.data, min, max, this->expected.data);

    EXPECT_EQ_VEC(this->result, this->expected);

    TEST_SECTION("Vector clamp with vector");
    Vec minVec;
    for (size_t i = 0; i < N; ++i) {
        minVec[i] = Type(i + 1);
    }
    Vec maxVec;
    for (size_t i = 0; i < N; ++i) {
        maxVec[i] = Type(i + 5);
    }

    this->result = this->v1;
    this->result.clamp(minVec, maxVec);

    this->expected = this->v1;
    GLESC::Math::VectorAlgorithms::clampWithVectors(this->expected.data, minVec.data, maxVec.data, this->expected.data);

    EXPECT_EQ_VEC(this->result, this->expected);
}

TYPED_TEST(VectorTests, VectorSum) {
    PREPARE_TEST();

    // Sum
    Type sumVec = this->v1.sum();
    Type expectSumVec = GLESC::Math::VectorAlgorithms::sum(this->v1.data);
    EXPECT_EQ_CUSTOM(sumVec, expectSumVec);
}

TYPED_TEST(VectorTests, Abs) {
    PREPARE_TEST();

    // Give v1 negative values
    Vec abs = -this->v1;
    abs = this->v1.abs();
    EXPECT_EQ_VEC(this->v1.data, abs.data);

    // Give v2 negative values
    abs = -this->v2;
    abs = this->v2.abs();
    EXPECT_EQ_VEC(this->v2.data, abs.data);

    // try with positive values
    abs = this->v1.abs();
    EXPECT_EQ_VEC(this->v1.data, abs.data);
}

TYPED_TEST(VectorTests, VectorSwap) {
    PREPARE_TEST();

    // Swap
    Vec swap = this->v1;
    Vec swap2 = this->v2;
    swap.swap(swap2);
    EXPECT_EQ_VEC(swap, this->v2);
    EXPECT_EQ_VEC(swap2, this->v1);
}

TYPED_TEST(VectorTests, VectorDot) {
    PREPARE_TEST();

    // Dot product
    Type dot = this->v1.dot(this->v2);
    Type expectDot = GLESC::Math::VectorAlgorithms::dotProduct(this->v1.data, this->v2.data);
    EXPECT_EQ_CUSTOM(dot, expectDot);
}

TYPED_TEST(VectorTests, VectorDistance) {
    PREPARE_TEST();

    // Distance
    Type distance = this->v1.distance(this->v2);
    Type expectDistance = GLESC::Math::VectorAlgorithms::distance(this->v1.data, this->v2.data);
}

TYPED_TEST(VectorTests, VectorCross) {
    PREPARE_TEST();

    // Cross
    if constexpr (N == 3) {
        // Cross product is only defined for 3D vectors
        Vec cross;
        initVector1(cross);
        Vec cross2;
        initVector2(cross2);
        Vec crossResult = cross.cross(cross2);
        Vec expectCrossResult;
        GLESC::Math::VectorAlgorithms::crossProduct(cross.data, cross2.data, expectCrossResult.data);
        EXPECT_EQ_VEC(crossResult, expectCrossResult);
    }
}

TYPED_TEST(VectorTests, VectorIsOrthogonal) {
    PREPARE_TEST();
    if constexpr (N == 2 || N == 3 || N == 4) {
        // Orthogonal vectors for any dimension N
        Vec orthogonalVec1;
        GLESC::Math::VectorAlgorithms::getOrthogonal(this->v1.data, orthogonalVec1.data);
        // Check if orthogonal
        EXPECT_TRUE(this->v1.isOrthogonal(orthogonalVec1));
    }
}

TYPED_TEST(VectorTests, VectorIsParallel) {
    PREPARE_TEST();

    // Parallel vectors for any dimension N
    Vec parallelVec1, parallelVec2;
    for (size_t i = 0; i < N; ++i) {
        parallelVec1.set(i, Type(i + 1));
        parallelVec2.set(i, Type((i + 1) * 2)); // Scalar multiple of parallelVec1
    }

    // Check if parallel (one vector is a scalar multiple of the other)
    bool isParallel = true;
    const Type scalar = parallelVec2.get(0) / parallelVec1.get(0);
    for (size_t i = 1; i < N; ++i) {
        if (parallelVec2.get(i) / parallelVec1.get(i) != scalar) {
            isParallel = false;
            break;
        }
    }

    EXPECT_TRUE(isParallel);
}


TYPED_TEST(VectorTests, VectorGetOrthogonal) {
    PREPARE_TEST();

    if constexpr (N == 2 || N == 3 || N == 4) {
        // Orthogonal
        Vec orthogonal;
        initVector1(orthogonal);
        Vec orthogonalResult = orthogonal.getOrthogonal();
        bool isOrthogonal = orthogonalResult.dot(orthogonal) == Type();
        EXPECT_TRUE(isOrthogonal);
    }
}

TYPED_TEST(VectorTests, VectorLenght) {
    PREPARE_TEST();

    // Length
    Type length = this->v1.length();
    Type expectLength = GLESC::Math::VectorAlgorithms::length(this->v1.data);
    EXPECT_EQ_CUSTOM(length, expectLength);


    // Length squared
    Type lengthSquared = this->v1.lengthSquared();
    Type expectLengthSquared = GLESC::Math::VectorAlgorithms::lengthSquared(this->v1.data);
    EXPECT_EQ_CUSTOM(lengthSquared, expectLengthSquared);
}

TYPED_TEST(VectorTests, VectorIsHomogenous) {
    PREPARE_TEST();
    VectorT<Type, N - 1> dehomogenized;
    GLESC::Math::VectorAlgorithms::dehomogenize(this->v1.data, dehomogenized.data);
    EXPECT_FALSE(dehomogenized.isHomogeneous());


    VectorT<Type, N + 1> homogenized;
    GLESC::Math::VectorAlgorithms::homogenize(this->v1.data, homogenized.data);
    EXPECT_TRUE(homogenized.isHomogeneous());
}

TYPED_TEST(VectorTests, VectorHomogenize) {
    PREPARE_TEST();
    // Test homogenizing a vector
    VectorT<Type, N - 1> toHomogenize;
    initVector1(toHomogenize);
    Vec homogenized = toHomogenize.homogenize();
    Vec expectedHomogenized;
    GLESC::Math::VectorAlgorithms::homogenize(toHomogenize.data, expectedHomogenized.data);
    EXPECT_EQ_VEC(homogenized, expectedHomogenized);
}

TYPED_TEST(VectorTests, VectorDehomogenous) {
    PREPARE_TEST();
    // Test dehomogenizing a vector
    VectorT<Type, N - 1> dehomogenized;
    dehomogenized = this->v1.dehomogenize();

    VectorT<Type, N - 1> expectedDehomogenized;
    GLESC::Math::VectorAlgorithms::dehomogenize(this->v1.data, expectedDehomogenized.data);
    EXPECT_EQ_VEC(dehomogenized, expectedDehomogenized);
}

TYPED_TEST(VectorTests, VectorNormalize) {
    PREPARE_TEST();

    // Normalize
    Vec normalize;
    initVector1(normalize);
    normalize = normalize.normalize();
    Type normalizeLength = normalize.length();

    if constexpr (!std::is_integral_v<Type>)
        EXPECT_EQ_CUSTOM(normalizeLength, Type(1));
    else // If it's integral, it should be 0 due to truncation
        EXPECT_EQ_CUSTOM(normalizeLength, Type(0));
}

TYPED_TEST(VectorTests, VectorSize) {
    PREPARE_TEST();

    // Size
    EXPECT_EQ_CUSTOM(this->v1.size(), N);
}

TYPED_TEST(VectorTests, VectorMultiple) {
    PREPARE_TEST();

    // Vectors are the same
    Vec multiple;
    initVector1(multiple);
    Vec multiple2;
    initVector2(multiple2);
    EXPECT_TRUE(multiple.isMultipleOf(multiple)); // A vector is always a multiple of itself

    // Vectors are multiple
    // Create a vector that is a known multiple of the initial vector
    Vec multiple3;
    const Type scalarMultiple = Type(2); // Example scalar multiple
    for (size_t i = 0; i < N; ++i) {
        multiple3.set(i, this->v1.get(i) * scalarMultiple);
    }
    EXPECT_TRUE(multiple3.isMultipleOf(this->v1));

    // Vectors are not multiple
    Vec notMultiple;
    initVector1(notMultiple);
    notMultiple.set(0, notMultiple.get(0) + Type(1)); // This change makes it not a multiple of v1
    EXPECT_FALSE(notMultiple.isMultipleOf(this->v1));
}


TYPED_TEST(VectorTests, VectorCollinearityOperator) {
    PREPARE_TEST();
    if constexpr (N == 3) {
        // Two vectors are always collinear
        std::vector<Vec> collinearVecs = {this->v2};
        EXPECT_TRUE(this->v1.isCollinear(collinearVecs));
        // Collinear vectors with a scalar multiple
        collinearVecs.clear();
        collinearVecs.push_back(this->v1 * Type(10));
        collinearVecs.push_back(this->v1 * Type(-20));
        collinearVecs.push_back(this->v1 * Type(0.33));
        EXPECT_TRUE(this->v1.isCollinear(collinearVecs));

        // Two equal, one different, they are collinear
        Vec nonCollinear = this->v1;
        nonCollinear[0] += Type(1); // Make it different
        std::vector<Vec> nonCollinearVecs = {nonCollinear, this->v1};
        EXPECT_TRUE(this->v1.isCollinear(nonCollinearVecs));

        // 3 vectors, all different, not collinear
        Vec nonCollinear2 = this->v1;
        Vec nonCollinear3 = this->v1;
        nonCollinear2[0] += Type(1);
        nonCollinear3[0] += Type(2);
        nonCollinear3[1] += Type(6);
        std::vector<Vec> nonCollinearVecs2 = {nonCollinear2, nonCollinear3};
        EXPECT_FALSE(this->v1.isCollinear(nonCollinearVecs2));
    }
}

TYPED_TEST(VectorTests, VectorToString) {
    PREPARE_TEST();
    // To String
    std::string toString = this->v1.toString();
    std::string expectToString = "[";
    for (size_t i = 0; i < N; ++i) {
        expectToString += std::to_string(generateNextValue1<Type>(i));
        if (i != N - 1)
            expectToString += ", ";
    }
    expectToString += "]";
    EXPECT_EQ(toString, expectToString);
}
#endif
