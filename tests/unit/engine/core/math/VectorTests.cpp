#include <gtest/gtest.h>
#include "engine/core/math/Matrix.h"
#include "MathTestHelper.h"

template<typename T, size_t N>
struct VectorType {
    using ValueType = T;
    static const size_t Length = N;
};

template<typename MyType>
static MyType getExpectedValue1(size_t i) {
    return MyType(i + 1);
}

template<typename MyType>
static MyType getExpectedValue2(size_t i) {
    return MyType(i + 1) * MyType(10);
}

/**
 * @brief Initializes the vector
 * @details Initializes the vector with values:
 * 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, ...
 * @tparam VecType
 * @tparam N
 * @param v
 */
template<typename VecType, size_t N>
inline void initVector(Vector<VecType, N> &v) {
    for (size_t i = 0; i < N; ++i)
        v.set(i, getExpectedValue1<VecType>(i));
}

/**
 * @brief Initializes the vector
 * @details Initializes the vector with values:
 * 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, ...
 * @tparam VecType
 * @tparam N
 * @param v
 */
template<typename VecType, size_t N>
inline void initVector2(Vector<VecType, N> &v) {
    for (size_t i = 0; i < N; ++i)
        v.set(i, getExpectedValue2<VecType>(i));
}

template<typename Type>
class VectorTests : public ::testing::Test {
protected:
    
    VectorTests() = default;
    
    void SetUp() override {
        initVector(this->v1);
        initVector2(this->v2);
    }
    
    void TearDown() override {}
    
    Vector<typename Type::ValueType, Type::Length> v1;
    Vector<typename Type::ValueType, Type::Length> v2;
};

using MyTypes = ::testing::Types<VectorType<float, 2>, VectorType<float, 3>, VectorType<float, 4>,
        VectorType<double, 2>, VectorType<double, 3>, VectorType<double, 4>, VectorType<int, 2>,
        VectorType<int, 3>, VectorType<int, 4>, VectorType<unsigned int, 2>,
        VectorType<unsigned int, 3>, VectorType<unsigned int, 4>, VectorType<short, 2>,
        VectorType<short, 3>, VectorType<short, 4>>;

TYPED_TEST_SUITE(VectorTests, MyTypes);

#define PREPARE_TEST()\
    using Type = typename TypeParam::ValueType; \
    constexpr size_t N = TypeParam::Length;     \
    using Vec = Vector<Type, N>;

TYPED_TEST(VectorTests, Accesors) {
    PREPARE_TEST();
    EXPECT_EQ(this->v1.size(), N);
    for (size_t i = 0; i < N; ++i)
        EXPECT_EQ_CUSTOM(this->v1.get(i), getExpectedValue1<Type>(i));
    for (size_t i = 0; i < N; ++i)
        EXPECT_EQ_CUSTOM(this->v1[i], getExpectedValue1<Type>(i));
    Vec v3;
    initVector(v3);
    if constexpr (N >= 1) {
        EXPECT_EQ_CUSTOM(this->v1.x(), getExpectedValue1<Type>(0));
        EXPECT_EQ_CUSTOM(this->v1.getX(), getExpectedValue1<Type>(0));
        
        v3.x(getExpectedValue1<Type>(0) + Type(1));
        EXPECT_EQ_CUSTOM(v3.x(), getExpectedValue1<Type>(0) + Type(1));
        v3.setX(getExpectedValue1<Type>(0) + Type(2));
        EXPECT_EQ_CUSTOM(v3.x(), getExpectedValue1<Type>(0) + Type(2));
    }
    if constexpr (N >= 2) {
        EXPECT_EQ_CUSTOM(this->v1.y(), getExpectedValue1<Type>(1));
        EXPECT_EQ_CUSTOM(this->v1.getY(), getExpectedValue1<Type>(1));
        
        v3.y(getExpectedValue1<Type>(1) + Type(1));
        EXPECT_EQ_CUSTOM(v3.y(), getExpectedValue1<Type>(1) + Type(1));
        
        v3.setY(getExpectedValue1<Type>(1) + Type(2));
        EXPECT_EQ_CUSTOM(v3.y(), getExpectedValue1<Type>(1) + Type(2));
        
    }
    if constexpr (N >= 3) {
        EXPECT_EQ_CUSTOM(this->v1.z(), getExpectedValue1<Type>(2));
        EXPECT_EQ_CUSTOM(this->v1.getZ(), getExpectedValue1<Type>(2));
        
        v3.z(getExpectedValue1<Type>(2) + Type(1));
        EXPECT_EQ_CUSTOM(v3.z(), getExpectedValue1<Type>(2) + Type(1));
        
        v3.setZ(getExpectedValue1<Type>(2) + Type(2));
        EXPECT_EQ_CUSTOM(v3.z(), getExpectedValue1<Type>(2) + Type(2));
    }
    if constexpr (N >= 4) {
        EXPECT_EQ_CUSTOM(this->v1.w(), getExpectedValue1<Type>(3));
        EXPECT_EQ_CUSTOM(this->v1.getW(), getExpectedValue1<Type>(3));
        
        v3.w(getExpectedValue1<Type>(3) + Type(1));
        EXPECT_EQ_CUSTOM(v3.w(), getExpectedValue1<Type>(3) + Type(1));
        
        v3.setW(getExpectedValue1<Type>(3) + Type(2));
        EXPECT_EQ_CUSTOM(v3.w(), getExpectedValue1<Type>(3) + Type(2));
    }
    
}

