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
TEST(MatrixTests, Constructors){
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

TEST(MatrixTests, AssignmentOperators){
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