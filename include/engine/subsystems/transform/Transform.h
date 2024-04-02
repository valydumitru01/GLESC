/**************************************************************************************************
 * @file   Transform.h
 * @author Valentin Dumitru
 * @date   16/02/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include <cmath>

#include "TransformTypes.h"
#include "engine/core/math/geometry/GeometryTypes.h"
#include "engine/subsystems/renderer/mesh/Mesh.h"

namespace GLESC::Transform {
    struct Transform {
        static Math::Direction worldUp;
        static Math::Direction worldRight;
        static Math::Direction worldForward;

        Transform() = default;

        Transform(Position position, Rotation rotation, Scale scale);

        Position position = Position(0.0f, 0.0f, 0.0f);
        Rotation rotation = Rotation(0.0f, 0.0f, 0.0f);
        Scale scale = Scale(1.0f, 1.0f, 1.0f);

        [[nodiscard]] Math::Direction forward() const;

        [[nodiscard]] Math::Direction right() const;

        [[nodiscard]] Math::Direction up() const;

        [[nodiscard]] bool operator==(const Transform &other) const;

        [[nodiscard]] std::string toString() const;
    };

    class Transformer {
    public:
        static void transformMesh(Render::ColorMesh &mesh,
                                  const Transform &transform);

        static void transformBoundingVolume(Render::BoundingVolume &boundingVolume,
                                            const Transform &transform) ;
    }; // class Transformer
} // namespace GLESC