TYPED_TEST(VectorTests, Constructors) {
    PREPARE_TEST();
    // Default constructor
    Vec defaultConstruct;
    Vec expectDefaultConstruct;
    for (size_t i = 0; i < N; ++i)
        expectDefaultConstruct.set(i, Type());
    EXPECT_EQ_VEC(defaultConstruct, expectDefaultConstruct);
    
    // Variadic constructor
    if constexpr (N == 2) {
        Vec variadicConstruct(getExpectedValue1<Type>(0), getExpectedValue1<Type>(1));
        EXPECT_EQ_VEC(variadicConstruct, this->v1);
    }
    if constexpr (N == 3) {
        Vec variadicConstruct(getExpectedValue1<Type>(0), getExpectedValue1<Type>(1),
                              getExpectedValue1<Type>(2));
        EXPECT_EQ_VEC(variadicConstruct, this->v1);
    }
    if constexpr (N == 4) {
        Vec variadicConstruct
                (getExpectedValue1<Type>(0), getExpectedValue1<Type>(1), getExpectedValue1<Type>(2),
                 getExpectedValue1<Type>(3));
        EXPECT_EQ_VEC(variadicConstruct, this->v1);
    } // Enough with the variadic constructors, it could go on forever
    
    // Array constructor
    Type arr[N];
    for (size_t i = 0; i < N; ++i)
        arr[i] = getExpectedValue1<Type>(i);
    Vec arrayConstruct(arr);
    EXPECT_EQ_VEC(arrayConstruct, this->v1);
    
    // Initializer list constructor
    if constexpr (N == 2) {
        Vec initListConstruct{getExpectedValue1<Type>(0), getExpectedValue1<Type>(1)};
        EXPECT_EQ_VEC(initListConstruct, this->v1);
    }
    if constexpr (N == 3) {
        Vec initListConstruct{getExpectedValue1<Type>(0), getExpectedValue1<Type>(1),
                              getExpectedValue1<Type>(2)};
        EXPECT_EQ_VEC(initListConstruct, this->v1);
    }
    if constexpr (N == 4) {
        Vec initListConstruct
                {getExpectedValue1<Type>(0), getExpectedValue1<Type>(1), getExpectedValue1<Type>(2),
                 getExpectedValue1<Type>(3)};
        EXPECT_EQ_VEC(initListConstruct, this->v1);
    } // Enough with the initializers, it could go on forever
    
    
    // Fill constructor
    Type fillValue = Type(1);
    Vec fillConstruct(fillValue);
    Vec expectFillConstruct;
    for (size_t i = 0; i < N; ++i)
        expectFillConstruct.set(i, fillValue);
    EXPECT_EQ_VEC(fillConstruct, expectFillConstruct);
    
    // Copy constructor
    Vec copyConstruct;
    initVector(copyConstruct);
    Vec copyConstruct2(copyConstruct);
    EXPECT_EQ_VEC(copyConstruct2, copyConstruct);
    EXPECT_EQ_VEC(copyConstruct2, this->v1); // Must be equal to the initial vector
    
    // Move constructor
    Vec moveConstruct;
    initVector(moveConstruct);
    Vec moveConstruct2(std::move(moveConstruct));
    EXPECT_EQ_VEC(moveConstruct2, this->v1);
}

