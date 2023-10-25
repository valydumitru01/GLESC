/******************************************************************************
 * @file   MatrixTest.cpp
 * @author Valentin Dumitru
 * @date   2023-10-06
 * @brief  @todo Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#include <gtest/gtest.h>
#include "engine/core/math/Math.h"
#include "engine/core/math/Matrix.h"
#define ASSERT_EQ_F(a,b) \
    ASSERT_NEAR(a,b,GLESC::Math::FLOAT_COMPARISON_EPSILON)
#define ASSERT_EQ_D(a,b) \
    ASSERT_NEAR(a,b,GLESC::Math::DOUBLE_COMPARISON_EPSILON)
TEST(MatrixTests, Constructors) {
    // Default constructor
    Matrix2I matrix;
    ASSERT_EQ(matrix[0][0], 0);
    ASSERT_EQ(matrix[0][1], 0);
    ASSERT_EQ(matrix[1][0], 0);
    ASSERT_EQ(matrix[1][1], 0);
    
    // Diagonal constructor
    Matrix2I matrix2(1);
    ASSERT_EQ(matrix2[0][0], 1);
    ASSERT_EQ(matrix2[0][1], 0);
    ASSERT_EQ(matrix2[1][0], 0);
    ASSERT_EQ(matrix2[1][1], 1);
    
    // Array constructor
    int array[2][2] = {{1, 2},
                       {3, 4}};
    Matrix2I matrix3(array);
    ASSERT_EQ(matrix3[0][0], 1);
    ASSERT_EQ(matrix3[0][1], 2);
    ASSERT_EQ(matrix3[1][0], 3);
    ASSERT_EQ(matrix3[1][1], 4);
    
    // Copy constructor
    Matrix2I matrix4(matrix3);
    ASSERT_EQ(matrix4[0][0], 1);
    ASSERT_EQ(matrix4[0][1], 2);
    ASSERT_EQ(matrix4[1][0], 3);
    ASSERT_EQ(matrix4[1][1], 4);
    
    // Move constructor
    Matrix2I matrix5(std::move(matrix4));
    ASSERT_EQ(matrix5[0][0], 1);
    ASSERT_EQ(matrix5[0][1], 2);
    ASSERT_EQ(matrix5[1][0], 3);
    ASSERT_EQ(matrix5[1][1], 4);
    
    // Initializer list constructor
    Matrix2I matrix6({{1, 2},
                      {3, 4}});
    ASSERT_EQ(matrix6[0][0], 1);
    ASSERT_EQ(matrix6[0][1], 2);
    ASSERT_EQ(matrix6[1][0], 3);
    ASSERT_EQ(matrix6[1][1], 4);
}

TEST(MatrixTests, AssignmentOperators) {
    // Copy assignment
    Matrix2I matrix;
    matrix = Matrix2I({{1, 2},
                       {3, 4}});
    ASSERT_EQ(matrix[0][0], 1);
    ASSERT_EQ(matrix[0][1], 2);
    ASSERT_EQ(matrix[1][0], 3);
    ASSERT_EQ(matrix[1][1], 4);
    
    // Move assignment
    auto tempMat = Matrix2I({{5, 6},
                             {7, 8}});
    matrix = std::move(tempMat);
    ASSERT_EQ(matrix[0][0], 5);
    ASSERT_EQ(matrix[0][1], 6);
    ASSERT_EQ(matrix[1][0], 7);
    ASSERT_EQ(matrix[1][1], 8);
    
    // Self assignment
    matrix = matrix; // NOLINT
    ASSERT_EQ(matrix[0][0], 5);
    ASSERT_EQ(matrix[0][1], 6);
    ASSERT_EQ(matrix[1][0], 7);
    ASSERT_EQ(matrix[1][1], 8);
    
    // Initializer list assignment
    Matrix2I matrix2 = {{1, 2},
                        {3, 4}};
    ASSERT_EQ(matrix2[0][0], 1);
    ASSERT_EQ(matrix2[0][1], 2);
    ASSERT_EQ(matrix2[1][0], 3);
    ASSERT_EQ(matrix2[1][1], 4);
    
    // Initializer incorrect dimensions
    
    ASSERT_DEATH(([] {
        Matrix2I matrix3 = {{1, 2},
                            {3, 4},
                            {5, 6}};
    }()), ".*");
    
    // Add assignment with scalar
    Matrix2I matrix3 = {{1, 2},
                        {3, 4}};
    matrix3 += 1;
    ASSERT_EQ(matrix3[0][0], 2);
    ASSERT_EQ(matrix3[0][1], 3);
    ASSERT_EQ(matrix3[1][0], 4);
    ASSERT_EQ(matrix3[1][1], 5);
    
    
    // Add assignment with matrix
    Matrix2I matrix4 = {{1, 2},
                        {3, 4}};
    matrix4 += Matrix2I({{1, 2},
                         {3, 4}});
    ASSERT_EQ(matrix4[0][0], 2);
    ASSERT_EQ(matrix4[0][1], 4);
    ASSERT_EQ(matrix4[1][0], 6);
    ASSERT_EQ(matrix4[1][1], 8);
    
    // Multiply assignment with scalar
    Matrix2I matrix5 = {{1, 2},
                        {3, 4}};
    matrix5 *= 2;
    ASSERT_EQ(matrix5[0][0], 2);
    ASSERT_EQ(matrix5[0][1], 4);
    ASSERT_EQ(matrix5[1][0], 6);
    ASSERT_EQ(matrix5[1][1], 8);
    
    // Multiply assignment with matrix
    Matrix2I matrix6 = {{1, 2},
                        {3, 4}};
    matrix6 *= Matrix2I({{1, 2},
                         {3, 4}});
    ASSERT_EQ(matrix6[0][0], 1);
    ASSERT_EQ(matrix6[0][1], 4);
    ASSERT_EQ(matrix6[1][0], 9);
    ASSERT_EQ(matrix6[1][1], 16);
    
    // Subtract assignment with scalar
    Matrix2I matrix7 = {{1, 2},
                        {3, 4}};
    matrix7 -= 1;
    ASSERT_EQ(matrix7[0][0], 0);
    ASSERT_EQ(matrix7[0][1], 1);
    ASSERT_EQ(matrix7[1][0], 2);
    ASSERT_EQ(matrix7[1][1], 3);
    
    // Subtract assignment with matrix
    Matrix2I matrix8 = {{1, 2},
                        {3, 4}};
    matrix8 -= Matrix2I({{2, 3},
                         {4, 5}});
    ASSERT_EQ(matrix8[0][0], -1);
    ASSERT_EQ(matrix8[0][1], -1);
    ASSERT_EQ(matrix8[1][0], -1);
    ASSERT_EQ(matrix8[1][1], -1);
    
    // Divide assignment with scalar
    Matrix2I matrix9 = {{2, 4},
                        {6, 8}};
    matrix9 /= 2;
    ASSERT_EQ(matrix9[0][0], 1);
    ASSERT_EQ(matrix9[0][1], 2);
    ASSERT_EQ(matrix9[1][0], 3);
    ASSERT_EQ(matrix9[1][1], 4);
    
    // Divide assignment with matrix
    Matrix2I matrix10 = {{2, 4},
                         {6, 8}};
    matrix10 /= Matrix2I({{2, 4},
                          {6, 8}});
    ASSERT_EQ(matrix10[0][0], 1);
    ASSERT_EQ(matrix10[0][1], 1);
    ASSERT_EQ(matrix10[1][0], 1);
    ASSERT_EQ(matrix10[1][1], 1);
    
    // Division by zero
    Matrix2I matrix11 = {{2, 4},
                         {6, 8}};
    ASSERT_THROW(matrix11 /= Matrix2I({{0, 0},
                                       {0, 0}}), MathException);
    Matrix2I matrix12 = {{2, 4},
                         {6, 8}};
    ASSERT_THROW(matrix12 /= 0, MathException);
}

TEST(MatrixTests, MatrixOperators) {
    // Add with scalar
    Matrix2I matrix = {{1, 2},
                       {3, 4}};
    Matrix2I matrix2 = matrix + 1;
    ASSERT_EQ(matrix2[0][0], 2);
    ASSERT_EQ(matrix2[0][1], 3);
    ASSERT_EQ(matrix2[1][0], 4);
    ASSERT_EQ(matrix2[1][1], 5);
    
    // Add with matrix
    Matrix2I matrix3 = {{1, 2},
                        {3, 4}};
    Matrix2I matrix4 = matrix3 + Matrix2I({{1, 2},
                                           {3, 4}});
    ASSERT_EQ(matrix4[0][0], 2);
    ASSERT_EQ(matrix4[0][1], 4);
    ASSERT_EQ(matrix4[1][0], 6);
    ASSERT_EQ(matrix4[1][1], 8);
    
    // Subtract with scalar
    Matrix2I matrix5 = {{1, 2},
                        {3, 4}};
    Matrix2I matrix6 = matrix5 - 1;
    ASSERT_EQ(matrix6[0][0], 0);
    ASSERT_EQ(matrix6[0][1], 1);
    ASSERT_EQ(matrix6[1][0], 2);
    ASSERT_EQ(matrix6[1][1], 3);
    
    // Subtract with matrix
    Matrix2I matrix7 = {{1, 2},
                        {3, 4}};
    
    Matrix2I matrix8 = matrix7 - Matrix2I({{2, 3},
                                           {4, 5}});
    ASSERT_EQ(matrix8[0][0], -1);
    ASSERT_EQ(matrix8[0][1], -1);
    ASSERT_EQ(matrix8[1][0], -1);
    ASSERT_EQ(matrix8[1][1], -1);
    
    // Multiply with scalar
    Matrix2I matrix9 = {{1, 2},
                        {3, 4}};
    Matrix2I matrix10 = matrix9 * 2;
    ASSERT_EQ(matrix10[0][0], 2);
    ASSERT_EQ(matrix10[0][1], 4);
    ASSERT_EQ(matrix10[1][0], 6);
    ASSERT_EQ(matrix10[1][1], 8);
    
    // Multiply with matrix
    Matrix2I matrix11 = {{1, 2},
                         {3, 4}};
    Matrix2I matrix12 = matrix11 * Matrix2I({{1, 2},
                                             {3, 4}});
    ASSERT_EQ(matrix12[0][0], 7);
    ASSERT_EQ(matrix12[0][1], 10);
    ASSERT_EQ(matrix12[1][0], 15);
    ASSERT_EQ(matrix12[1][1], 22);
    
    // Multiply with vector
    Matrix2I matrix13 = {{1, 2},
                         {3, 4}};
    Vec2I vector = {1, 2};
    Vec2I vector2 = matrix13 * vector;
    ASSERT_EQ(vector2[0], 5);
    ASSERT_EQ(vector2[1], 11);
    
    // Divide with scalar
    Matrix2I matrix14 = {{2, 4},
                         {6, 8}};
    Matrix2I matrix15 = matrix14 / 2;
    ASSERT_EQ(matrix15[0][0], 1);
    ASSERT_EQ(matrix15[0][1], 2);
    ASSERT_EQ(matrix15[1][0], 3);
    ASSERT_EQ(matrix15[1][1], 4);
    
    // Divide with matrix
    Matrix2I matrix16 = {{2, 4},
                         {6, 8}};
    Matrix2I matrix17 = matrix16 / Matrix2I({{2, 4},
                                             {6, 8}});
    ASSERT_EQ(matrix17[0][0], 1);
    ASSERT_EQ(matrix17[0][1], 1);
    ASSERT_EQ(matrix17[1][0], 1);
    ASSERT_EQ(matrix17[1][1], 1);
    
    // Division by zero
    Matrix2I matrix18 = {{2, 4},
                         {6, 8}};
    // Casting to void to avoid warning
    ASSERT_THROW(static_cast<void>(matrix18 / Matrix2I({{0, 0},
                                                        {0, 0}})), MathException);
    Matrix2I matrix19 = {{2, 4},
                         {6, 8}};
    // Casting to void to avoid warning
    ASSERT_THROW(static_cast<void>(matrix19 / 0), MathException);
    
}

TEST(MatrixTests, MatrixFunctions){
    // Determinant
    Matrix2I matrix = {{1, 2},
                       {3, 4}};
    ASSERT_EQ(matrix.determinant(), -2);
    
    Matrix3F matrixDet2 = {{1, 2, 3},
                        {0, 1, 4},
                        {5, 6, 0}};
    ASSERT_EQ(matrixDet2.determinant(), 1);
    
    Matrix4F matrixDet3 = {{1, 2, 3, 4},
                        {0, 1, 4, 5},
                        {5, 6, 0, 7},
                        {8, 9, 10, 0}};
    ASSERT_EQ(matrixDet3.determinant(), -95);
    
    
    
    // Inverse
    Matrix2I matrixInv = {{1, 2},
                        {3, 4}};
    Matrix2I matrixInv2 = matrixInv.inverse();
    ASSERT_EQ(matrixInv2[0][0], -2);
    ASSERT_EQ(matrixInv2[0][1], 1);
    ASSERT_EQ(matrixInv2[1][0], 1);
    ASSERT_EQ(matrixInv2[1][1], 0);
    
    Matrix3F matrixInv3 = {{1, 2, 3},
                           {0, 1, 4},
                           {5, 6, 0}};
    Matrix3F matrixInv4 = matrixInv3.inverse();
    ASSERT_EQ_F(matrixInv4[0][0], -24);
    ASSERT_EQ_F(matrixInv4[0][1], 18);
    ASSERT_EQ_F(matrixInv4[0][2], 5);
    ASSERT_EQ_F(matrixInv4[1][0], 20);
    ASSERT_EQ_F(matrixInv4[1][1], -15);
    ASSERT_EQ_F(matrixInv4[1][2], -4);
    ASSERT_EQ_F(matrixInv4[2][0], -5);
    ASSERT_EQ_F(matrixInv4[2][1], 4);
    ASSERT_EQ_F(matrixInv4[2][2], 1);
    
    Matrix4F matrixInv5 = {{1, 2, 3, 4},
                           {0, 1, 4, 5},
                           {5, 6, 0, 7},
                           {8, 9, 10, 0}};
    Matrix4F matrixInv6 = matrixInv5.inverse();
    ASSERT_EQ_F(matrixInv6[0][0], 9.5);
    ASSERT_EQ_F(matrixInv6[0][1], -8.5);
    ASSERT_EQ_F(matrixInv6[0][2], -1.5);
    ASSERT_EQ_F(matrixInv6[0][3], 1);
    ASSERT_EQ_F(matrixInv6[1][0], -8);
    ASSERT_EQ_F(matrixInv6[1][1], 7);
    ASSERT_EQ_F(matrixInv6[1][2], 1);
    ASSERT_EQ_F(matrixInv6[1][3], 0);
    ASSERT_EQ_F(matrixInv6[2][0], 1.5);
    ASSERT_EQ_F(matrixInv6[2][1], -1.5);
    ASSERT_EQ_F(matrixInv6[2][2], 0.5);
    ASSERT_EQ_F(matrixInv6[2][3], 0);
    
    
    // Transpose
    Matrix2I matrix2 = {{1, 2},
                        {3, 4}};
    Matrix2I matrix3 = matrix2.transpose();
    ASSERT_EQ(matrix3[0][0], 1);
    ASSERT_EQ(matrix3[0][1], 3);
    ASSERT_EQ(matrix3[1][0], 2);
    ASSERT_EQ(matrix3[1][1], 4);
    
    // Minor
    Matrix3I matrix4 = {{1, 2, 3},
                        {4, 5, 6},
                        {7, 8, 9}};
    ASSERT_EQ(matrix4.minor(0, 0), -3);
    ASSERT_EQ(matrix4.minor(0, 1), -6);
    ASSERT_EQ(matrix4.minor(0, 2), -3);
    ASSERT_EQ(matrix4.minor(1, 0), -6);
    ASSERT_EQ(matrix4.minor(1, 1), -12);
    ASSERT_EQ(matrix4.minor(1, 2), -6);
    ASSERT_EQ(matrix4.minor(2, 0), -3);
    
    Matrix4 matrix5 = {{1, 2, 3, 4},
                       {5, 6, 7, 8},
                       {9, 10, 11, 12},
                       {13, 14, 15, 16}};
    ASSERT_EQ(matrix5.minor(0, 0), -60);
    ASSERT_EQ(matrix5.minor(0, 1), -120);
    ASSERT_EQ(matrix5.minor(0, 2), -120);
    ASSERT_EQ(matrix5.minor(0, 3), -60);
    ASSERT_EQ(matrix5.minor(1, 0), -120);
    ASSERT_EQ(matrix5.minor(1, 1), -240);
    ASSERT_EQ(matrix5.minor(1, 2), -240);
    ASSERT_EQ(matrix5.minor(1, 3), -120);
    ASSERT_EQ(matrix5.minor(2, 0), -120);
    ASSERT_EQ(matrix5.minor(2, 1), -240);
    ASSERT_EQ(matrix5.minor(2, 2), -240);
    ASSERT_EQ(matrix5.minor(2, 3), -120);
    ASSERT_EQ(matrix5.minor(3, 0), -60);
    ASSERT_EQ(matrix5.minor(3, 1), -120);
    ASSERT_EQ(matrix5.minor(3, 2), -120);
    ASSERT_EQ(matrix5.minor(3, 3), -60);
    
    // Transpose
    Matrix2I matrix6 = {{1, 2},
                        {3, 4}};
    Matrix2I matrix7 = matrix6.transpose();
    ASSERT_EQ(matrix7, Matrix2I({{1, 3},
                                 {2, 4}}));
    
    Matrix3I matrix8 = {{1, 2, 3},
                        {4, 5, 6},
                        {7, 8, 9}};
    Matrix3I matrix9 = matrix8.transpose();
    ASSERT_EQ(matrix9, Matrix3I({{1, 4, 7},
                                 {2, 5, 8},
                                 {3, 6, 9}}));
    
    // Translate
    Matrix4F matrix10 = Matrix4F(1).translate(Vec3F(1, 2, 3));
    ASSERT_EQ(matrix10, Matrix4F({{1, 0, 0, 1},
                                  {0, 1, 0, 2},
                                  {0, 0, 1, 3},
                                  {0, 0, 0, 1}}));
    
    Matrix3F matrix11 = Matrix3F(1).translate(Vec2F(1, 2));
    ASSERT_EQ(matrix11, Matrix3F({{1, 0, 1},
                                  {0, 1, 2},
                                  {0, 0, 1}}));
    
    // Scale
    Matrix4F matrix12 = Matrix4F(1).scale(Vec3F(1, 2, 3));
    ASSERT_EQ(matrix12, Matrix4F({{1, 0, 0, 0},
                                  {0, 2, 0, 0},
                                  {0, 0, 3, 0},
                                  {0, 0, 0, 1}}));
    
    Matrix3F matrix13 = Matrix3F(1).scale(Vec2F(1, 2));
    ASSERT_EQ(matrix13, Matrix3F({{1, 0, 0},
                                  {0, 2, 0},
                                  {0, 0, 1}}));
    
    // Rotate
    Matrix4F matrix14 = Matrix4F(1).rotate(Vec3F(90, 0, 0));
    ASSERT_EQ(matrix14, Matrix4F({{1, 0, 0, 0},
                                  {0, 0, -1, 0},
                                  {0, 1, 0, 0},
                                  {0, 0, 0, 1}}));
    
    Matrix4F matrix15 = Matrix4F(1).rotate(Vec3F(0, 90, 0));
    ASSERT_EQ(matrix15, Matrix4F({{0, 0, 1, 0},
                                  {0, 1, 0, 0},
                                  {-1, 0, 0, 0},
                                  {0, 0, 0, 1}}));
    
    Matrix4F matrix16 = Matrix4F(1).rotate(Vec3F(0, 0, 90));
    ASSERT_EQ(matrix16, Matrix4F({{0, -1, 0, 0},
                                  {1, 0, 0, 0},
                                  {0, 0, 1, 0},
                                  {0, 0, 0, 1}}));
    
    Matrix3F matrix17 = Matrix3F(1).rotate(90);
    ASSERT_EQ(matrix17, Matrix3F({{0, -1, 0},
                                  {1, 0, 0},
                                  {0, 0, 1}}));
}