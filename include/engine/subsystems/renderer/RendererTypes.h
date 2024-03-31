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
#include "engine/core/low-level-renderer/buffers/vertex/VertexArray.h"

enum class RenderType {
    Static,
    Dynamic,
    InstancedStatic,
    InstancedDynamic
};

inline GAPI::BufferUsages getBufferUsage(RenderType renderType) {
    if (renderType == RenderType::Static) {
        return GAPI::BufferUsages::StaticDraw;
    }
    if (renderType == RenderType::Dynamic) {
        return GAPI::BufferUsages::DynamicDraw;
    }
    if (renderType == RenderType::InstancedStatic) {
        return GAPI::BufferUsages::StaticDraw;
    }
    if (renderType == RenderType::InstancedDynamic) {
        return GAPI::BufferUsages::DynamicDraw;
    }
    D_ASSERT_TRUE(false, "Unknown render type");
}

/**
 * @brief Vertex Array Object
 * @details We make the unique because we only want the renderer to own the VAOs
 */
using VertexArrayPtr = std::unique_ptr<GLESC::VertexArray>;

using Color = Vec4F;
using UV = Vec2F;
using Normal = Vec3F;
using Position = Vec3F;

using Model = Mat4F;
using View = Mat4F;
using Projection = Mat4F;
using VP = Mat4F;
using MVP = Mat4F;

namespace GLESC::Render {
    struct Rgba;

    struct Rgb {
        Rgb() = default;

        Rgb(const Rgb &other) = default;

        Rgb(Rgba &other) noexcept;

        Rgb &operator=(const Rgb &other) = default;

        Rgb(Rgb &&other) noexcept = default;

        Rgb &operator=(Rgb &&other) noexcept = default;

        ~Rgb() = default;


        Rgb(float r, float g, float b) : r(r), g(g), b(b) {
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

        void setR(float rParam) {
            checkValue(rParam, "R");
            r = rParam;
        }

        void setG(float gParam) {
            checkValue(gParam, "G");
            g = gParam;
        }

        void setB(float bParam) {
            checkValue(bParam, "B");
            b = bParam;
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

        float r = 0.0f;
        float g = 0.0f;
        float b = 0.0f;
    };

    struct Rgba : Rgb {
        Rgba() = default;

        Rgba(const Rgba &other) = default;

        Rgba(Rgb &other) noexcept;

        Rgba &operator=(const Rgba &other) = default;

        Rgba(Rgba &&other) noexcept = default;

        Rgba &operator=(Rgba &&other) noexcept = default;

        ~Rgba() = default;

        Rgba(float r, float g, float b, float a) : Rgb(r, g, b), a(a) {
        }

        float getA() const {
            return a;
        }

        void setA(float aParam) {
            checkValue(aParam, "A");
            a = aParam;
        }

        [[nodiscard]] std::string toString() const {
            return Rgb::toString() + " A:" + Stringer::toString(a);
        }

    private:
        float a = 0.0f;
    };
} // namespace GLESC::Render