TYPED_TEST(VectorTests, AssignmentOperators) {
    PREPARE_TEST();
    // Copy assignment
    Vec copyAssign;
    copyAssign = this->v1;
    EXPECT_EQ_VEC(copyAssign, this->v1); // Must be equal to the initial vector
    
    // Move assignment
    Vec moveAssign;
    Vec moveAssign2;
    initVector(moveAssign);
    moveAssign2 = std::move(moveAssign);
    EXPECT_EQ_VEC(moveAssign2, this->v1);
    
    // Array assignment
    Type arr[N];
    for (size_t i = 0; i < N; ++i)
        arr[i] = getExpectedValue1<Type>(i);
    Vec arrayAssign;
    arrayAssign = arr;
    EXPECT_EQ_VEC(arrayAssign, this->v1);
    
    // Initializer list assignment
    if constexpr (N == 2) {
        Vec initListAssign;
        initListAssign = {getExpectedValue1<Type>(0), getExpectedValue1<Type>(1)};
        EXPECT_EQ_VEC(initListAssign, this->v1);
    }
    if constexpr (N == 3) {
        Vec initListAssign;
        initListAssign = {getExpectedValue1<Type>(0), getExpectedValue1<Type>(1),
                          getExpectedValue1<Type>(2)};
        EXPECT_EQ_VEC(initListAssign, this->v1);
    }
    if constexpr (N == 4) {
        Vec initListAssign;
        initListAssign =
                {getExpectedValue1<Type>(0), getExpectedValue1<Type>(1), getExpectedValue1<Type>(2),
                 getExpectedValue1<Type>(3)};
        EXPECT_EQ_VEC(initListAssign, this->v1);
    } // Enough with the initializers, it could go on forever
    
    
    // =============================================================================================
    // In place arithmetic assignment
    
    // Addition assignment with another vector
    Vec addAssign;
    initVector(addAssign);
    addAssign += this->v1;
    Vec expectAddAssign;
    for (size_t i = 0; i < N; ++i)
        expectAddAssign.set(i, getExpectedValue1<Type>(i) * Type(2));
    EXPECT_EQ_VEC(addAssign, expectAddAssign);
    
    // Addition assignment with a scalar
    Vec addAssignScalar;
    initVector(addAssignScalar);
    Type scalarAdd = Type(10);
    addAssignScalar += scalarAdd;
    Vec expectAddAssignScalar;
    for (size_t i = 0; i < N; ++i)
        expectAddAssignScalar.set(i, getExpectedValue1<Type>(i) + scalarAdd);
    EXPECT_EQ_VEC(addAssignScalar, expectAddAssignScalar);
    
    // Subtraction assignment with another vector
    Vec subAssign;
    initVector(subAssign);
    subAssign -= this->v2;
    Vec expectSubAssign;
    for (size_t i = 0; i < N; ++i)
        expectSubAssign.set(i, getExpectedValue1<Type>(i) - getExpectedValue2<Type>(i));
    EXPECT_EQ_VEC(subAssign, expectSubAssign);
    
    // Subtraction assignment with a scalar
    Vec subAssignScalar;
    initVector(subAssignScalar);
    Type scalarSub = Type(10);
    subAssignScalar -= scalarSub;
    Vec expectSubAssignScalar;
    for (size_t i = 0; i < N; ++i)
        expectSubAssignScalar.set(i, getExpectedValue1<Type>(i) - scalarSub);
    EXPECT_EQ_VEC(subAssignScalar, expectSubAssignScalar);
    
    // Multiplication assignment with another vector
    Vec mulAssign;
    initVector(mulAssign);
    mulAssign *= this->v1;
    Vec expectMulAssign;
    for (size_t i = 0; i < N; ++i)
        expectMulAssign.set(i, getExpectedValue1<Type>(i) * getExpectedValue1<Type>(i));
    EXPECT_EQ_VEC(mulAssign, expectMulAssign);
    
    // Multiplication assignment with a scalar
    Vec mulAssignScalar;
    initVector(mulAssignScalar);
    Type scalarMul = Type(10);
    mulAssignScalar *= scalarMul;
    Vec expectMulAssignScalar;
    for (size_t i = 0; i < N; ++i)
        expectMulAssignScalar.set(i, getExpectedValue1<Type>(i) * scalarMul);
    EXPECT_EQ_VEC(mulAssignScalar, expectMulAssignScalar);
    
    // Division assignment with another vector
    Vec divAssign;
    initVector(divAssign);
    divAssign /= this->v1;
    Vec expectDivAssign;
    for (size_t i = 0; i < N; ++i)
        expectDivAssign.set(i, getExpectedValue1<Type>(i) / getExpectedValue1<Type>(i));
    EXPECT_EQ_VEC(divAssign, expectDivAssign);
    
    // Division assignment with a scalar
    Vec divAssignScalar;
    initVector(divAssignScalar);
    Type scalarDiv = Type(10);
    divAssignScalar /= scalarDiv;
    Vec expectDivAssignScalar;
    for (size_t i = 0; i < N; ++i)
        expectDivAssignScalar.set(i, getExpectedValue1<Type>(i) / scalarDiv);
    EXPECT_EQ_VEC(divAssignScalar, expectDivAssignScalar);
}

