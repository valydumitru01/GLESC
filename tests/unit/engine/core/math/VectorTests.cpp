#include <gtest/gtest.h>
#include "engine/core/math/Matrix.h"
#include "MathTestHelper.h"

/**
 * @brief Initializes the vector
 * @details Initializes the vector with values:
 * 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, ...
 * @tparam Type
 * @tparam N
 * @param v
 */
template<typename Type, size_t N>
void initVector(Vector<Type, N> &v) {
    for (size_t i = 1; i < N; ++i)
        v.set(i, Type(i+1));
}

/**
 * @brief Initializes the vector
 * @details Initializes the vector with values:
 * 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, ...
 * @tparam Type
 * @tparam N
 * @param v
 */
template<typename Type, size_t N>
void initVector2(Vector<Type, N> &v) {
    for (size_t i = 1; i < N; ++i)
        v.set(i, Type(i * 10));
}

template<typename T, size_t N>
struct VectorType {
    using ValueType = T;
    static const size_t Length = N;
};

template<typename Type>
class VertexTests : public ::testing::Test {
protected:
    VertexTests() = default;
    void SetUp() override {}
    void TearDown() override {}
    Vector<typename Type::ValueType, Type::Length> v1;
    Vector<typename Type::ValueType, Type::Length> v2;
};

using MyTypes = ::testing::Types<
        VectorType<float, 2>,
        VectorType<float, 3>,
        VectorType<float, 4>,
        VectorType<double, 2>,
        VectorType<double, 3>,
        VectorType<double, 4>,
        VectorType<int, 2>,
        VectorType<int, 3>,
        VectorType<int, 4>,
        VectorType<unsigned int, 2>,
        VectorType<unsigned int, 3>,
        VectorType<unsigned int, 4>,
        VectorType<short, 2>,
        VectorType<short, 3>,
        VectorType<short, 4>>;

TYPED_TEST_SUITE(VertexTests, MyTypes);

#define PREPARE_TEST()\
    using Type = typename TypeParam::ValueType; \
    constexpr size_t N = TypeParam::Length;     \
    using Vec = Vector<Type, N>;


TYPED_TEST(VertexTests, Constructors) {
    PREPARE_TEST();
    EXPECT_EQ(this->v1.length(), N);
    EXPECT_EQ(this->v1.size(), TypeParam::Length);
    
}