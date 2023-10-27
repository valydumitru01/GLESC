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
#include "engine/core/math/Matrix.h"
#include "engine/core/math/Math.h"
#include "MathTestHelper.h"

TEST(MatrixTests, Constructors) {
    // Default constructor
    Matrix2I matrix;
    EXPECT_EQ_MAT(matrix, Matrix2I({{0, 0},
                                    {0, 0}}));
    
    // Diagonal constructor
    Matrix2I matrix2(1);
    EXPECT_EQ_MAT(matrix2, Matrix2I({{1, 0},
                                     {0, 1}}));
    
    // Array constructor
    int array[2][2] = {{1, 2},
                       {3, 4}};
    Matrix2I matrix3(array);
    EXPECT_EQ_MAT(matrix3, Matrix2I({{1, 2},
                                     {3, 4}}));
    
    // Copy constructor
    Matrix2I matrix4(matrix3);
    EXPECT_EQ_MAT(matrix4, Matrix2I({{1, 2},
                                     {3, 4}}));
    
    // Move constructor
    Matrix2I matrix5(std::move(matrix4));
    EXPECT_EQ_MAT(matrix5, Matrix2I({{1, 2},
                                     {3, 4}}));
    
    // Initializer list constructor
    Matrix2I matrix6({{1, 2},
                      {3, 4}});
    EXPECT_EQ_MAT(matrix6, Matrix2I({{1, 2},
                                     {3, 4}}));
}