TYPED_TEST(VectorTests, ArithmeticOperators) {
    PREPARE_TEST();
    
    // Addition with another vector
    Vec add;
    add = this->v1 + this->v2;
    Vec expectAdd;
    for (size_t i = 0; i < N; ++i)
        expectAdd.set(i, getExpectedValue1<Type>(i) + getExpectedValue2<Type>(i));
    EXPECT_EQ_VEC(add, expectAdd);
    
    // Addition with a scalar
    Vec addScalar;
    Type scalarAdd = Type(10);
    addScalar = this->v1 + scalarAdd;
    Vec expectAddScalar;
    for (size_t i = 0; i < N; ++i)
        expectAddScalar.set(i, getExpectedValue1<Type>(i) + scalarAdd);
    EXPECT_EQ_VEC(addScalar, expectAddScalar);
    
    // Subtraction with another vector
    Vec sub;
    sub = this->v1 - this->v2;
    Vec expectSub;
    for (size_t i = 0; i < N; ++i)
        expectSub.set(i, getExpectedValue1<Type>(i) - getExpectedValue2<Type>(i));
    EXPECT_EQ_VEC(sub, expectSub);
    
    // Subtraction with a scalar
    Vec subScalar;
    Type scalarSub = Type(10);
    subScalar = this->v1 - scalarSub;
    Vec expectSubScalar;
    for (size_t i = 0; i < N; ++i)
        expectSubScalar.set(i, getExpectedValue1<Type>(i) - scalarSub);
    EXPECT_EQ_VEC(subScalar, expectSubScalar);
    
    // Unary minus
    Vec unaryMinus;
    unaryMinus = -this->v1;
    Vec expectUnaryMinus;
    for (size_t i = 0; i < N; ++i)
        expectUnaryMinus.set(i, -getExpectedValue1<Type>(i));
    EXPECT_EQ_VEC(unaryMinus, expectUnaryMinus);
    
    // Multiplication with another vector
    Vec mul;
    mul = this->v1 * this->v2;
    Vec expectMul;
    for (size_t i = 0; i < N; ++i)
        expectMul.set(i, getExpectedValue1<Type>(i) * getExpectedValue2<Type>(i));
    EXPECT_EQ_VEC(mul, expectMul);
    
    // Multiplication with a scalar
    Vec mulScalar;
    Type scalarMul = Type(10);
    mulScalar = this->v1 * scalarMul;
    Vec expectMulScalar;
    for (size_t i = 0; i < N; ++i)
        expectMulScalar.set(i, getExpectedValue1<Type>(i) * scalarMul);
    EXPECT_EQ_VEC(mulScalar, expectMulScalar);
    
    // Division with another vector
    Vec div;
    div = this->v1 / this->v2;
    Vec expectDiv;
    for (size_t i = 0; i < N; ++i)
        expectDiv.set(i, getExpectedValue1<Type>(i) / getExpectedValue2<Type>(i));
    EXPECT_EQ_VEC(div, expectDiv);
    
    // Division with a scalar
    Vec divScalar;
    Type scalarDiv = Type(10);
    divScalar = this->v1 / scalarDiv;
    Vec expectDivScalar;
    for (size_t i = 0; i < N; ++i)
        expectDivScalar.set(i, getExpectedValue1<Type>(i) / scalarDiv);
    EXPECT_EQ_VEC(divScalar, expectDivScalar);
}

