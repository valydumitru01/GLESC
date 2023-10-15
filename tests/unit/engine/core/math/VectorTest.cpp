/******************************************************************************
 * @file   VectorTest.cpp
 * @author Valentin Dumitru
 * @date   2023-10-06
 * @brief  @todo Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include <gtest/gtest.h>
#include "engine/core/math/Math.h"
#include "engine/core/math/Vector.h"


using namespace GLESC::Math;
// ------------------------ Constructor Tests ------------------------ //
TEST(VectorTests, DefaultConstructor) {
    // Vec<int, 1> vec2(1); // Should not compile, 1D vectors are not supported
    // Vec<2, int> vec2(1); // Should not compile, parameters are in the wrong order
    Vec<Vec<int, 2>, 2> vec2X2(Vec<int, 2>(1, 2), Vec<int, 2>(3, 4));
    EXPECT_EQ(vec2X2[0][0], 1);
    EXPECT_EQ(vec2X2[0][1], 2);
    EXPECT_EQ(vec2X2[1][0], 3);
    EXPECT_EQ(vec2X2[1][1], 4);
    
    Vec<int, 2> vecI;
    EXPECT_EQ(vecI[0], 0);
    EXPECT_EQ(vecI[1], 0);
    
    Vec<float, 3> vecF;
    EXPECT_EQ(vecF[0], 0);
    EXPECT_EQ(vecF[1], 0);
    EXPECT_EQ(vecF[2], 0);
    
    Vec<size_t, 4> vecSt;
    EXPECT_EQ(vecSt[0], 0);
    EXPECT_EQ(vecSt[1], 0);
    EXPECT_EQ(vecSt[2], 0);
    EXPECT_EQ(vecSt[3], 0);
}

TEST(VectorTests, ParametrizedConstructor) {
    Vec<Vec<int, 2>, 2> vec2X2(Vec<int, 2>(1, 2), Vec<int, 2>(3, 4));
    EXPECT_EQ(vec2X2[0][0], 1);
    EXPECT_EQ(vec2X2[0][1], 2);
    EXPECT_EQ(vec2X2[1][0], 3);
    EXPECT_EQ(vec2X2[1][1], 4);
    
    Vec<int, 2> vecI(1, 2);
    EXPECT_EQ(vecI[0], 1);
    EXPECT_EQ(vecI[1], 2);
    
    Vec<float, 3> vecF(1.0, 2.0, 3.0);
    EXPECT_EQ(vecF[0], 1);
    EXPECT_EQ(vecF[1], 2);
    EXPECT_EQ(vecF[2], 3);
    
    Vec<size_t, 4> vecSt(1, 2, 3, 4);
    EXPECT_EQ(vecSt[0], 1);
    EXPECT_EQ(vecSt[1], 2);
    EXPECT_EQ(vecSt[2], 3);
    EXPECT_EQ(vecSt[3], 4);
}

TEST(VectorTests, CopyConstructor) {
    Vec<Vec<int, 2>, 2> vec2X2(Vec<int, 2>(1, 2), Vec<int, 2>(3, 4));
    Vec<Vec<int, 2>, 2> vec2X22(vec2X2); // NOLINT
    EXPECT_EQ(vec2X22[0][0], 1);
    EXPECT_EQ(vec2X22[0][1], 2);
    EXPECT_EQ(vec2X22[1][0], 3);
    EXPECT_EQ(vec2X22[1][1], 4);
    
    Vec<int, 2> vecI(1, 2);
    Vec<int, 2> vecI2(vecI); // NOLINT
    EXPECT_EQ(vecI, vecI2);
    
    Vec<float, 3> vecF(1.0, 2.0, 3.0);
    Vec<float, 3> vecF2(vecF); // NOLINT
    EXPECT_EQ(vecF, vecF2);
    
    Vec<size_t, 4> vecSt(1, 2, 3, 4);
    Vec<size_t, 4> vecSt2(vecSt); // NOLINT
    EXPECT_EQ(vecSt, vecSt2);
}

TEST(VectorTests, MoveConstructor) {
    Vec<Vec<int, 2>, 2> vec2X2(Vec<int, 2>(1, 2), Vec<int, 2>(3, 4));
    Vec<Vec<int, 2>, 2> vec2X22(std::move(vec2X2));
    EXPECT_EQ(vec2X22[0][0], 1);
    EXPECT_EQ(vec2X22[0][1], 2);
    EXPECT_EQ(vec2X22[1][0], 3);
    EXPECT_EQ(vec2X22[1][1], 4);
    
    Vec<int, 2> vecI(1, 2); // Becomes invalid after move (undefined behavior)
    Vec<int, 2> vecI2(std::move(vecI));
    EXPECT_EQ(vecI2[0], 1);
    EXPECT_EQ(vecI2[1], 2);
    
    Vec<float, 3> vecF(1.0, 2.0, 3.0); // Becomes invalid after move (undefined behavior)
    Vec<float, 3> vecF2(std::move(vecF));
    EXPECT_EQ(vecF2[0], 1);
    EXPECT_EQ(vecF2[1], 2);
    EXPECT_EQ(vecF2[2], 3);
    
    Vec<size_t, 4> vecSt(1, 2, 3, 4); // Becomes invalid after move (undefined behavior)
    Vec<size_t, 4> vecSt2(std::move(vecSt));
    EXPECT_EQ(vecSt2[0], 1);
    EXPECT_EQ(vecSt2[1], 2);
    EXPECT_EQ(vecSt2[2], 3);
    EXPECT_EQ(vecSt2[3], 4);
}

// ------------------------ Access Tests ------------------------ //

TEST(VectorTest, AccessOperator) {
    Vec<Vec<int, 2>, 2> vec2X2(Vec<int, 2>(1, 2), Vec<int, 2>(3, 4));
    EXPECT_EQ(vec2X2[0][0], 1);
    EXPECT_EQ(vec2X2[0][1], 2);
    EXPECT_EQ(vec2X2[1][0], 3);
    EXPECT_EQ(vec2X2[1][1], 4);
    
    Vec<int, 2> vecI(1, 2);
    EXPECT_EQ(vecI[0], 1);
    EXPECT_EQ(vecI[1], 2);
    
    Vec<float, 3> vecF(1.0, 2.0, 3.0);
    EXPECT_EQ(vecF[0], 1);
    EXPECT_EQ(vecF[1], 2);
    EXPECT_EQ(vecF[2], 3);
    
    Vec<size_t, 4> vecSt(1, 2, 3, 4);
    EXPECT_EQ(vecSt[0], 1);
    EXPECT_EQ(vecSt[1], 2);
    EXPECT_EQ(vecSt[2], 3);
    EXPECT_EQ(vecSt[3], 4);
}

TEST(VectorTest, ConstAccessOperator) {
    const Vec<Vec<int, 2>, 2> vec2X2(Vec<int, 2>(1, 2), Vec<int, 2>(3, 4));
    EXPECT_EQ(vec2X2[0][0], 1);
    EXPECT_EQ(vec2X2[0][1], 2);
    EXPECT_EQ(vec2X2[1][0], 3);
    EXPECT_EQ(vec2X2[1][1], 4);
    
    const Vec<int, 2> vecI(1, 2);
    EXPECT_EQ(vecI[0], 1);
    EXPECT_EQ(vecI[1], 2);
    
    const Vec<float, 3> vecF(1.0, 2.0, 3.0);
    EXPECT_EQ(vecF[0], 1);
    EXPECT_EQ(vecF[1], 2);
    EXPECT_EQ(vecF[2], 3);
    
    const Vec<size_t, 4> vecSt(1, 2, 3, 4);
    EXPECT_EQ(vecSt[0], 1);
    EXPECT_EQ(vecSt[1], 2);
    EXPECT_EQ(vecSt[2], 3);
    EXPECT_EQ(vecSt[3], 4);
}

TEST(VectorTest, Getter) {
    Vec<Vec<int, 2>, 2> vec2X2(Vec<int, 2>(1, 2), Vec<int, 2>(3, 4));
    auto expected1 = Vec<int, 2>(1, 2);
    auto expected2 = Vec<int, 2>(3, 4);
    EXPECT_EQ(vec2X2.getX(), expected1);
    EXPECT_EQ(vec2X2.getY(), expected2);
    
    Vec<int, 2> vecI(1, 2);
    EXPECT_EQ(vecI.getX(), 1);
    EXPECT_EQ(vecI.getY(), 2);
    
    Vec<float, 3> vecF(1.0, 2.0, 3.0);
    EXPECT_EQ(vecF.getX(), 1);
    EXPECT_EQ(vecF.getY(), 2);
    EXPECT_EQ(vecF.getZ(), 3);
    
    Vec<size_t, 4> vecSt(1, 2, 3, 4);
    EXPECT_EQ(vecSt.getX(), 1);
    EXPECT_EQ(vecSt.getY(), 2);
    EXPECT_EQ(vecSt.getZ(), 3);
    EXPECT_EQ(vecSt.getW(), 4);
}

TEST(VectorTest, ShortGetter) {
    Vec<Vec<int, 2>, 2> vec2X2(Vec<int, 2>(1, 2), Vec<int, 2>(3, 4));
    auto expected1 = Vec<int, 2>(1, 2);
    auto expected2 = Vec<int, 2>(3, 4);
    EXPECT_EQ(vec2X2.x(), expected1);
    EXPECT_EQ(vec2X2.y(), expected2);
    
    Vec<int, 2> vecI(1, 2);
    EXPECT_EQ(vecI.x(), 1);
    EXPECT_EQ(vecI.y(), 2);
    
    Vec<float, 3> vecF(1.0, 2.0, 3.0);
    EXPECT_EQ(vecF.x(), 1);
    EXPECT_EQ(vecF.y(), 2);
    EXPECT_EQ(vecF.z(), 3);
    
    Vec<size_t, 4> vecSt(1, 2, 3, 4);
    EXPECT_EQ(vecSt.x(), 1);
    EXPECT_EQ(vecSt.y(), 2);
    EXPECT_EQ(vecSt.z(), 3);
    EXPECT_EQ(vecSt.w(), 4);
    
    // vecI.z(); // Should not compile
    // vecI.w(); // Should not compile (only for 4D vectors)
    
}

TEST(VectorTest, Setter){
    Vec<Vec<int, 2>, 2> vec2X2(Vec<int, 2>(1, 2), Vec<int, 2>(3, 4));
    vec2X2.setX(Vec<int, 2>(3, 4));
    vec2X2.setY(Vec<int, 2>(1, 2));
    auto expected1 = Vec<int, 2>(3, 4);
    auto expected2 = Vec<int, 2>(1, 2);
    EXPECT_EQ(vec2X2.getX(), expected1);
    EXPECT_EQ(vec2X2.getY(), expected2);
    
    Vec<int, 2> vecI(1, 2);
    vecI.setX(3);
    vecI.setY(4);
    EXPECT_EQ(vecI.getX(), 3);
    EXPECT_EQ(vecI.getY(), 4);
    
    Vec<float, 3> vecF(1.0, 2.0, 3.0);
    vecF.setX(3);
    vecF.setY(4);
    vecF.setZ(5);
    EXPECT_EQ(vecF.getX(), 3);
    EXPECT_EQ(vecF.getY(), 4);
    EXPECT_EQ(vecF.getZ(), 5);
    
    Vec<size_t, 4> vecSt(1, 2, 3, 4);
    vecSt.setX(3);
    vecSt.setY(4);
    vecSt.setZ(5);
    vecSt.setW(6);
    EXPECT_EQ(vecSt.getX(), 3);
    EXPECT_EQ(vecSt.getY(), 4);
    EXPECT_EQ(vecSt.getZ(), 5);
    EXPECT_EQ(vecSt.getW(), 6);
}

// ------------------------ Operator Tests ------------------------ //

TEST(VectorTest, AssignmentOperator) {
    Vec<Vec<int, 2>, 2> vec2X2(Vec<int, 2>(1, 2), Vec<int, 2>(3, 4));
    Vec<Vec<int, 2>, 2> vec2X22;
    vec2X22 = vec2X2;
    EXPECT_EQ(vec2X22[0][0], 1);
    EXPECT_EQ(vec2X22[0][1], 2);
    EXPECT_EQ(vec2X22[1][0], 3);
    EXPECT_EQ(vec2X22[1][1], 4);
    
    Vec<int, 2> vecI(1, 2);
    Vec<int, 2> vecI2;
    vecI2 = vecI;
    EXPECT_EQ(vecI2[0], 1);
    EXPECT_EQ(vecI2[1], 2);
    
    EXPECT_EQ(vecI[0], 1);
    EXPECT_EQ(vecI[1], 2);
    
    Vec<float, 3> vecF(1.0, 2.0, 3.0);
    Vec<float, 3> vecF2;
    vecF2 = vecF;
    EXPECT_EQ(vecF2[0], 1);
    EXPECT_EQ(vecF2[1], 2);
    EXPECT_EQ(vecF2[2], 3);
    
    EXPECT_EQ(vecF[0], 1);
    EXPECT_EQ(vecF[1], 2);
    EXPECT_EQ(vecF[2], 3);
    
    Vec<size_t, 4> vecSt(1, 2, 3, 4);
    Vec<size_t, 4> vecSt2;
    vecSt2 = vecSt;
    EXPECT_EQ(vecSt2[0], 1);
    EXPECT_EQ(vecSt2[1], 2);
    EXPECT_EQ(vecSt2[2], 3);
    EXPECT_EQ(vecSt2[3], 4);
    
    EXPECT_EQ(vecSt[0], 1);
    EXPECT_EQ(vecSt[1], 2);
    EXPECT_EQ(vecSt[2], 3);
    EXPECT_EQ(vecSt[3], 4);
}

TEST(VectorTest, MoveAssignmentOperator) {
    // Becomes invalid after move (undefined behavior)
    Vec<Vec<int, 2>, 2> vec2X2(Vec<int, 2>(1, 2), Vec<int, 2>(3, 4));
    Vec<Vec<int, 2>, 2> vec2X22;
    vec2X22 = std::move(vec2X2);
    EXPECT_EQ(vec2X22[0][0], 1);
    EXPECT_EQ(vec2X22[0][1], 2);
    EXPECT_EQ(vec2X22[1][0], 3);
    EXPECT_EQ(vec2X22[1][1], 4);
    
    Vec<int, 2> vecI(1, 2); // Becomes invalid after move (undefined behavior)
    Vec<int, 2> vecI2;
    vecI2 = std::move(vecI);
    EXPECT_EQ(vecI2[0], 1);
    EXPECT_EQ(vecI2[1], 2);
    
    Vec<float, 3> vecF(1.0, 2.0, 3.0); // Becomes invalid after move (undefined behavior)
    Vec<float, 3> vecF2;
    vecF2 = std::move(vecF);
    EXPECT_EQ(vecF2[0], 1);
    EXPECT_EQ(vecF2[1], 2);
    EXPECT_EQ(vecF2[2], 3);
    
    Vec<size_t, 4> vecSt(1, 2, 3, 4); // Becomes invalid after move (undefined behavior)
    Vec<size_t, 4> vecSt2;
    vecSt2 = std::move(vecSt);
    EXPECT_EQ(vecSt2[0], 1);
    EXPECT_EQ(vecSt2[1], 2);
    EXPECT_EQ(vecSt2[2], 3);
    EXPECT_EQ(vecSt2[3], 4);
}

TEST(VectorTest, AdditionOperator) {
    Vec<Vec<int, 2>, 2> vec2X2(Vec<int, 2>(1, 2), Vec<int, 2>(3, 4));
    Vec<Vec<int, 2>, 2> vec2X22(Vec<int, 2>(1, 2), Vec<int, 2>(3, 4));
    Vec<Vec<int, 2>, 2> result2x2 = vec2X2 + vec2X22;
    EXPECT_EQ(result2x2[0][0], 2);
    EXPECT_EQ(result2x2[0][1], 4);
    EXPECT_EQ(result2x2[1][0], 6);
    EXPECT_EQ(result2x2[1][1], 8);
    
    Vec<int, 2> vecI(1, 2);
    Vec<int, 2> vecI2(1, 2);
    Vec<int, 2> result = vecI + vecI2;
    EXPECT_EQ(result[0], 2);
    EXPECT_EQ(result[1], 4);
    
    Vec<float, 3> vecF(1.0, 2.0, 3.0);
    Vec<float, 3> vecF2(1.0, 2.0, 3.0);
    Vec<float, 3> resultF = vecF + vecF2;
    EXPECT_EQ(resultF[0], 2);
    EXPECT_EQ(resultF[1], 4);
    EXPECT_EQ(resultF[2], 6);
    
    Vec<size_t, 4> vecSt(1, 2, 3, 4);
    Vec<size_t, 4> vecSt2(1, 2, 3, 4);
    Vec<size_t, 4> resultSt = vecSt + vecSt2;
    EXPECT_EQ(resultSt[0], 2);
    EXPECT_EQ(resultSt[1], 4);
    EXPECT_EQ(resultSt[2], 6);
    EXPECT_EQ(resultSt[3], 8);
    
    // A harder one
    Vec<size_t, 4> vecSt3(333, 222, 111, 444);
    Vec<size_t, 4> vecSt4(444, 111, 222, 333);
    Vec<size_t, 4> resultSt2 = vecSt3 + vecSt4;
    EXPECT_EQ(resultSt2[0], 777);
    EXPECT_EQ(resultSt2[1], 333);
    EXPECT_EQ(resultSt2[2], 333);
    EXPECT_EQ(resultSt2[3], 777);
}

TEST(VectorTest, SubtractionOperator) {
    Vec<Vec<int, 2>, 2> vec2X2(Vec<int, 2>(1, 2), Vec<int, 2>(3, 4));
    Vec<Vec<int, 2>, 2> vec2X22(Vec<int, 2>(1, 2), Vec<int, 2>(3, 4));
    Vec<Vec<int, 2>, 2> result2x2 = vec2X2 - vec2X22;
    EXPECT_EQ(result2x2[0][0], 0);
    EXPECT_EQ(result2x2[0][1], 0);
    EXPECT_EQ(result2x2[1][0], 0);
    EXPECT_EQ(result2x2[1][1], 0);
    
    Vec<int, 2> vecI(1, 2);
    Vec<int, 2> vecI2(1, 2);
    Vec<int, 2> result = vecI - vecI2;
    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[1], 0);
    
    Vec<float, 3> vecF(1.0, 2.0, 3.0);
    Vec<float, 3> vecF2(1.0, 2.0, 3.0);
    Vec<float, 3> resultF = vecF - vecF2;
    EXPECT_EQ(resultF[0], 0);
    EXPECT_EQ(resultF[1], 0);
    EXPECT_EQ(resultF[2], 0);
    
    Vec<size_t, 4> vecSt(1, 2, 3, 4);
    Vec<size_t, 4> vecSt2(1, 2, 3, 4);
    Vec<size_t, 4> resultSt = vecSt - vecSt2;
    EXPECT_EQ(resultSt[0], 0);
    EXPECT_EQ(resultSt[1], 0);
    EXPECT_EQ(resultSt[2], 0);
    EXPECT_EQ(resultSt[3], 0);
    
    // A harder one
    Vec<size_t, 4> vecSt3(333, 222, 111, 444);
    Vec<size_t, 4> vecSt4(444, 111, 222, 333);
    Vec<size_t, 4> resultSt2 = vecSt3 - vecSt4;
    EXPECT_EQ(resultSt2[0], -111);
    EXPECT_EQ(resultSt2[1], 111);
    EXPECT_EQ(resultSt2[2], -111);
    EXPECT_EQ(resultSt2[3], 111);
}


TEST(VectorTest, MultiplicationOperator) {
    Vec<Vec<int, 2>, 2> vec2X2(Vec<int, 2>(1, 2), Vec<int, 2>(3, 4));
    Vec<Vec<int, 2>, 2> vec2X22(Vec<int, 2>(1, 2), Vec<int, 2>(3, 4));
    Vec<Vec<int, 2>, 2> result2x2 = vec2X2 * vec2X22;
    EXPECT_EQ(result2x2[0][0], 1);
    EXPECT_EQ(result2x2[0][1], 4);
    EXPECT_EQ(result2x2[1][0], 9);
    EXPECT_EQ(result2x2[1][1], 16);
    
    Vec<int, 2> vecI(1, 2);
    Vec<int, 2> vecI2(1, 2);
    Vec<int, 2> result = vecI * vecI2;
    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 4);
    
    Vec<float, 3> vecF(1.0, 2.0, 3.0);
    Vec<float, 3> vecF2(1.0, 2.0, 3.0);
    Vec<float, 3> resultF = vecF * vecF2;
    EXPECT_EQ(resultF[0], 1);
    EXPECT_EQ(resultF[1], 4);
    EXPECT_EQ(resultF[2], 9);
    
    Vec<size_t, 4> vecSt(1, 2, 3, 4);
    Vec<size_t, 4> vecSt2(1, 2, 3, 4);
    Vec<size_t, 4> resultSt = vecSt * vecSt2;
    EXPECT_EQ(resultSt[0], 1);
    EXPECT_EQ(resultSt[1], 4);
    EXPECT_EQ(resultSt[2], 9);
    EXPECT_EQ(resultSt[3], 16);
    
    // A harder one
    Vec<size_t, 4> vecSt3(333, 222, 111, 444);
    Vec<size_t, 4> vecSt4(3, 2, 3, 4);
    Vec<size_t, 4> resultSt2 = vecSt3 * vecSt4;
    EXPECT_EQ(resultSt2[0], 999);
    EXPECT_EQ(resultSt2[1], 444);
    EXPECT_EQ(resultSt2[2], 333);
    EXPECT_EQ(resultSt2[3], 1776);
}

TEST(VectorTest, DivisionOperator) {
    Vec<Vec<int, 2>, 2> vec2X2(Vec<int, 2>(1, 2), Vec<int, 2>(3, 4));
    Vec<Vec<int, 2>, 2> vec2X22(Vec<int, 2>(1, 2), Vec<int, 2>(3, 4));
    Vec<Vec<int, 2>, 2> result2x2 = vec2X2 / vec2X22;
    EXPECT_EQ(result2x2[0][0], 1);
    EXPECT_EQ(result2x2[0][1], 1);
    EXPECT_EQ(result2x2[1][0], 1);
    EXPECT_EQ(result2x2[1][1], 1);
    
    Vec<int, 2> vecI(1, 2);
    Vec<int, 2> vecI2(1, 2);
    Vec<int, 2> result = vecI / vecI2;
    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 1);
    
    Vec<float, 3> vecF(1.0, 2.0, 3.0);
    Vec<float, 3> vecF2(1.0, 2.0, 3.0);
    Vec<float, 3> resultF = vecF / vecF2;
    EXPECT_EQ(resultF[0], 1);
    EXPECT_EQ(resultF[1], 1);
    EXPECT_EQ(resultF[2], 1);
    
    Vec<size_t, 4> vecSt(1, 2, 3, 4);
    Vec<size_t, 4> vecSt2(1, 2, 3, 4);
    Vec<size_t, 4> resultSt = vecSt / vecSt2;
    EXPECT_EQ(resultSt[0], 1);
    EXPECT_EQ(resultSt[1], 1);
    EXPECT_EQ(resultSt[2], 1);
    EXPECT_EQ(resultSt[3], 1);
    
    // A harder one
    Vec<size_t, 4> vecSt3(333, 222, 111, 444);
    Vec<size_t, 4> vecSt4(3, 2, 3, 4);
    Vec<size_t, 4> resultSt2 = vecSt3 / vecSt4;
    EXPECT_EQ(resultSt2[0], 111);
    EXPECT_EQ(resultSt2[1], 111);
    EXPECT_EQ(resultSt2[2], 37);
    EXPECT_EQ(resultSt2[3], 111);
    
    // A harder one
    Vec<double, 2> vecD(333.11, 222.32);
    Vec<double, 2> vecD2(3.32, 2.12);
    Vec<double, 2> resultD = vecD / vecD2;
    EXPECT_TRUE(GLESC::Math::eq(resultD[0], 100.334337));
    EXPECT_TRUE(GLESC::Math::eq(resultD[1], 104.867925));
}



