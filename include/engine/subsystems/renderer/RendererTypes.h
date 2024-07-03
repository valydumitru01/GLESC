/**************************************************************************************************
 * @file   RendererTypes.h
 * @author Valentin Dumitru
 * @date   21/02/2024
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "engine/core/debugger/Stringer.h"
#include "engine/core/low-level-renderer/buffers/VertexArray.h"
#include "engine/core/hash/Hasher.h"

namespace GLESC::Render {
    /**
     * @brief This is the possible rendering types for a mesh.
     */
    [[nodisacrd]] enum class RenderType {
        /**
         * @brief Single draw meshes are going to call render once per mesh every frame
         * Static meshes are not going to change their vertices
         */
        SingleDrawStatic,
        /**
         * @brief Single draw dynamic meshes can change their vertices at any point.
         * Dynamic meshes can change their vertices at any point.
         */
        SingleDrawDynamic,
        /**
         * @brief Instanced meshes are going to be rendered multiple times with the same vertices
         * Static meshes are not going to change their vertices
         */
        InstancedStatic,
        /**
         * @brief Instanced dynamic meshes can change their vertices at any point.
         * Dynamic meshes can change their vertices at any point.
         */
        InstancedDynamic,
        /**
         * @brief Batched meshes are going to be batched in a single large mesh and then rendered once (saving a lot
         * of draw calls).
         * Static meshes are not going to change their vertices
         */
        BatchedStatic,
        /**
         * @brief Batched meshes are going to be batched in a single large mesh and then rendered once (saving a lot
         * of draw calls).
         * Dynamic meshes can change their vertices at any point.
         */
        BatchedDynamic
    };

    /**
     * @brief This maps the enum of the renderer to the enum of the graphic api
     * @details This allows the renderer to be agnostic of the graphic api
     * @param renderType
     * @return The buffer usage for the graphic api
     */
    inline GAPI::Enums::BufferUsages getBufferUsage(RenderType renderType) {
        if (renderType == RenderType::SingleDrawStatic) {
            return GAPI::Enums::BufferUsages::StaticDraw;
        }
        if (renderType == RenderType::SingleDrawDynamic) {
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
        // This is just to make the compiler happy
        return GAPI::Enums::BufferUsages::StaticDraw;
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

    /**
     * @brief Intensity class, to encapsulate values between 0 and 1
     * @details This ensures values are always between 0 and 1, as are very common in the engine.
     * It has minimum overhead, and only validates in debug mode.
     * @tparam IntensityType The type of the intensity (float, double, etc)
     */
    template <typename IntensityType>
    [[nodiscard]] class Intensity {
    public:
        Intensity() = default;

        Intensity(const Intensity& other) = default;

        explicit Intensity(IntensityType intensityParam) {
            this->set(intensityParam);
        }

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

    /**
     * @brief Color functions, utility static class for color operations
     */
    class ColorFuncs {
    public:
        static void checkValue(float value, const std::string& valueName) {
            D_ASSERT_LESS_OR_EQUAL(value, 255.0f, valueName + " must be between less or equal than 255");
            D_ASSERT_GREATER_OR_EQUAL(value, 0.0f, valueName + " must be between greater or equal than 0");
        }

        /**
         * @brief Normalizes a color to be between 0 and 1
         * @param value
         * @return
         */
        static float normalizeColorValue(float value) {
            return value / 255.0f;
        }
    };

    struct ColorRgba;

    /**
     * @brief Color in RGB values
     * @details Will store colors in the range of 0 to 255
     * @details Has minimum overhead as only validates in debug mode.
     * @details Contains a set of static colors for convenience.
     * Examples: ColorRgb::Red, ColorRgb::Green, etc.
     * @details Inherits from Vec3F to allow for easy conversion to Vec3F, as many functions expect Vec3F
     */
    [[nodiscard]] struct ColorRgb : Vec3F {
        static const ColorRgb Red;
        static const ColorRgb Green;
        static const ColorRgb DarkGreen;
        static const ColorRgb Blue;
        static const ColorRgb White;
        static const ColorRgb Black;
        static const ColorRgb Yellow;
        static const ColorRgb Cyan;
        static const ColorRgb Magenta;
        static const ColorRgb Orange;
        static const ColorRgb Purple;
        static const ColorRgb Pink;
        static const ColorRgb Brown;
        static const ColorRgb DarkBrown;
        static const ColorRgb Grey;
        static const ColorRgb LightGrey;
        static const ColorRgb DarkGrey;
        static const ColorRgb ClearSkin;

        ColorRgb() = default;

        ColorRgb(const ColorRgb& other) = default;

        explicit ColorRgb(ColorRgba& other) noexcept;

        explicit ColorRgb(const ColorRgba& other) noexcept;

        ColorRgb& operator=(const ColorRgb& other) = default;

        ColorRgb(ColorRgb&& other) noexcept = default;

        ColorRgb& operator=(ColorRgb&& other) noexcept = default;

        ~ColorRgb() = default;


        ColorRgb(float r, float g, float b) {
            data[0] = r;
            data[1] = g;
            data[2] = b;
        }


        [[nodiscard]] const float& getR() const {
            return data[0];
        }

        [[nodiscard]] const float& getG() const {
            return data[1];
        }

        [[nodiscard]] const float& getB() const {
            return data[2];
        }

        [[nodiscard]] float getRNormalized() const {
            return ColorFuncs::normalizeColorValue(data[0]);
        }

        [[nodiscard]] float getGNormalized() const {
            return ColorFuncs::normalizeColorValue(data[1]);
        }

        [[nodiscard]] float getBNormalized() const {
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

        [[nodiscard]] Vec3F getRGBVec3FNormalized() const {
            return {getRNormalized(), getGNormalized(), getBNormalized()};
        }

        [[nodiscard]] std::string toString() const {
            return "R:" + Stringer::toString(getR()) + " G:" + Stringer::toString(getG()) + " B:" +
                Stringer::toString(getB());
        }
    };


    /**
     * @brief Color in RGBA values (x = [0] = R, y = [1] = G, z = [2] = B, w = [3] = A)
     * @details Will store colors in the range of 0 to 255
     * @details Has minimum overhead as only validates in debug mode.
     * @details Contains a set of static colors for convenience.
     * Examples: ColorRgba::Red, ColorRgba::Green, etc.
     * @details Inherits from Vec4F to allow for easy conversion to Vec4F, as many functions expect Vec4F
     */
    [[nodiscard]] struct ColorRgba : Vec4F {
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

        [[nodiscard]] const float& getR() const {
            return data[0];
        }

        [[nodiscard]] const float& getG() const {
            return data[1];
        }

        [[nodiscard]] const float& getB() const {
            return data[2];
        }

        [[nodiscard]] const float& getA() const {
            return data[3];
        }

        [[nodiscard]] float getRNormalized() const {
            return ColorFuncs::normalizeColorValue(data[0]);
        }

        [[nodiscard]] float getGNormalized() const {
            return ColorFuncs::normalizeColorValue(data[1]);
        }

        [[nodiscard]] float getBNormalized() const {
            return ColorFuncs::normalizeColorValue(data[2]);
        }

        [[nodiscard]] float getANormalized() const {
            return ColorFuncs::normalizeColorValue(data[3]);
        }

        [[nodiscard]] Vec4F getRGBAVec4FNormalized() const {
            return {getRNormalized(), getGNormalized(), getBNormalized(), getANormalized()};
        }


        [[nodiscard]] float& getRModifiable() {
            return data[0];
        }

        [[nodiscard]] float& getGModifiable() {
            return data[1];
        }

        [[nodiscard]] float& getBModifiable() {
            return data[2];
        }

        [[nodiscard]] float& getAModifiable() {
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

        [[nodiscard]] std::string toString() const {
            return "R:" + Stringer::toString(getR()) + " G:" + Stringer::toString(getG()) + " B:" +
                Stringer::toString(getB()) + " A:" + Stringer::toString(getA());
        }
    };


#pragma pack(push, 1)
    /**
     * @brief Color in normalized values
     * @details This cannot be constructed on its own, must be constructed from a ColorRgb
     */
    [[nodiscard]] struct ColorRgbNorm : Vec3F {
        ColorRgbNorm() : Vec3F(0) {
        }

        [[nodiscard]] float getR() const {
            return data[0];
        }

        [[nodiscard]] float getG() const {
            return data[1];
        }

        [[nodiscard]] float getB() const {
            return data[2];
        }

        explicit ColorRgbNorm(float r, float g, float b) {
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


        explicit ColorRgbNorm(const ColorRgb& colorRgb) {
            data[0] = colorRgb.getRNormalized();
            data[1] = colorRgb.getGNormalized();
            data[2] = colorRgb.getBNormalized();
        }

        [[nodiscard]] bool operator==(const ColorRgbNorm& other) const {
            return Vec3F::operator==(other);
        }

        ColorRgbNorm& operator=(const ColorRgb& colorRgb) {
            data[0] = colorRgb.getRNormalized();
            data[1] = colorRgb.getGNormalized();
            data[2] = colorRgb.getBNormalized();
            return *this;
        }

        ColorRgbNorm& operator=(const ColorRgbNorm& other) {
            Vec3F::operator=(other);
            return *this;
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
    [[nodiscard]] struct ColorRgbaNorm : Vec4F {
        ColorRgbaNorm() = delete;

        [[nodiscard]] float getR() const {
            return data[0];
        }

        [[nodiscard]] float getG() const {
            return data[1];
        }

        [[nodiscard]] float getB() const {
            return data[2];
        }

        [[nodiscard]] float getA() const {
            return data[3];
        }

        explicit ColorRgbaNorm(const ColorRgba& colorRgba) {
            data[0] = colorRgba.getRNormalized();
            data[1] = colorRgba.getGNormalized();
            data[2] = colorRgba.getBNormalized();
            data[3] = colorRgba.getANormalized();
        }


        [[nodiscard]] bool operator==(const ColorRgbaNorm& other) const {
            return Vec4F::operator==(other);
        }

        ColorRgbaNorm& operator=(const ColorRgba& colorRgba) {
            data[0] = colorRgba.getRNormalized();
            data[1] = colorRgba.getGNormalized();
            data[2] = colorRgba.getBNormalized();
            data[3] = colorRgba.getANormalized();
            return *this;
        }

        ColorRgbaNorm& operator=(const ColorRgbaNorm& other) = default;

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
