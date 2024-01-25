/**************************************************************************************************
 * @file   VectorBasicAlgorithms.h
 * @author Valentin Dumitru
 * @date   23/01/2024
 * @brief  @TODO Add description of this file
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

#include <vector>
#include "engine/core/math/algebra/vector/VectorTypes.h"

namespace GLESC::Math {
    class VectorAlgorithms {
    public:
        
        template<typename Type, size_t N, size_t N2>
        static inline void
        vectorCopy(const VectorData<Type, N> &vec, VectorData<Type, N2> &result) {
            size_t minOfTheTwo = std::min(N, N2); // So we don't go out of bounds
            for (size_t i = 0; i < minOfTheTwo; ++i) {
                result[i] = vec[i];
            }
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
        template<typename Type, size_t N>
        static inline void
        vectorAdd(const VectorData<Type, N> &a, const VectorData<Type, N> &b, VectorData<Type, N> &result) {
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
        template<typename Type, size_t N>
        static inline void
        vectorScalarAdd(const VectorData<Type, N> &vec, const Type &scalar, VectorData<Type, N> &result) {
            for (size_t i = 0; i < N; ++i) {
                result[i] = vec[i] + scalar;
            }
        }
        
        /**
         * @brief Subtracts two vectors.
         *
         * @tparam Type Data type of the vectors (e.g., double, float).
         * @tparam N Dimension of space.
         * @param a First vector.
         * @param b Second vector.
         * @return Difference of the two vectors.
         */
        template<typename Type, size_t N>
        static inline void
        vectorSub(const VectorData<Type, N> &a, const VectorData<Type, N> &b, VectorData<Type, N> &result) {
            for (size_t i = 0; i < N; ++i) {
                result[i] = a[i] - b[i];
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
        template<typename Type, size_t N>
        static inline void
        vectorScalarSub(const VectorData<Type, N> &vec, const Type &scalar, VectorData<Type, N> &result) {
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
        template<typename Type, size_t N>
        static inline void vectorNegate(const VectorData<Type, N> &vec, VectorData<Type, N> &result) {
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
        template<typename Type, size_t N>
        static inline void
        vectorMul(const VectorData<Type, N> &vec1, const VectorData<Type, N> &vec2, VectorData<Type, N> &result) {
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
        template<typename Type, size_t N>
        static inline void
        vectorScalarMul(const VectorData<Type, N> &vec, const Type &scalar, VectorData<Type, N> &result) {
            for (size_t i = 0; i < N; ++i) {
                result[i] = vec[i] * scalar;
            }
        }
        
        
        /**
         * @brief Divides two vectors.
         *
         * @tparam Type Data type of the vectors (e.g., double, float).
         * @tparam N Dimension of space.
         * @param a First vector.
         * @param b Second vector.
         * @return Product of the two vectors.
         */
        template<typename Type, size_t N>
        static inline void
        vectorDiv(const VectorData<Type, N> &a, const VectorData<Type, N> &b, VectorData<Type, N> &result) {
            for (size_t i = 0; i < N; ++i) {
                result[i] = a[i] / b[i];
            }
        }
        
        /**
         * @brief Divides a vector by a scalar.
         *
         * @tparam Type Data type of the vector (e.g., double, float).
         * @tparam N Dimension of space.
         * @param vec Vector to be divided.
         * @param scalar Scalar to divide the vector by.
         * @return Quotient of the vector and the scalar.
         */
        template<typename Type, size_t N>
        static inline void
        vectorScalarDiv(const VectorData<Type, N> &vec, const Type &scalar, VectorData<Type, N> &result) {
            for (size_t i = 0; i < N; ++i) {
                result[i] = vec[i] / scalar;
            }
        }
        
        
        /**
         * @brief Computes the dot product of two vectors.
         *
         * @tparam Type Data type of the vectors (e.g., double, float).
         * @tparam N Dimension of space.
         * @param a First vector.
         * @param b Second vector.
         * @return Dot product of the two vectors.
         */
        template<typename Type, size_t N>
        static inline Type dotProduct(const VectorData<Type, N> &a, const VectorData<Type, N> &b) {
            Type result = 0;
            for (size_t i = 0; i < N; ++i) {
                result += a[i] * b[i];
            }
            return result;
        }
        
        /**
         * @brief Computes the cross product of two vectors.
         *
         * @tparam Type Data type of the vectors (e.g., double, float).
         * @param vec1 First vector.
         * @param vec2 Second vector.
         * @return Cross product of the two vectors.
         */
        template<typename Type>
        static inline VectorData<Type, 3>
        crossProduct(const VectorData<Type, 3> &vec1, const VectorData<Type, 3> &vec2, VectorData<Type, 3> &result) {
            result[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
            result[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
            result[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
            return result;
        }
        
        
        /**
         * @brief Computes the length of a vector.
         *
         * @tparam Type Data type of the vector (e.g., double, float).
         * @tparam N Dimension of space.
         * @param vec Vector.
         * @return Length of the vector.
         */
        template<typename Type, size_t N>
        static inline Type length(const VectorData<Type, N> &vec) {
            return std::sqrt(dotProduct(vec, vec));
        }
        
        /**
         * @brief Computes the squared length of a vector.
         *
         * @tparam Type Data type of the vector (e.g., double, float).
         * @tparam N Dimension of space.
         * @param vec Vector.
         * @return Squared length of the vector.
         */
        template<typename Type, size_t N>
        static inline Type lengthSquared(const VectorData<Type, N> &vec) {
            return dotProduct(vec, vec);
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
        template<typename Type, size_t N>
        static inline Type distance(const VectorData<Type, N> &vec1, const VectorData<Type, N> &vec2) {
            return length(vec1 - vec2);
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
        template<typename Type, size_t N>
        static inline Type distanceSquared(const VectorData<Type, N> &vec1, const VectorData<Type, N> &vec2) {
            return lengthSquared(vec1 - vec2);
        }
        
        /**
         * @brief Normalizes a vector.
         *
         * @tparam Type Data type of the vector (e.g., double, float).
         * @tparam N Dimension of space.
         * @param vec Vector to be normalized.
         * @return Normalized vector.
         */
        template<typename Type, size_t N>
        static inline void normalize(const VectorData<Type, N> &vec, VectorData<Type, N> &result) {
            Type length = VectorAlgorithms::length(vec);
            if (eq(length, Type(1)) || GLESC::Math::eq(length, Type(0)))
                result = vec;
            
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
        template<typename Type, size_t N>
        static inline Type angle(const VectorData<Type, N> &vec1, const VectorData<Type, N> &vec2) {
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
        template<typename Type, size_t N>
        static inline void
        project(const VectorData<Type, N> &vec, const VectorData<Type, N> &onto, VectorData<Type, N> &result) {
            Type scalarProjection = dotProduct(vec, onto) / length(onto);
            VectorAlgorithms::vectorScalarMul(onto, scalarProjection, result);
        }
        
    }; // class VectorBasicAlgorithms
} // namespace GLESC::Math