TYPED_TEST(VectorTests, ComparisonOperators) {
    PREPARE_TEST();
    
    // Equality
    Vec eq;
    initVector(eq);
    EXPECT_TRUE(eq == this->v1);
    
    // Inequality
    Vec neq;
    initVector(neq);
    EXPECT_FALSE(neq != this->v1);
    
    // Less than
    Vec lt;
    initVector(lt);
    EXPECT_FALSE(lt < this->v1);
    
    // Less than or equal
    Vec lte;
    initVector(lte);
    EXPECT_TRUE(lte <= this->v1);
    
    // Greater than
    Vec gt;
    initVector(gt);
    EXPECT_FALSE(gt > this->v1);
    
    // Greater than or equal
    Vec gte;
    initVector(gte);
    EXPECT_TRUE(gte >= this->v1);
}

TYPED_TEST(VectorTests, VectorSwap) {
    PREPARE_TEST();
    
    // Swap
    Vec swap;
    initVector(swap);
    Vec swap2;
    initVector2(swap2);
    swap.swap(swap2);
    EXPECT_EQ_VEC(swap, this->v2);
    EXPECT_EQ_VEC(swap2, this->v1);
}

TYPED_TEST(VectorTests, VectorDot) {
    PREPARE_TEST();
    
    // Dot product
    Type dot = this->v1.dot(this->v2);
    Type expectDot = Type();
    for (size_t i = 0; i < N; ++i)
        expectDot += getExpectedValue1<Type>(i) * getExpectedValue2<Type>(i);
    EXPECT_EQ_CUSTOM(dot, expectDot);
}

TYPED_TEST(VectorTests, VectorCross) {
    PREPARE_TEST();
    
    // Cross
    if constexpr (N == 3) { // Cross product is only defined for 3D vectors
        Vec cross;
        initVector(cross);
        Vec cross2;
        initVector2(cross2);
        Vec crossResult = cross.cross(cross2);
        Vec expectCrossResult;
        expectCrossResult.set(0, getExpectedValue1<Type>(1) * getExpectedValue2<Type>(2) -
                                 getExpectedValue1<Type>(2) * getExpectedValue2<Type>(1));
        expectCrossResult.set(1, getExpectedValue1<Type>(2) * getExpectedValue2<Type>(0) -
                                 getExpectedValue1<Type>(0) * getExpectedValue2<Type>(2));
        expectCrossResult.set(2, getExpectedValue1<Type>(0) * getExpectedValue2<Type>(1) -
                                 getExpectedValue1<Type>(1) * getExpectedValue2<Type>(0));
        EXPECT_EQ_VEC(crossResult, expectCrossResult);
    }
}

