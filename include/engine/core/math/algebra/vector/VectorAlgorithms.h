/**************************************************************************************************
 * @file   VectorAlgorithms.h
 * @author Valentin Dumitru
 * @date   23/01/2024
 * @brief  @TODO Add description of this file
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

#include "engine/core/math/algebra/vector/VectorTypes.h"
#include "engine/core/exceptions/core/math/MathException.h"
#include "engine/core/math/Math.h"

namespace GLESC::Math {
    class VectorAlgorithms {
    public:
        // =============================================================================================================
        // ============================================= Vector Init ===================================================
        // =============================================================================================================

        template <typename Type, size_t N>
        static void
        vectorZero(VectorData<Type, N>& vec) {
            std::fill(std::begin(vec), std::end(vec), Type(0));
        }


        template <typename Type, size_t N>
        static void
        vectorFill(VectorData<Type, N>& vec, const Type& value) {
            std::fill(std::begin(vec), std::end(vec), value);
        }

        template <typename Type, size_t N>
        static void
        vectorInitRawArray(VectorData<Type, N>& vec, const Type (&list)[N]) {
            std::copy(std::begin(list), std::end(list), std::begin(vec));
        }


        template <typename Type, size_t N, size_t N2>
        static void
        vectorCopy(VectorData<Type, N>& vecToCopyTo, const VectorData<Type, N2>& vecToCopy) {
            if constexpr (N == N2) // This is needed because you can't compare pointers to different types
                if (&vecToCopyTo == &vecToCopy) {
                    return;
                }
            constexpr size_t minOfTheTwo = std::min(N, N2); // So we don't go out of bounds
            for (size_t i = 0; i < minOfTheTwo; ++i) {
                vecToCopyTo[i] = vecToCopy[i];
            }
        }


        template <typename Type, size_t N>
        static void
        vectorMove(VectorData<Type, N>& vecToMoveTo, VectorData<Type, N>& movedVec) {
            if (&vecToMoveTo == &movedVec) {
                return;
            }
            std::move(std::begin(movedVec), std::end(movedVec), std::begin(vecToMoveTo));
        }


        // =============================================================================================================
        // ========================================= Arithmetic operations =============================================
        // =============================================================================================================
        /**
         * @brief Adds two vectors.
         *
         * @tparam Type Data type of the vectors (e.g., double, float).
         * @tparam N Dimension of space.
         * @param a First vector.
         * @param b Second vector.
         * @return Sum of the two vectors.
         */
        template <typename Type, size_t N>
        static void
        vectorAdd(const VectorData<Type, N>& a, const VectorData<Type, N>& b, VectorData<Type, N>& result) {
            for (size_t i = 0; i < N; ++i) {
                result[i] = a[i] + b[i];
            }
        }

        /**
         * @brief Add a scalar to a vector.
         * @details Adds a scalar to each element of a vector.
         * @tparam Type Data type of the vector (e.g., double, float).
         * @tparam N Dimension of space.
         * @param vec Vector to be added to.
         * @param scalar Scalar to add to the vector.
         * @return Sum of the vector and the scalar.
         */
        template <typename Type, size_t N>
        static void
        vectorScalarAdd(const VectorData<Type, N>& vec, const Type& scalar, VectorData<Type, N>& result) {
            for (size_t i = 0; i < N; ++i) {
                result[i] = vec[i] + scalar;
            }
        }

        /**
         * @brief Subtracts two vectors.
         * @details result = vecLeft - vecRight
         * @tparam TypeResult Data type of the result vector (e.g., double, float).
         * @tparam TypeLeft Data type of the first vector (e.g., double, float).
         * @tparam TypeRight Data type of the second vector (e.g., double, float).
         * @tparam N Dimension of space.
         * @param vecLeft First vector.
         * @param vecRight Second vector.
         * @return Difference of the two vectors.
         */
        template <typename TypeResult, typename TypeLeft, typename TypeRight, size_t N>
        static void vectorSub(
            const VectorData<TypeLeft, N>& vecLeft,
            const VectorData<TypeRight, N>& vecRight,
            VectorData<TypeResult, N>& result) {
            for (size_t i = 0; i < N; ++i) {
                result[i] = vecLeft[i] - vecRight[i];
            }
        }

        /**
         * @brief Subtracts a scalar from a vector.
         * @details Subtracts a scalar from each element of a vector.
         * @tparam Type Data type of the vector (e.g., double, float).
         * @tparam N Dimension of space.
         * @param vec Vector to be subtracted from.
         * @param scalar Scalar to subtract from the vector.
         * @return Difference of the vector and the scalar.
         */
        template <typename Type, size_t N>
        static void
        vectorScalarSub(const VectorData<Type, N>& vec, const Type& scalar, VectorData<Type, N>& result) {
            for (size_t i = 0; i < N; ++i) {
                result[i] = vec[i] - scalar;
            }
        }

        /**
         * @brief Negates a vector.
         * @details Negates each element of a vector.
         * @tparam Type Data type of the vector (e.g., double, float).
         * @tparam N Dimension of space.
         * @param vec Vector to be negated.
         * @return Negated vector.
         */
        template <typename Type, size_t N>
        static void vectorNegate(const VectorData<Type, N>& vec, VectorData<Type, N>& result) {
            for (size_t i = 0; i < N; ++i) {
                result[i] = -vec[i];
            }
        }

        /**
         * @brief Multiplies two vectors.
         *
         * @tparam Type Data type of the vectors (e.g., double, float).
         * @tparam N Dimension of space.
         * @param vec1 First vector.
         * @param vec2 Second vector.
         * @return Product of the two vectors.
         */
        template <typename Type, size_t N>
        static void
        vectorMul(const VectorData<Type, N>& vec1, const VectorData<Type, N>& vec2, VectorData<Type, N>& result) {
            for (size_t i = 0; i < N; ++i) {
                result[i] = vec1[i] * vec2[i];
            }
        }

        /**
         * @brief Multiplies a vector by a scalar.
         *
         * @tparam Type Data type of the vector (e.g., double, float).
         * @tparam N Dimension of space.
         * @param vec Vector to be multiplied.
         * @param scalar Scalar to multiply the vector by.
         * @return Product of the vector and the scalar.
         */
        template <typename Type, size_t N>
        static void
        vectorScalarMul(const VectorData<Type, N>& vec, const Type& scalar, VectorData<Type, N>& result) {
            for (size_t i = 0; i < N; ++i) {
                result[i] = vec[i] * scalar;
            }
        }


        /**
         * @brief Divides two vectors.
         *
         * @tparam Type Data type of the vectors (e.g., double, float).
         * @tparam N Dimension of space.
         * @param dividend First vector.
         * @param divisor Second vector.
         * @return Product of the two vectors.
         */
        template <typename Type, size_t N>
        static void
        vectorDiv(const VectorData<Type, N>& dividend, const VectorData<Type, N>& divisor,
                  VectorData<Type, N>& result) {
            for (size_t i = 0; i < N; ++i) {
                result[i] = dividend[i] / divisor[i];
            }
        }

        /**
         * @brief Divides a vector by a scalar.
         *
         * @tparam Type Data type of the vector (e.g., double, float).
         * @tparam N Dimension of space.
         * @param dividend Vector to be divided.
         * @param divisorScalar Scalar to divide the vector by.
         * @return Quotient of the vector and the scalar.
         */
        template <typename Type, size_t N>
        static void
        vectorScalarDiv(const VectorData<Type, N>& dividend, const Type& divisorScalar, VectorData<Type, N>& result) {
            for (size_t i = 0; i < N; ++i) {
                result[i] = dividend[i] / divisorScalar;
            }
        }

        // =============================================================================================================
        // ========================================== Vector Comparations ==============================================
        // =============================================================================================================

        /**
         * @brief Equality operator for vectors
         * @details Compares this vector to another, allowing for different underlying types.
         * Handles floating-point comparison via 'eq' function.
         * @param rhs Vector to compare against
         * @return True if the vectors are equal, false otherwise
         */
        template <typename Type, size_t N>
        static bool eq(const VectorData<Type, N>& vec1, const VectorData<Type, N>& vec2) {
            for (size_t i = 0; i < N; ++i) {
                if (!Math::eq(vec1[i], vec2[i])) {
                    return false;
                }
            }
            return true;
        }


        template <typename Type, size_t N>
        static bool neq(const VectorData<Type, N>& vec1, const VectorData<Type, N>& vec2) {
            return !eq(vec1, vec2);
        }

        template <typename Type, size_t N>
        static bool lt(const VectorData<Type, N>& vec1, const VectorData<Type, N>& vec2) {
            // Use of length squared is more efficient
            auto length1 = VectorAlgorithms::sum(vec1);
            auto length2 = VectorAlgorithms::sum(vec2);
            return length1 < length2;
        }


        // =============================================================================================================
        // ========================================== Vector Opeartions ================================================
        // =============================================================================================================


        /**
         * @brief Checks if a vector is zero.
         * @details A vector is zero if all its elements are zero.
         * @tparam Type Data type of the vector (e.g., double, float).
         * @tparam N Dimension of space.
         * @param vec Vector to be checked.
         * @return true if the vector is zero, false otherwise.
         */
        template <typename Type, size_t N>
        static bool isZero(const VectorData<Type, N>& vec) {
            VectorData<Type, N> zeroVec;
            VectorAlgorithms::vectorFill(zeroVec, Type(0));
            return eq(vec, zeroVec);
        }

        template <typename Type, size_t N>
        static void clampWithVectors(const VectorData<Type, N>& vec, const VectorData<Type, N>& min,
                                     const VectorData<Type, N>& max, VectorData<Type, N>& result) {
            for (size_t i = 0; i < N; ++i) {
                result[i] = Math::clamp(vec[i], min[i], max[i]);
            }
        }

        template <typename Type, size_t N>
        static void clampWithValues(const VectorData<Type, N>& vec, const Type& min, const Type& max,
                                    VectorData<Type, N>& result) {
            for (size_t i = 0; i < N; ++i) {
                result[i] = Math::clamp(vec[i], min, max);
            }
        }

        template <typename Type, size_t N>
        static void modWithValue(const VectorData<Type, N>& vec, const Type& mod, VectorData<Type, N>& result) {
            for (size_t i = 0; i < N; ++i) {
                result[i] = Math::mod(vec[i], mod);
            }
        }

        template <typename Type, size_t N>
        static void modWithVector(const VectorData<Type, N>& vec, const VectorData<Type, N>& mod,
                                  VectorData<Type, N>& result) {
            for (size_t i = 0; i < N; ++i) {
                result[i] = Math::mod(vec[i], mod[i]);
            }
        }

        template <typename Type, size_t N>
        static void lerp(const VectorData<Type, N>& start, const VectorData<Type, N>& end, const Type& factor,
                         VectorData<Type, N>& result) {
            for (size_t i = 0; i < N; ++i) {
                result[i] = Math::lerp(start[i], end[i], factor);
            }
        }

        /**
         * @brief Computes the sum of all elements inside the vector
         * @tparam Type Data type of the vector (e.g., double, float).
         * @tparam N Dimension of space.
         * @param vec Vector to be used.
         * @return Sum of the vector.
         */
        template <typename Type, size_t N>
        static Type sum(const VectorData<Type, N>& vec) {
            Type result = 0;
            for (size_t i = 0; i < N; ++i) {
                result += vec[i];
            }
            return result;
        }


        /**
         * @brief Computes the absolute value of a vector.
         * @details Computes the absolute value of each element of a vector, it can be used for in place absolute value.
         * @tparam Type Data type of the vector (e.g., double, float).
         * @tparam N Dimension of space.
         * @param vec Vector to be used.
         * @param result Vector to store the absolute value of the input vector.
         * @return Absolute value of the vector.
         */
        template <typename Type, size_t N>
        static void abs(const VectorData<Type, N>& vec, VectorData<Type, N>& result) {
            for (size_t i = 0; i < N; ++i) {
                result[i] = Math::abs(vec[i]);
            }
        }

        /**
         * @brief Computes the dot product of two vectors.
         * @details Also called Inner Product, it is the sum of the products of the corresponding elements of the two.
         * Dot product gives us a sense of similarity between two vectors.
         * Also, represents the projection of one vector onto another.
         * This implementation is for cartesian coordinates in euclidean space only.
         * @tparam Type Data type of the vectors (e.g., double, float).
         * @tparam N Dimension of space.
         * @param leftVec First vector.
         * @param rightVec Second vector.
         * @return Dot product of the two vectors.
         */
        template <typename TypeLeft, typename TypeRight, size_t N>
        static auto dotProduct(const VectorData<TypeLeft, N>& leftVec, const VectorData<TypeRight, N>& rightVec) {
            using CommonType = std::common_type_t<TypeLeft, TypeRight>;
            CommonType result = 0;
            for (size_t i = 0; i < N; ++i) {
                result += leftVec[i] * rightVec[i];
            }
            return result;
        }

        /**
         * @brief Computes the cross product of two vectors.
         * @details The cross product is a vector that is perpendicular to the two vectors being multiplied and the
         * plane containing them.
         * This only has meaning in 3D space.
         * The magnitude of the cross product is the area of the parallelogram that the two vectors span.
         * The direction of the cross product is orthogonal to both vectors, and follows the right-hand rule.
         * @note Cross product is not commutative, is anti-commutative, meaning that a x b = -b x a.
         * @tparam TypeResult Data type of the result vector (e.g., double, float).
         * @tparam TypeLeft Data type of the first vector (e.g., double, float).
         * @tparam TypeRight Data type of the second vector (e.g., double, float).
         * @param vec1 First vector.
         * @param vec2 Second vector.
         * @return Cross product of the two vectors.
         */
        template <typename TypeResult, typename TypeLeft, typename TypeRight>
        static void
        crossProduct(const VectorData<TypeLeft, 3>& vec1, const VectorData<TypeRight, 3>& vec2,
                     VectorData<TypeResult, 3>& result) {
            result[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
            result[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
            result[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
        }


        /**
         * @brief Computes the length of a vector.
         *
         * @tparam Type Data type of the vector (e.g., double, float).
         * @tparam N Dimension of space.
         * @param vec Vector.
         * @return Length of the vector.
         */
        template <typename Type, size_t N>
        static Type length(const VectorData<Type, N>& vec) {
            return Math::sqrt(dotProduct(vec, vec));
        }

        /**
         * @brief Computes the squared length of a vector.
         *
         * @tparam Type Data type of the vector (e.g., double, float).
         * @tparam N Dimension of space.
         * @param vec Vector.
         * @return Squared length of the vector.
         */
        template <typename Type, size_t N>
        static Type lengthSquared(const VectorData<Type, N>& vec) {
            return dotProduct(vec, vec);
        }


        template <typename Type, size_t N>
        static bool isNormalized(const VectorData<Type, N>& vec) {
            return Math::eq(length(vec), Type(1));
        }

        /**
         * @brief Computes the distance between two vectors.
         *
         * @tparam Type Data type of the vectors (e.g., double, float).
         * @tparam N Dimension of space.
         * @param vec1 First vector.
         * @param vec2 Second vector.
         * @return Distance between the two vectors.
         */
        template <typename Type, size_t N>
        static Type distance(const VectorData<Type, N>& vec1, const VectorData<Type, N>& vec2) {
            VectorData<Type, N> diff;
            vectorSub(vec1, vec2, diff);
            return length(diff);
        }

        /**
         * @brief Computes the squared distance between two vectors.
         *
         * @tparam Type Data type of the vectors (e.g., double, float).
         * @tparam N Dimension of space.
         * @param vec1 First vector.
         * @param vec2 Second vector.
         * @return Squared distance between the two vectors.
         */
        template <typename Type, size_t N>
        static Type distanceSquared(const VectorData<Type, N>& vec1, const VectorData<Type, N>& vec2) {
            VectorData<Type, N> diff;
            vectorSub(vec1, vec2, diff);
            return lengthSquared(diff);
        }

        /**
         * @brief Normalizes a vector.
         *
         * @tparam Type Data type of the vector (e.g., double, float).
         * @tparam N Dimension of space.
         * @param vec Vector to be normalized.
         * @return Normalized vector.
         */
        template <typename Type, size_t N>
        static void normalize(const VectorData<Type, N>& vec, VectorData<Type, N>& result) {
            Type length = VectorAlgorithms::length(vec);
            if (Math::eq(length, Type(1)) || Math::eq(length, Type(0))) {
                result = vec;
                return;
            }

            for (size_t i = 0; i < N; ++i)
                result[i] = vec[i] / length;
        }

        /**
         * @brief Computes the angle between two vectors.
         *
         * @tparam Type Data type of the vectors (e.g., double, float).
         * @tparam N Dimension of space.
         * @param vec1 First vector.
         * @param vec2 Second vector.
         * @return Angle between the two vectors.
         */
        template <typename Type, size_t N>
        static Type angle(const VectorData<Type, N>& vec1, const VectorData<Type, N>& vec2) {
            D_ASSERT_TRUE(length(vec1) * length(vec2) != Type(0), "Cannot compute angle between zero vectors");
            return std::acos(dotProduct(vec1, vec2) / (length(vec1) * length(vec2)));
        }

        /**
         * @brief Projects a vector onto another vector.
         * @details Projects a vector onto another vector by computing the scalar projection and multiplying it by
         * the unit vector of the second vector.
         * @tparam Type Data type of the vectors (e.g., double, float).
         * @tparam N Dimension of space.
         * @param vec Vector to be projected.
         * @param onto Vector to be projected onto.
         * @return Projected vector.
         */
        template <typename Type, size_t N>
        static void
        project(const VectorData<Type, N>& vec, const VectorData<Type, N>& onto, VectorData<Type, N>& result) {
            Type scalarProjection = dotProduct(vec, onto) / length(onto);
            VectorAlgorithms::vectorScalarMul(onto, scalarProjection, result);
        }


        /**
         * @brief Checks if two vectors are parallel.
         * @details Two vectors are parallel if the absolute value of their dot product equals the product of their
         * lengths.
         * @tparam Type Data type of the vectors (e.g., double, float).
         * @tparam N Dimension of space.
         * @param vec1 First vector.
         * @param vec2 Second vector.
        * @return true if the vectors are parallel, false otherwise.
        */
        template <typename Type, size_t N>
        static bool areParallel(const VectorData<Type, N>& vec1, const VectorData<Type, N>& vec2) {
            Type absDot = Math::abs(dotProduct(vec1, vec2));
            Type length1 = length(vec1);
            Type length2 = length(vec2);
            Type productOfLengths = length1 * length2;
            return Math::eq(absDot, productOfLengths); // Account for floating-point errors
        }

        template <typename Type, size_t N>
        static bool isHomogeneous(const VectorData<Type, N>& vec) {
            return vec[N - 1] == Type(1);
        }

        template <typename Type, size_t N>
        static void homogenize(const VectorData<Type, N>& vec, VectorData<Type, N + 1>& result) {
            VectorAlgorithms::vectorCopy(result, vec); // Copies until the Nth element
            result[N] = Type(1); // Set the N+1th element to 1
        }

        template <typename Type, size_t N>
        static void dehomogenize(const VectorData<Type, N>& vec, VectorData<Type, N - 1>& result) {
            if (vec[N - 1] == Type(0))
                throw MathException("Cannot dehomogenize a vector with a zero w-component.");

            Type wInv = Type(1) / vec[N - 1]; // Inverse of the w-component

            for (size_t i = 0; i < N - 1; ++i) {
                result[i] = vec[i] * wInv; // Divide each component by the w-component
            }
        }

        template <typename Type, size_t N>
        static void makeForwardVector(const VectorData<Type, N>& rotationRads, VectorData<Type, N>& result) {
            Type pitch = rotationRads[0];
            Type yaw = rotationRads[1];

            result[0] = Math::cos(pitch) * Math::sin(yaw);
            result[1] = Math::sin(pitch);
            result[2] = Math::cos(pitch) * Math::cos(yaw);
        }


        template <typename Type, size_t N>
        static void makeRightVector(const VectorData<Type, N>& rotationRads,
                                    VectorData<Type, N>& result) {
            Type pitch = rotationRads[0];
            Type yaw = rotationRads[1];
            Type roll = rotationRads[2];
            result[0] = Math::cos(pitch) * Math::sin(yaw - Math::PI / 2);
            result[1] = Math::sin(roll);
            result[2] = Math::cos(pitch) * Math::cos(yaw - Math::PI / 2);
        }

        template <typename Type, size_t N>
        static void makeUpVector(const VectorData<Type, N>& rotationRads, VectorData<Type, N>& result) {
            Type pitch = rotationRads[0];
            Type yaw = rotationRads[1];
            Type roll = rotationRads[2];

            result[0] = -Math::cos(roll) * Math::sin(pitch) * Math::sin(yaw) + Math::sin(roll) * Math::cos(yaw); // up_x
            result[1] = Math::cos(roll) * Math::cos(pitch); // up_y
            result[2] = -Math::cos(roll) * Math::sin(pitch) * Math::cos(yaw) - Math::sin(roll) * Math::sin(yaw); // up_z
        }


        /**
         * @brief Checks if two vectors are orthogonal.
         * @details Two vectors are orthogonal if their dot product is zero.
         * @tparam Type Data type of the vectors (e.g., double, float).
         * @tparam N Dimension of space.
         * @param vec1 First vector.
         * @param vec2 Second vector.
         * @return true if the vectors are orthogonal, false otherwise.
         */
        template <typename Type, size_t N>
        static bool areOrthogonal(const VectorData<Type, N>& vec1, const VectorData<Type, N>& vec2) {
            Type dot = dotProduct(vec1, vec2);
            return Math::eq(dot, Type(0));
        }


        template <typename Type, size_t N>
        static void getOrthogonal(const VectorData<Type, N>& data, VectorData<Type, N>& result) {
            static_assert(N == 2 || N == 3 || N == 4, "getOrthogonal is only implemented for 2D, 3D, and 4D vectors");

            if constexpr (N == 2) {
                // In 2D, the orthogonal vector can be obtained by swapping the data
                // and negating one of them.
                result = {-data[1], data[0]};
            }
            else if constexpr (N == 3) {
                // In 3D, we use the cross product to find an orthogonal vector.
                // First, we need a non-parallel vector to cross with.
                // We choose either (0, 1, 0) or (1, 0, 0) depending on which one is less parallel
                // to the original vector, to avoid degenerate cross products.
                VectorData<Type, N> nonParallel;
                if (Math::abs(data[0]) > Math::abs(data[1]))
                    nonParallel = VectorData<Type, N>({0, 1, 0});
                else
                    nonParallel = VectorData<Type, N>({1, 0, 0});

                // The cross product of this vector with 'nonParallel' yields an orthogonal vector.
                VectorAlgorithms::crossProduct(data, nonParallel, result);
            }
            else if constexpr (N == 4) {
                // Finding an orthogonal vector in 4D involves more choices due to extra degrees of
                // freedom. Here, we zero out two data and solve the other two to maintain
                // orthogonality. The choice of which data to zero out depends on the
                // non-zero data of the original vector.
                if (data[0] != 0 || data[1] != 0) {
                    // If the first or second component is non-zero, we set the last two data
                    // to zero and negate one of the first two data to create orthogonality.
                    result = VectorData<Type, N>({-data[1], data[0], 0, 0});
                }
                else {
                    // If the first two data are zero, we work with the last two data.
                    // We negate one and copy the other to create orthogonality.
                    result = VectorData<Type, N>({0, -data[3], data[2], 0});
                }
            }
        }

        /**
         * @brief Checks if two vectors are collinear.
         * @details Two vectors are collinear if one is a scalar multiple of the other.
         * @tparam Type Data type of the vectors (e.g., double, float).
         * @tparam N Dimension of space.
         * @param vec1 First vector.
         * @param vec2 Second vector.
         * @return true if the vectors are collinear, false otherwise.
         */
        template <typename Type, size_t N>
        static bool isMultipleOf(const VectorData<Type, N>& vec1, const VectorData<Type, N>& vec2) {
            Type ratio;
            bool ratioInitialized = false;

            for (size_t i = 0; i < N; ++i) {
                if (!Math::eq(vec2[i], Type(0))) {
                    if (!ratioInitialized) {
                        ratio = vec1[i] / vec2[i];
                        ratioInitialized = true;
                    }
                    else {
                        if (!Math::eq(vec1[i] / vec2[i], ratio)) {
                            return false;
                        }
                    }
                }
                else if (!Math::eq(vec1[i], Type(0))) {
                    return false;
                }
            }

            return true;
        }


        /**
         * @brief Generates a string representation of a vector.
         * @details Generates a string representation of a vector by calling the toString method of each element.
         * @tparam Type Data type of the vector (e.g., double, float).
         * @tparam N Dimension of space.
         * @param vec Vector to be converted to string.
         * @return String representation of the vector.
         */
        template <typename Type, size_t N>
        static std::string toString(const VectorData<Type, N>& vec) {
            std::string result;
            result += "[";
            if constexpr (std::is_arithmetic_v<Type>) {
                for (size_t i = 0; i < N; ++i) {
                    result += std::to_string(vec[i]) + ", ";
                }
            }
            else {
                for (size_t i = 0; i < N; ++i) {
                    result += vec[i].toString() + ", ";
                }
            }

            result.pop_back();
            result.pop_back();
            result += "]";
            return result;
        }
    }; // class VectorBasicAlgorithms
} // namespace GLESC::Math
