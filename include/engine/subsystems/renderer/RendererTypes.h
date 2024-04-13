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

    template<typename IntensityType>
    class Intensity {
    public:
        Intensity() = default;

        Intensity(const Intensity &other) = default;

        Intensity &operator=(const Intensity &other) = default;

        Intensity(Intensity &&other) noexcept = default;

        Intensity &operator=(Intensity &&other) noexcept = default;

        bool operator==(const Intensity &other) const {
            return intensity == other.intensity;
        }
        bool operator<(const Intensity &other) const {
            return intensity < other.intensity;
        }

        ~Intensity() = default;

        explicit Intensity(IntensityType intensity) {
            set(intensity);
        }

        [[nodiscard]] IntensityType get() const {
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

    struct ColorRgba;

    struct ColorRgb {
        ColorRgb() = default;

        ColorRgb(const ColorRgb &other) = default;

        ColorRgb(ColorRgba &other) noexcept;

        ColorRgb &operator=(const ColorRgb &other) = default;

        ColorRgb(ColorRgb &&other) noexcept = default;

        ColorRgb &operator=(ColorRgb &&other) noexcept = default;

        ~ColorRgb() = default;


        ColorRgb(float r, float g, float b) : r(r), g(g), b(b),
                                              rNorm(normalize(r)), gNorm(normalize(g)), bNorm(normalize(b)) {
        }

        bool operator==(const ColorRgb &other) const {
            return r == other.r && g == other.g && b == other.b;
        }

        bool operator<(const ColorRgb &other) const {
            return std::tie(r, g, b) < std::tie(other.r, other.g, other.b);
        }


        float getR() const {
            return r;
        }

        float getG() const {
            return g;
        }

        float getB() const {
            return b;
        }

        float getRNormalized() const {
            return rNorm;
        }

        float getGNormalized() const {
            return gNorm;
        }

        float getBNormalized() const {
            return bNorm;
        }

        void setR(float rParam) {
            checkValue(rParam, "R");
            r = rParam;
            gNorm = normalize(r);
        }

        void setG(float gParam) {
            checkValue(gParam, "G");
            g = gParam;
            gNorm = normalize(g);
        }

        void setB(float bParam) {
            checkValue(bParam, "B");
            b = bParam;
            bNorm = normalize(b);
        }

        Vec3F getRGBVec3F() const {
            return Vec3F(r, g, b);
        }

        Vec3F getRGBVec3FNormalized() const {
            return Vec3F(rNorm, gNorm, bNorm);
        }

        [[nodiscard]] std::string toString() const {
            return "R:" + Stringer::toString(r) +
                   " G:" + Stringer::toString(g) +
                   " B:" + Stringer::toString(b);
        }

    protected:
        void checkValue(float value, std::string valueName) {
            D_ASSERT_LESS_OR_EQUAL(value, 255.0f, valueName + " must be between less or equal than 255");
            D_ASSERT_GREATER_OR_EQUAL(value, 0.0f, valueName + " must be between greater or equal than 0");
        }

        float normalize(float value) {
            return value / 255.0f;
        }

        float r{0.0f};
        float g{0.0f};
        float b{0.0f};

        float rNorm{0.0f};
        float gNorm{0.0f};
        float bNorm{0.0f};
    };

    struct ColorRgba : ColorRgb {
        ColorRgba() = default;

        ColorRgba(const ColorRgba &other) = default;

        ColorRgba(ColorRgb &other) noexcept;

        ColorRgba &operator=(const ColorRgba &other) = default;

        ColorRgba(ColorRgba &&other) noexcept = default;

        ColorRgba &operator=(ColorRgba &&other) noexcept = default;

        ~ColorRgba() = default;

        ColorRgba(float r, float g, float b, float a) : ColorRgb(r, g, b), a(a), aNorm(normalize(a)) {
        }

        Vec4F getRGBAVec4F() const {
            return Vec4F(r, g, b, a);
        }

        Vec4F getRGBAVec4FNormalized() const {
            return Vec4F(rNorm, gNorm, bNorm, aNorm);
        }

        float getA() const {
            return a;
        }

        float getANormalized() const {
            return aNorm;
        }


        void setA(float aParam) {
            checkValue(aParam, "A");
            a = aParam;
            aNorm = normalize(a);
        }

        [[nodiscard]] std::string toString() const {
            return ColorRgb::toString() + " A:" + Stringer::toString(a);
        }

    private:
        float a = 0.0f;

        float aNorm = 0.0f;
    };
} // namespace GLESC::Render
// Hash
template<>
struct std::hash<GLESC::Render::ColorRgb> {
    std::size_t operator()(const GLESC::Render::ColorRgb &rgb) const noexcept {
        std::size_t hash = 0;
        GLESC::Hasher::hashCombine(hash, std::hash<float>{}(rgb.getR()));
        GLESC::Hasher::hashCombine(hash, std::hash<float>{}(rgb.getG()));
        GLESC::Hasher::hashCombine(hash, std::hash<float>{}(rgb.getB()));
        return hash;
    }
};

template<>
struct std::hash<GLESC::Render::ColorRgba> {
    std::size_t operator()(const GLESC::Render::ColorRgba &rgba) const noexcept {
        std::size_t hash = 0;
        GLESC::Hasher::hashCombine(hash, std::hash<GLESC::Render::ColorRgb>{}(rgba));
        GLESC::Hasher::hashCombine(hash, std::hash<float>{}(rgba.getA()));
        return hash;
    }
};