TYPED_TEST(VectorTests, VectorIsOrthogonal) {
    PREPARE_TEST();
    
    // Orthogonal vectors for any dimension N
    Vec orthogonalVec1, orthogonalVec2;
    orthogonalVec1.set(0, Type(1));  // First element is 1, rest are 0
    if (N > 1) {
        orthogonalVec2.set(1, Type(1));  // Second element is 1, rest are 0
    }
    
    // Check if orthogonal
    EXPECT_TRUE(orthogonalVec1.isOrthogonal(orthogonalVec2));
    
    // Orthogonal for any dimension N but with non-zero elements and different values
    Vec orthogonalVec3, orthogonalVec4;
    for (size_t i = 0; i < N; ++i) {
        orthogonalVec3.set(i, Type(i + 1));
        orthogonalVec4.set(i, Type((i + 1) * 2));  // Scalar multiple of orthogonalVec3
    }
    
    // Check if orthogonal
    EXPECT_TRUE(orthogonalVec3.isOrthogonal(orthogonalVec4));
}

TYPED_TEST(VectorTests, VectorIsParallel) {
    PREPARE_TEST();
    
    // Parallel vectors for any dimension N
    Vec parallelVec1, parallelVec2;
    for (size_t i = 0; i < N; ++i) {
        parallelVec1.set(i, Type(i + 1));
        parallelVec2.set(i, Type((i + 1) * 2));  // Scalar multiple of parallelVec1
    }
    
    // Check if parallel (one vector is a scalar multiple of the other)
    bool isParallel = true;
    Type scalar = parallelVec2.get(0) / parallelVec1.get(0);
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
        initVector(orthogonal);
        Vec orthogonalResult = orthogonal.getOrthogonal();
        bool isOrthogonal = orthogonalResult.dot(orthogonal) == Type();
        EXPECT_TRUE(isOrthogonal);
    }
}

TYPED_TEST(VectorTests, VectorLenght) {
    PREPARE_TEST();
    
    // Length
    Type length = this->v1.length();
    Type expectLength = Type();
    for (size_t i = 0; i < N; ++i)
        expectLength += getExpectedValue1<Type>(i) * getExpectedValue1<Type>(i);
    expectLength = sqRoot(expectLength);
    EXPECT_EQ_CUSTOM(length, expectLength);
    
    
    // Length squared
    Type lengthSquared = this->v1.lengthSquared();
    Type expectLengthSquared = Type();
    for (size_t i = 0; i < N; ++i)
        expectLengthSquared += getExpectedValue1<Type>(i) * getExpectedValue1<Type>(i);
    EXPECT_EQ_CUSTOM(lengthSquared, expectLengthSquared);
}

TYPED_TEST(VectorTests, VectorHomogenous) {
    PREPARE_TEST();
    
    // Test if the vector is homogeneous when the last element is not 1
    Vec homogeneous;
    initVector(homogeneous);
    homogeneous.set(N - 1, Type(0));
    EXPECT_FALSE(homogeneous.isHomogeneous());
    
    // Test if the vector is homogeneous when the last element is 1
    homogeneous.set(N - 1, Type(1));
    EXPECT_TRUE(homogeneous.isHomogeneous());
    
    // Test homogenizing a vector
    Vector<Type, N - 1> toHomogenize;
    initVector(toHomogenize);
    Vec homogenized = toHomogenize.homogenize();
    Vec expectedHomogenized;
    for (size_t i = 0; i < N - 1; ++i) {
        expectedHomogenized.set(i, toHomogenize.get(i));
    }
    expectedHomogenized.set(N - 1, Type(1));
    EXPECT_EQ_VEC(homogenized, expectedHomogenized);
    
    // Test dehomogenizing a vector
    Vector<Type, N + 1> toDehomogenize;
    initVector(toDehomogenize);
    toDehomogenize.set(N, Type(1)); // Ensure last element is non-zero to avoid division by zero
    Vec dehomogenized = toDehomogenize.dehomogenize();
    Vec expectedDehomogenized;
    for (size_t i = 0; i < N; ++i) {
        expectedDehomogenized.set(i, toDehomogenize.get(i));
    }
    EXPECT_EQ_VEC(dehomogenized, expectedDehomogenized);
}

