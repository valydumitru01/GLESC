/**************************************************************************************************
 * @file   RendererTypes.h
 * @author Valentin Dumitru
 * @date   21/02/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "engine/core/low-level-renderer/buffers/VertexArray.h"
#include "engine/core/hash/Hasher.h"

namespace GLESC::Render {
    enum class RenderType {
        Static,
        Dynamic,
        InstancedStatic,
        InstancedDynamic
    };

    inline GAPI::Enums::BufferUsages getBufferUsage(RenderType renderType) {
        if (renderType == RenderType::Static) {
            return GAPI::Enums::BufferUsages::StaticDraw;
        }
        if (renderType == RenderType::Dynamic) {
            return GAPI::Enums::BufferUsages::DynamicDraw;
        }
        if (renderType == RenderType::InstancedStatic) {
            return GAPI::Enums::BufferUsages::StaticDraw;
        }
        if (renderType == RenderType::InstancedDynamic) {
            return GAPI::Enums::BufferUsages::DynamicDraw;
        }
        D_ASSERT_TRUE(false, "Unknown render type");
    }

    /**
     * @brief Vertex Array Object
     * @details We make the unique because we only want the renderer to own the VAOs
     */
    using VertexArrayPtr = std::unique_ptr<GAPI::VertexArray>;

    using Color = Vec4F;
    using UV = Vec2F;
    using Normal = Vec3F;
    using Position = Vec3F;

    using Model = Mat4F;
    using NormalMat = Mat3F;
    using View = Mat4F;
    using Projection = Mat4F;
    using MV = Mat4F;
    using VP = Mat4F;
    using MVP = Mat4F;

    template <typename IntensityType>
    class Intensity {
    public:
        Intensity() = default;

        Intensity(const Intensity& other) = default;

        Intensity& operator=(const Intensity& other) = default;

        Intensity(Intensity&& other) noexcept = default;

        Intensity& operator=(Intensity&& other) noexcept = default;

        bool operator==(const Intensity& other) const {
            return intensity == other.intensity;
        }

        bool operator<(const Intensity& other) const {
            return intensity < other.intensity;
        }

        ~Intensity() = default;

        explicit Intensity(IntensityType intensity) {
            set(intensity);
        }

        [[nodiscard]] IntensityType get() const {
            return intensity;
        }

        [[nodiscard]] IntensityType& getModifiable() {
            return intensity;
        }

        void set(IntensityType intensityParam) {
            D_ASSERT_GREATER_OR_EQUAL(intensityParam, IntensityType(0), "Intensity must be greater or equal than 0");
            D_ASSERT_LESS_OR_EQUAL(intensityParam, IntensityType(1), "Intensity must be less or equal than 1");
            intensity = intensityParam;
        }

        [[nodiscard]] std::string toString() const {
            return Stringer::toString(intensity);
        }

    private:
        IntensityType intensity = IntensityType(0);
    };

    class ColorFuncs {
    public:
        static void checkValue(float value, std::string valueName) {
            D_ASSERT_LESS_OR_EQUAL(value, 255.0f, valueName + " must be between less or equal than 255");
            D_ASSERT_GREATER_OR_EQUAL(value, 0.0f, valueName + " must be between greater or equal than 0");
        }

        static float normalizeColorValue(float value) {
            return value / 255.0f;
        }
    };

    struct ColorRgba;

    struct ColorRgb : Vec3F {
        ColorRgb() = default;

        ColorRgb(const ColorRgb& other) = default;

        ColorRgb(ColorRgba& other) noexcept;

        ColorRgb(const ColorRgba& other) noexcept;

        ColorRgb& operator=(const ColorRgb& other) = default;

        ColorRgb(ColorRgb&& other) noexcept = default;

        ColorRgb& operator=(ColorRgb&& other) noexcept = default;

        ~ColorRgb() = default;


        ColorRgb(float r, float g, float b) {
            data[0] = r;
            data[1] = g;
            data[2] = b;
        }


        const float& getR() const {
            return data[0];
        }

        const float& getG() const {
            return data[1];
        }

        const float& getB() const {
            return data[2];
        }

        float getRNormalized() const {
            return ColorFuncs::normalizeColorValue(data[0]);
        }

        float getGNormalized() const {
            return ColorFuncs::normalizeColorValue(data[1]);
        }

        float getBNormalized() const {
            return ColorFuncs::normalizeColorValue(data[2]);
        }

        void setR(float rParam) {
            ColorFuncs::checkValue(rParam, "R");
            data[0] = rParam;
        }

        void setG(float gParam) {
            ColorFuncs::checkValue(gParam, "G");
            data[1] = gParam;
        }

        void setB(float bParam) {
            ColorFuncs::checkValue(bParam, "B");
            data[2] = bParam;
        }

        Vec3F getRGBVec3FNormalized() const {
            return Vec3F(getRNormalized(), getGNormalized(), getBNormalized());
        }

        [[nodiscard]] std::string toString() const {
            return "R:" + Stringer::toString(getR()) + " G:" + Stringer::toString(getG()) + " B:" +
                Stringer::toString(getB());
        }
    };

    struct ColorRgba : Vec4F {
        ColorRgba() = default;

        ColorRgba(const ColorRgba& other) = default;

        ColorRgba(ColorRgb& other) noexcept;

        ColorRgba(const ColorRgb& other) noexcept;

        ColorRgba& operator=(const ColorRgba& other) = default;

        ColorRgba(ColorRgba&& other) noexcept = default;

        ColorRgba& operator=(ColorRgba&& other) noexcept = default;

        ~ColorRgba() = default;

        ColorRgba(float r, float g, float b, float a) {
            data[0] = r;
            data[1] = g;
            data[2] = b;
            data[3] = a;
        }

        const float& getR() const {
            return data[0];
        }

        const float& getG() const {
            return data[1];
        }

        const float& getB() const {
            return data[2];
        }

        const float& getA() const {
            return data[3];
        }

        float getRNormalized() const {
            return ColorFuncs::normalizeColorValue(data[0]);
        }

        float getGNormalized() const {
            return ColorFuncs::normalizeColorValue(data[1]);
        }

        float getBNormalized() const {
            return ColorFuncs::normalizeColorValue(data[2]);
        }

        float getANormalized() const {
            return ColorFuncs::normalizeColorValue(data[3]);
        }

        Vec4F getRGBAVec4FNormalized() const {
            return Vec4F(getRNormalized(), getGNormalized(), getBNormalized(), getANormalized());
        }


        float& getRModifiable() {
            return data[0];
        }

        float& getGModifiable() {
            return data[1];
        }

        float& getBModifiable() {
            return data[2];
        }

        float& getAModifiable() {
            return data[3];
        }

        void setR(float rParam) {
            ColorFuncs::checkValue(rParam, "R");
            data[0] = rParam;
        }

        void setG(float gParam) {
            ColorFuncs::checkValue(gParam, "G");
            data[1] = gParam;
        }

        void setB(float bParam) {
            ColorFuncs::checkValue(bParam, "B");
            data[2] = bParam;
        }

        void setA(float aParam) {
            ColorFuncs::checkValue(aParam, "A");
            data[3] = aParam;
        }

        std::string toString() const {
            return "R:" + Stringer::toString(getR()) + " G:" + Stringer::toString(getG()) + " B:" +
                Stringer::toString(getB()) + " A:" + Stringer::toString(getA());
        }
    };
} // namespace GLESC::Render

// Hash definition for rgb values
// We just call the hash function for Vec3F
namespace std {
    template <>
    struct hash<GLESC::Render::ColorRgb> {
        std::size_t operator()(const GLESC::Render::ColorRgb& color) const noexcept {
            return std::hash<Vec3F>()(color);
        }
    };

    template <>
    struct hash<GLESC::Render::ColorRgba> {
        std::size_t operator()(const GLESC::Render::ColorRgba& color) const noexcept {
            return std::hash<Vec4F>()(color);
        }
    };
} // namespace std