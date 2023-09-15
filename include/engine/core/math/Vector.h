/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <cmath>

template<typename T>
class Vector3 {
public:
    T x, y, z;
    
    // Constructors
    Vector3() : x(T(0)), y(T(0)), z(T(0)) {}
    
    Vector3(T x, T y, T z) : x(x), y(y), z(z) {}
    
    // Operator Overloads
    Vector3<T> operator+(const Vector3<T> &rhs) const {
        return Vector3<T>(x + rhs.x, y + rhs.y, z + rhs.z);
    }
    
    Vector3<T> operator-(const Vector3<T> &rhs) const {
        return Vector3<T>(x - rhs.x, y - rhs.y, z - rhs.z);
    }
    
    Vector3<T> operator*(T scalar) const {
        return Vector3<T>(x * scalar, y * scalar, z * scalar);
    }
    
    Vector3<T> operator/(T scalar) const {
        return Vector3<T>(x / scalar, y / scalar, z / scalar);
    }
    
    T dot(const Vector3<T> &rhs) const {
        return x * rhs.x + y * rhs.y + z * rhs.z;
    }
    
    Vector3<T> cross(const Vector3<T> &rhs) const {
        return Vector3<T>(y * rhs.z - z * rhs.y,
                          z * rhs.x - x * rhs.z,
                          x * rhs.y - y * rhs.x);
    }
    
    T length() const {
        return std::sqrt(x * x + y * y + z * z);
    }
    
    Vector3<T> normalize() const {
        T length = this->length();
        return Vector3<T>(x / length, y / length, z / length);
    }
    
    Vector3<T> operator+=(const Vector3<T> &rhs) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }
    
    Vector3<T> operator-=(const Vector3<T> &rhs) {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }
    
    Vector3<T> operator*=(T scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }
    
    Vector3<T> operator/=(T scalar) {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }
    
    bool operator==(const Vector3<T> &rhs) const {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }
    
    bool operator!=(const Vector3<T> &rhs) const {
        return x != rhs.x || y != rhs.y || z != rhs.z;
    }
    
};

template<typename T>
class Vector2 {
public:
    T x, y;
    
    // Constructors
    Vector2() : x(T(0)), y(T(0)) {}
    
    Vector2(T x, T y) : x(x), y(y) {}
    
    // Operator Overloads
    Vector2<T> operator+(const Vector2<T> &rhs) const {
        return Vector2<T>(x + rhs.x, y + rhs.y);
    }
    
    Vector2<T> operator-(const Vector2<T> &rhs) const {
        return Vector2<T>(x - rhs.x, y - rhs.y);
    }
    
    Vector2<T> operator*(T scalar) const {
        return Vector2<T>(x * scalar, y * scalar);
    }
    
    Vector2<T> operator/(T scalar) const {
        return Vector2<T>(x / scalar, y / scalar);
    }
    
    T dot(const Vector2<T> &rhs) const {
        return x * rhs.x + y * rhs.y;
    }
    
    T length() const {
        return std::sqrt(x * x + y * y);
    }
    
    Vector2<T> normalize() const {
        T length = this->length();
        return Vector2<T>(x / length, y / length);
    }
    
    Vector2<T> operator+=(const Vector2<T> &rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
    
    Vector2<T> operator-=(const Vector2<T> &rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }
    
    Vector2<T> operator*=(T scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }
    
    Vector2<T> operator/=(T scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }
    
    bool operator==(const Vector2<T> &rhs) const {
        return x == rhs.x && y == rhs.y;
    }
    
    bool operator!=(const Vector2<T> &rhs) const {
        return x != rhs.x || y != rhs.y;
    }
};

template<typename T>
class Vector4 {
public:
    T x, y, z, w;
    
    // Constructors
    Vector4() : x(T(0)), y(T(0)), z(T(0)), w(T(0)) {}
    
    Vector4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
    
    // Operator Overloads
    Vector4<T> operator+(const Vector4<T> &rhs) const {
        return Vector4<T>(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
    }
    
    Vector4<T> operator-(const Vector4<T> &rhs) const {
        return Vector4<T>(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
    }
    
    Vector4<T> operator*(T scalar) const {
        return Vector4<T>(x * scalar, y * scalar, z * scalar, w * scalar);
    }
    
    Vector4<T> operator/(T scalar) const {
        return Vector4<T>(x / scalar, y / scalar, z / scalar, w / scalar);
    }
    
    T dot(const Vector4<T> &rhs) const {
        return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
    }
    
    T length() const {
        return std::sqrt(x * x + y * y + z * z + w * w);
    }
    
    Vector4<T> normalize() const {
        T length = this->length();
        return Vector4<T>(x / length, y / length, z / length, w / length);
    }
    
    Vector4<T> operator+=(const Vector4<T> &rhs) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        w += rhs.w;
        return *this;
    }
    
    Vector4<T> operator-=(const Vector4<T> &rhs) {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        w -= rhs.w;
        return *this;
    }
    
    Vector4<T> operator*=(T scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        w *= scalar;
        return *this;
    }
    
    Vector4<T> operator/=(T scalar) {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        w /= scalar;
        return *this;
    }
    
    bool operator==(const Vector4<T> &rhs) const {
        return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
    }
    
    bool operator!=(const Vector4<T> &rhs) const {
        return x != rhs.x || y != rhs.y || z != rhs.z || w != rhs.w;
    }
    
    Vector4<T> cross(const Vector4<T> &rhs) const {
        return Vector4<T>(y * rhs.z - z * rhs.y,
                          z * rhs.x - x * rhs.z,
                          x * rhs.y - y * rhs.x,
                          0);
    }
    
};

using Vector2F [[maybe_unused]] = Vector2<float>;
using Vector3F [[maybe_unused]] = Vector3<float>;
using Vector4F [[maybe_unused]] = Vector4<float>;

using Vector2I [[maybe_unused]] = Vector2<int>;
using Vector3I [[maybe_unused]] = Vector3<int>;
using Vector4I [[maybe_unused]] = Vector4<int>;

using Vector3U [[maybe_unused]] = Vector3<unsigned int>;
using Vector2U [[maybe_unused]] = Vector2<unsigned int>;
using Vector4U [[maybe_unused]] = Vector4<unsigned int>;

using Vector2D [[maybe_unused]] = Vector2<double>;
using Vector3D [[maybe_unused]] = Vector3<double>;
using Vector4D [[maybe_unused]] = Vector4<double>;