TEST(MatrixTests, AssignmentOperators) {
    // Copy assignment
    Matrix2I matrix;
    matrix = Matrix2I({{1, 2},
                       {3, 4}});
    EXPECT_EQ_MAT(matrix, Matrix2I({{1, 2},
                                    {3, 4}}));
    
    // Move assignment
    auto tempMat = Matrix2I({{5, 6},
                             {7, 8}});
    matrix = std::move(tempMat);
    EXPECT_EQ_MAT(matrix, Matrix2I({{5, 6},
                                    {7, 8}}));
    
    // Self assignment
    matrix = matrix; // NOLINT
    EXPECT_EQ_MAT(matrix, Matrix2I({{5, 6},
                                    {7, 8}}));
    
    // Initializer list assignment
    Matrix2I matrix2 = {{1, 2},
                        {3, 4}};
    EXPECT_EQ_MAT(matrix2, Matrix2I({{1, 2},
                                     {3, 4}}));
    
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
    EXPECT_EQ_MAT(matrix3, Matrix2I({{2, 3},
                                     {4, 5}}));
    
    
    // Add assignment with matrix
    Matrix2I matrix4 = {{1, 2},
                        {3, 4}};
    matrix4 += Matrix2I({{1, 2},
                         {3, 4}});
    EXPECT_EQ_MAT(matrix4, Matrix2I({{2, 4},
                                     {6, 8}}));
    
    // Multiply assignment with scalar
    Matrix2I matrix5 = {{1, 2},
                        {3, 4}};
    matrix5 *= 2;
    EXPECT_EQ_MAT(matrix5, Matrix2I({{2, 4},
                                     {6, 8}}));
    
    // Multiply assignment with matrix
    Matrix2I matrix6 = {{1, 2},
                        {3, 4}};
    matrix6 *= Matrix2I({{1, 2},
                         {3, 4}});
    EXPECT_EQ_MAT(matrix6, Matrix2I({{1, 4},
                                     {9, 16}}));
    
    // Subtract assignment with scalar
    Matrix2I matrix7 = {{1, 2},
                        {3, 4}};
    matrix7 -= 1;
    EXPECT_EQ_MAT(matrix7, Matrix2I({{0, 1},
                                     {2, 3}}));
    
    // Subtract assignment with matrix
    Matrix2I matrix8 = {{1, 2},
                        {3, 4}};
    matrix8 -= Matrix2I({{2, 3},
                         {4, 5}});
    EXPECT_EQ_MAT(matrix8, Matrix2I({{-1, -1},
                                     {-1, -1}}));
    
    // Divide assignment with scalar
    Matrix2I matrix9 = {{2, 4},
                        {6, 8}};
    matrix9 /= 2;
    EXPECT_EQ_MAT(matrix9, Matrix2I({{1, 2},
                                     {3, 4}}));
    
    // Divide assignment with matrix
    Matrix2I matrix10 = {{2, 4},
                         {6, 8}};
    matrix10 /= Matrix2I({{2, 4},
                          {6, 8}});
    EXPECT_EQ_MAT(matrix10, Matrix2I({{1, 1},
                                      {1, 1}}));
    
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
    EXPECT_EQ_MAT(matrix2, Matrix2I({{2, 3},
                                     {4, 5}}));
    
    // Add with matrix
    Matrix2I matrix3 = {{1, 2},
                        {3, 4}};
    Matrix2I matrix4 = matrix3 + Matrix2I({{1, 2},
                                           {3, 4}});
    EXPECT_EQ_MAT(matrix4, Matrix2I({{2, 4},
                                     {6, 8}}));
    
    // Subtract with scalar
    Matrix2I matrix5 = {{1, 2},
                        {3, 4}};
    Matrix2I matrix6 = matrix5 - 1;
    EXPECT_EQ_MAT(matrix6, Matrix2I({{0, 1},
                                     {2, 3}}));
    
    // Subtract with matrix
    Matrix2I matrix7 = {{1, 2},
                        {3, 4}};
    Matrix2I matrix8 = matrix7 - Matrix2I({{2, 3},
                                           {4, 5}});
    EXPECT_EQ_MAT(matrix8, Matrix2I({{-1, -1},
                                     {-1, -1}}));
    
    // Multiply with scalar
    Matrix2I matrix9 = {{1, 2},
                        {3, 4}};
    Matrix2I matrix10 = matrix9 * 2;
    EXPECT_EQ_MAT(matrix10, Matrix2I({{2, 4},
                                      {6, 8}}));
    // Multiply with matrix
    Matrix2I matrix11 = {{1, 2},
                         {3, 4}};
    Matrix2I matrix12 = matrix11 * Matrix2I({{1, 2},
                                             {3, 4}});
    EXPECT_EQ_MAT(matrix12, Matrix2I({{7,  10},
                                      {15, 22}}));
    
    // Multiply with vector
    Matrix2I matrix13 = {{1, 2},
                         {3, 4}};
    Vec2I vector = {1, 2};
    
    
    
    // Divide with scalar
    Matrix2I matrix14 = {{2, 4},
                         {6, 8}};
    Matrix2I matrix15 = matrix14 / 2;
    EXPECT_EQ_MAT(matrix15, Matrix2I({{1, 2},
                                      {3, 4}}));
    
    // Divide with matrix
    Matrix2I matrix16 = {{2, 4},
                         {6, 8}};
    Matrix2I matrix17 = matrix16 / Matrix2I({{2, 4},
                                             {6, 8}});
    EXPECT_EQ_MAT(matrix17, Matrix2I({{1, 1},
                                      {1, 1}}));
    
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

TEST(MatrixTests, MatrixFunctions) {
    // Determinant
    Matrix2I matrix = {{1, 2},
                       {3, 4}};
    EXPECT_EQ_CUSTOM(matrix.determinant(), -2);
    
    Matrix3F matrixDet2 = {{1, 2, 3},
                           {0, 1, 4},
                           {5, 6, 0}};
    EXPECT_EQ_CUSTOM(matrixDet2.determinant(), 1);
    
    Matrix4F matrixDet3 = {{1, 2, 3,  4},
                           {0, 1, 4,  5},
                           {5, 6, 0,  7},
                           {8, 9, 10, 0}};
    EXPECT_EQ_CUSTOM(matrixDet3.determinant(), -95);
    
    
    
    // Inverse
    Matrix2I matrixInv = {{1, 2},
                          {3, 4}};
    Matrix2I matrixInv2 = matrixInv.inverse();
    EXPECT_EQ_MAT(matrixInv2, Matrix2I({{-2, 1},
                                        {1,  0}}));
    
    Matrix3F matrixInv3 = {{1, 2, 3},
                           {0, 1, 4},
                           {5, 6, 0}};
    Matrix3F matrixInv4 = matrixInv3.inverse();
    EXPECT_EQ_MAT(matrixInv4, Matrix3F({{-24, 18,  5},
                                        {20,  -15, -4},
                                        {-5,  4,   1}}));
    
    Matrix4F matrixInv5 = {{1, 2, 3,  4},
                           {0, 1, 4,  5},
                           {5, 6, 0,  7},
                           {8, 9, 10, 0}};
    Matrix4F matrixInv6 = matrixInv5.inverse();
    EXPECT_EQ_MAT(matrixInv6, Matrix4F({{9.5,  -8.5, -1.5, 1},
                                        {-8,   7,    1,    0},
                                        {1.5,  -1.5, 0.5,  0},
                                        {0.25, 0.25, 0.25, 0}}));
    
    // Transpose
    Matrix2I matrix2 = {{1, 2},
                        {3, 4}};
    Matrix2I matrix3 = matrix2.transpose();
    EXPECT_EQ_MAT(matrix3, Matrix2I({{1, 3},
                                     {2, 4}}));
    
    // Minor
    Matrix4 matrix5 = {{1,  2,  3,  4},
                       {5,  6,  7,  8},
                       {9,  10, 11, 12},
                       {13, 14, 15, 16}};
    EXPECT_EQ_CUSTOM(matrix5.minor(0, 0), -60);
    EXPECT_EQ_CUSTOM(matrix5.minor(0, 1), -120);
    EXPECT_EQ_CUSTOM(matrix5.minor(0, 2), -120);
    EXPECT_EQ_CUSTOM(matrix5.minor(0, 3), -60);
    EXPECT_EQ_CUSTOM(matrix5.minor(1, 0), -120);
    EXPECT_EQ_CUSTOM(matrix5.minor(1, 1), -240);
    EXPECT_EQ_CUSTOM(matrix5.minor(1, 2), -240);
    EXPECT_EQ_CUSTOM(matrix5.minor(1, 3), -120);
    EXPECT_EQ_CUSTOM(matrix5.minor(2, 0), -120);
    EXPECT_EQ_CUSTOM(matrix5.minor(2, 1), -240);
    EXPECT_EQ_CUSTOM(matrix5.minor(2, 2), -240);
    EXPECT_EQ_CUSTOM(matrix5.minor(2, 3), -120);
    EXPECT_EQ_CUSTOM(matrix5.minor(3, 0), -60);
    EXPECT_EQ_CUSTOM(matrix5.minor(3, 1), -120);
    EXPECT_EQ_CUSTOM(matrix5.minor(3, 2), -120);
    EXPECT_EQ_CUSTOM(matrix5.minor(3, 3), -60);
    
    
    // Transpose
    Matrix2I matrix6 = {{1, 2},
                        {3, 4}};
    Matrix2I matrix7 = matrix6.transpose();
    EXPECT_EQ_MAT(matrix7, Matrix2I({{1, 3},
                                 {2, 4}}));
    
    Matrix3I matrix8 = {{1, 2, 3},
                        {4, 5, 6},
                        {7, 8, 9}};
    Matrix3I matrix9 = matrix8.transpose();
    EXPECT_EQ_MAT(matrix9, Matrix3I({{1, 4, 7},
                                 {2, 5, 8},
                                 {3, 6, 9}}));
    
    // Translate
    Matrix4F matrix10 = Matrix4F(1).translate(Vec3F(1, 2, 3));
    EXPECT_EQ_MAT(matrix10, Matrix4F({{1, 0, 0, 1},
                                  {0, 1, 0, 2},
                                  {0, 0, 1, 3},
                                  {0, 0, 0, 1}}));
    
    Matrix3F matrix11 = Matrix3F(1).translate(Vec2F(1, 2));
    EXPECT_EQ_MAT(matrix11, Matrix3F({{1, 0, 1},
                                  {0, 1, 2},
                                  {0, 0, 1}}));
    
    // Scale
    Matrix4F matrix12 = Matrix4F(1).scale(Vec3F(1, 2, 3));
    EXPECT_EQ_MAT(matrix12, Matrix4F({{1, 0, 0, 0},
                                  {0, 2, 0, 0},
                                  {0, 0, 3, 0},
                                  {0, 0, 0, 1}}));
    
    Matrix3F matrix13 = Matrix3F(1).scale(Vec2F(1, 2));
    EXPECT_EQ_MAT(matrix13, Matrix3F({{1, 0, 0},
                                  {0, 2, 0},
                                  {0, 0, 1}}));
    
    // Rotate
    Matrix4F matrix14 = Matrix4F(1).rotate(Vec3F(90, 0, 0));
    EXPECT_EQ_MAT(matrix14, Matrix4F({{1, 0, 0,  0},
                                  {0, 0, -1, 0},
                                  {0, 1, 0,  0},
                                  {0, 0, 0,  1}}));
    
    Matrix4F matrix15 = Matrix4F(1).rotate(Vec3F(0, 90, 0));
    EXPECT_EQ_MAT(matrix15, Matrix4F({{0,  0, 1, 0},
                                  {0,  1, 0, 0},
                                  {-1, 0, 0, 0},
                                  {0,  0, 0, 1}}));
    
    Matrix4F matrix16 = Matrix4F(1).rotate(Vec3F(0, 0, 90));
    EXPECT_EQ_MAT(matrix16, Matrix4F({{0, -1, 0, 0},
                                  {1, 0,  0, 0},
                                  {0, 0,  1, 0},
                                  {0, 0,  0, 1}}));
    
    Matrix3F matrix17 = Matrix3F(1).rotate(90);
    EXPECT_EQ_MAT(matrix17, Matrix3F({{0, -1, 0},
                                  {1, 0,  0},
                                  {0, 0,  1}}));
}