TYPED_TEST(VectorTests, VectorNormalize) {
    PREPARE_TEST();
    
    // Normalize
    Vec normalize;
    initVector(normalize);
    normalize = normalize.normalize();
    Type normalizeLength = normalize.length();
    // If it's integral, it should be 0 due to truncation
    if constexpr (!std::is_integral_v<Type>)
        EXPECT_EQ_CUSTOM(normalizeLength, Type(1));
    
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
    initVector(multiple);
    Vec multiple2;
    initVector2(multiple2);
    EXPECT_TRUE(multiple.isMultipleOf(multiple)); // A vector is always a multiple of itself
    
    // Vectors are multiple
    // Create a vector that is a known multiple of the initial vector
    Vec multiple3;
    Type scalarMultiple = Type(2); // Example scalar multiple
    for (size_t i = 0; i < N; ++i) {
        multiple3.set(i, this->v1.get(i) * scalarMultiple);
    }
    EXPECT_TRUE(multiple3.isMultipleOf(this->v1));
    
    // Vectors are not multiple
    Vec notMultiple;
    initVector(notMultiple);
    notMultiple.set(0, notMultiple.get(0) + Type(1)); // This change makes it not a multiple of v1
    EXPECT_FALSE(notMultiple.isMultipleOf(this->v1));
}

TYPED_TEST(VectorTests, VectorCollinearityMethod) {
    PREPARE_TEST();
    auto generatePoints = [&](size_t count, bool makeNonCollinear) {
        std::vector<Vec> points;
        for (size_t i = 0; i < count; ++i) {
            Vec point;
            for (size_t j = 0; j < N; ++j) {
                point.set(j, this->v1.get(j) * static_cast<Type>(i + 1));
            }
            if (makeNonCollinear) {
                point.set(0, point.get(0) + Type(1));
            }
            points.push_back(point);
        }
        return points;
    };
    
    size_t minimumNumberOfPointsToTest = 1;
    size_t maximumNumberOfPointsToTest = 10;
    
    // Test all subsets of points for collinearity
    for (size_t count = minimumNumberOfPointsToTest; count <= maximumNumberOfPointsToTest; ++count){
        auto collinearPoints = generatePoints(count, false);
        EXPECT_TRUE(VectorMethods::areCollinear(collinearPoints)) << "Failed at count: " << count;
        
        // Test all subsets of points for non-collinearity
        // Ignore the case where there are only 2 points, since they are always collinear
        if (count > 2){
            auto nonCollinearPoints = generatePoints(count, true);
            EXPECT_FALSE(VectorMethods::areCollinear(nonCollinearPoints))
                                << "Failed at count: " << count;
        }
        
    }
}

TYPED_TEST(VectorTests, VectorCollinearityOperator) {
    PREPARE_TEST();
    
    // Collinear vectors
    Vec collinear;
    initVector(collinear);
    Vec collinear2;
    initVector2(collinear2);
    std::vector<Vec> collinearVecs = {collinear, collinear2};
    EXPECT_TRUE(collinear.isCollinear(collinearVecs));
    
    // Non-collinear vectors
    Vec nonCollinear;
    initVector(nonCollinear);
    nonCollinear.set(0, nonCollinear.get(0) + Type(1)); // This change makes it not a multiple of v1
    Vec nonCollinear2;
    initVector2(nonCollinear2);
    std::vector<Vec> nonCollinearVecs = {nonCollinear, nonCollinear2};
    EXPECT_FALSE(nonCollinear.isCollinear(nonCollinearVecs));
}

TYPED_TEST(VectorTests, VectorToString) {
    PREPARE_TEST();
    // To String
    std::string toString = this->v1.toString();
    std::string expectToString = "[";
    for (size_t i = 0; i < N; ++i) {
        expectToString += std::to_string(getExpectedValue1<Type>(i));
        if (i != N - 1)
            expectToString += ", ";
    }
    expectToString += "]";
    EXPECT_EQ(toString, expectToString);
}
