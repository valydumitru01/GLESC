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
        InstancedDynamic,
        BatchedStatic,
        BatchedDynamic
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
        if (renderType == RenderType::BatchedDynamic) {
            return GAPI::Enums::BufferUsages::DynamicDraw;
        }
        if (renderType == RenderType::BatchedStatic) {
            return GAPI::Enums::BufferUsages::StaticDraw;
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

    using RotateMat = Mat4F;
    using ScaleMat = Mat4F;
    using TranslateMat = Mat4F;
    using Model = Mat4F;
    using NormalMat = Mat3F;
    using View = Mat4F;
    using Projection = Mat4F;
    using MV = Mat4F;
    using VP = Mat4F;
    using MVP = Mat4F;

    template <typename IntensityType>
    class Intensity{
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

        bool operator>(const Intensity& other) const {
            return intensity > other.intensity;
        }

        bool operator<=(const Intensity& other) const {
            return intensity <= other.intensity;
        }

        IntensityType operator+(const Intensity& other) const {
            return intensity + other.intensity;
        }

        IntensityType operator-(const Intensity& other) const {
            return intensity - other.intensity;
        }

        IntensityType operator*(const Intensity& other) const {
            return intensity * other.intensity;
        }

        IntensityType operator/(const Intensity& other) const {
            return intensity / other.intensity;
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
        static const ColorRgb RED;
        static const ColorRgb GREEN;
        static const ColorRgb BLUE;
        static const ColorRgb WHITE;
        static const ColorRgb BLACK;
        static const ColorRgb YELLOW;
        static const ColorRgb CYAN;
        static const ColorRgb MAGENTA;
        static const ColorRgb ORANGE;
        static const ColorRgb PURPLE;
        static const ColorRgb PINK;
        static const ColorRgb BROWN;
        static const ColorRgb DARK_BROWN;
        static const ColorRgb GREY;
        static const ColorRgb LIGHT_GREY;
        static const ColorRgb DARK_GREY;

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


#pragma pack(push, 1)
    /**
     * @brief Color in normalized values
     * @details This cannot be constructed on its own, must be constructed from a ColorRgb
     */
    struct ColorRgbNorm : Vec3F {
        ColorRgbNorm() : Vec3F(0) {}

        float getR() const {
            return data[0];
        }

        float getG() const {
            return data[1];
        }

        float getB() const {
            return data[2];
        }

        ColorRgbNorm(float r, float g, float b) {
            D_ASSERT_LESS_OR_EQUAL(r, 1.0f, "R must be less or equal than 1");
            D_ASSERT_GREATER_OR_EQUAL(r, 0.0f, "R must be greater or equal than 0");
            D_ASSERT_LESS_OR_EQUAL(g, 1.0f, "G must be less or equal than 1");
            D_ASSERT_GREATER_OR_EQUAL(g, 0.0f, "G must be greater or equal than 0");
            D_ASSERT_LESS_OR_EQUAL(b, 1.0f, "B must be less or equal than 1");
            D_ASSERT_GREATER_OR_EQUAL(b, 0.0f, "B must be greater or equal than 0");
            data[0] = r;
            data[1] = g;
            data[2] = b;
        }


        ColorRgbNorm(const ColorRgb& colorRgb) {
            data[0] = colorRgb.getRNormalized();
            data[1] = colorRgb.getGNormalized();
            data[2] = colorRgb.getBNormalized();
        }

        bool operator==(const ColorRgbNorm& other) const {
            return Vec3F::operator==(other);
        }

        void operator=(const ColorRgb& colorRgb) {
            data[0] = colorRgb.getRNormalized();
            data[1] = colorRgb.getGNormalized();
            data[2] = colorRgb.getBNormalized();
        }

        void operator=(const ColorRgbNorm& other) {
            Vec3F::operator=(other);
        }

        [[nodiscard]] std::string toString() const {
            return "R:" + Stringer::toString(getR()) +
                " G:" + Stringer::toString(getG()) +
                " B:" + Stringer::toString(getB());
        }
    };

    /**
     * @brief Color in normalized values
     * @details This cannot be constructed on its own, must be constructed from a ColorRgb
     */
    struct ColorRgbaNorm : Vec4F {
        ColorRgbaNorm() = delete;

        float getR() const {
            return data[0];
        }

        float getG() const {
            return data[1];
        }

        float getB() const {
            return data[2];
        }

        float getA() const {
            return data[3];
        }

        ColorRgbaNorm(const ColorRgba& colorRgba) {
            data[0] = colorRgba.getRNormalized();
            data[1] = colorRgba.getGNormalized();
            data[2] = colorRgba.getBNormalized();
            data[3] = colorRgba.getANormalized();
        }


        bool operator==(const ColorRgbaNorm& other) const {
            return Vec4F::operator==(other);
        }

        void operator=(const ColorRgba& colorRgba) {
            data[0] = colorRgba.getRNormalized();
            data[1] = colorRgba.getGNormalized();
            data[2] = colorRgba.getBNormalized();
            data[3] = colorRgba.getANormalized();
        }

        void operator=(const ColorRgbaNorm& other) {
            Vec4F::operator=(other);
        }

        [[nodiscard]] std::string toString() const {
            return "R:" + Stringer::toString(getR()) +
                " G:" + Stringer::toString(getG()) +
                " B:" + Stringer::toString(getB()) +
                " A:" + Stringer::toString(getA());
        }
    };
#pragma pack(pop)
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

    template <>
    struct hash<GLESC::Render::ColorRgbNorm> {
        std::size_t operator()(const GLESC::Render::ColorRgbNorm& color) const noexcept {
            GLESC::Hasher::Hash seed = 0;
            GLESC::Hasher::hashCombine(seed, color.getR());
            GLESC::Hasher::hashCombine(seed, color.getG());
            GLESC::Hasher::hashCombine(seed, color.getB());
            return seed;
        }
    };

    template <>
    struct hash<GLESC::Render::ColorRgbaNorm> {
        std::size_t operator()(const GLESC::Render::ColorRgbaNorm& color) const noexcept {
            GLESC::Hasher::Hash seed = 0;
            GLESC::Hasher::hashCombine(seed, color.getR());
            GLESC::Hasher::hashCombine(seed, color.getG());
            GLESC::Hasher::hashCombine(seed, color.getB());
            GLESC::Hasher::hashCombine(seed, color.getA());
            return seed;
        }
    };
} // namespace std
