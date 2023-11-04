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
class VertexTests : public ::testing::Test {
protected:
    
    VertexTests() = default;
    
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

TYPED_TEST_SUITE(VertexTests, MyTypes);

#define PREPARE_TEST()\
    using Type = typename TypeParam::ValueType; \
    constexpr size_t N = TypeParam::Length;     \
    using Vec = Vector<Type, N>;

TYPED_TEST(VertexTests, Accesors) {
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

TYPED_TEST(VertexTests, Constructors) {
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

TYPED_TEST(VertexTests, AssignmentOperators) {
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

TYPED_TEST(VertexTests, ArithmeticOperators){
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

TYPED_TEST(VertexTests, ComparisonOperators){
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

TYPED_TEST(VertexTests, VectorMethods){
    PREPARE_TEST();
    
    // Swap
    Vec swap;
    initVector(swap);
    Vec swap2;
    initVector2(swap2);
    swap.swap(swap2);
    EXPECT_EQ_VEC(swap, this->v2);
    EXPECT_EQ_VEC(swap2, this->v1);
    
    // Dot product
    Type dot = this->v1.dot(this->v2);
    Type expectDot = Type();
    for (size_t i = 0; i < N; ++i)
        expectDot += getExpectedValue1<Type>(i) * getExpectedValue2<Type>(i);
    EXPECT_EQ_CUSTOM(dot, expectDot);
    
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
    
    // Is homogeneous
    Vec homogenous;
    initVector(homogenous);
    homogenous.set(N - 1, Type(0));
    EXPECT_FALSE(homogenous.isHomogeneous());
    homogenous.set(N - 1, Type(1));
    EXPECT_TRUE(homogenous.isHomogeneous());

    // Homogenize
    Vector<Type, N-1> homogenize;
    initVector(homogenize);
    Vector<Type, N> homogenizeExpected;  // Changed to N from N-1
    for (size_t i = 0; i < N - 1; ++i) {
        homogenizeExpected.set(i, getExpectedValue1<Type>(i));
    }
    homogenizeExpected.set(N - 1, Type(1));  // Setting the last element to 1
    EXPECT_EQ_VEC(homogenize.homogenize(), homogenizeExpected);

    // Dehomogenize
    Vector<Type, N+1> nonHomogenize;
    initVector(nonHomogenize);
    Vector<Type, N> nonHomogenizeExpected;  // Changed to N from N+1
    Type w = nonHomogenize.get(N); // Get the last (homogenizing) component

    // Skip the loop if w is zero to avoid division by zero
    if (w != Type(0)) {
        std::cout<< "-----values:";
        for (size_t i = 0; i < N; ++i) {
            nonHomogenizeExpected.set(i, nonHomogenize.get(i) / w);
            
            std::cout << std::setprecision(std::numeric_limits<Type>::max_digits10)
            << nonHomogenize.dehomogenize().get(i) << std::endl;
            
            std::cout << std::setprecision(std::numeric_limits<Type>::max_digits10)
                      << nonHomogenizeExpected.get(i) << std::endl;
        }
    }
    EXPECT_EQ_VEC(nonHomogenize.dehomogenize(), nonHomogenizeExpected);
    
    // Normalize
    Vec normalize;
    initVector(normalize);
    normalize=normalize.normalize();
    Type normalizeLength = normalize.length();
    // If it's integral, it should be 0 due to truncation
    if constexpr (!std::is_integral_v<Type>)
        EXPECT_EQ_CUSTOM(normalizeLength, Type(1));
    // Size
    EXPECT_EQ_CUSTOM(this->v1.size(), N);
    
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