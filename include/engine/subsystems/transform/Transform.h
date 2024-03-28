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
#include "engine/core/math/algebra/vector/Vector.h"
#include "engine/subsystems/renderer/mesh/Mesh.h"

namespace GLESC {
    namespace TransformTypes {
        using Position = Vec3F;
        using PosComp = Position::ValueType;

        using Rotation = Vec3F;
        using RotComp = Rotation::ValueType;

        using Scale = Vec3F;
        using ScaleComp = Scale::ValueType;
    } // namespace Transform
    using namespace TransformTypes;

    struct Transform {
        Transform() = default;
        Transform(Position position, Rotation rotation, Scale scale) : position(position), rotation(rotation),
                                                                       scale(scale) {
        }

        Position position = Position(0.0f, 0.0f, 0.0f);
        Rotation rotation = Rotation(0.0f, 0.0f, 0.0f);
        Scale scale = Scale(1.0f, 1.0f, 1.0f);

        Math::Direction forward() const {
            RotComp yaw = Math::radians(rotation.getY());
            RotComp pitch = Math::radians(rotation.getX());

            PosComp x = cos(yaw) * cos(pitch);
            PosComp y = sin(pitch);
            PosComp z = sin(yaw) * cos(pitch);

            return Math::Direction(x, y, z).normalize();
        }

        Math::Direction right() const {
            return forward().cross(Math::Direction(0.0f, 1.0f, 0.0f)).normalize();
        }

        Math::Direction up() const {

            return right().cross(forward()).normalize();
        }

        bool operator==(const Transform &other) const {
            return position == other.position && rotation == other.rotation && scale == other.scale;
        }

        std::string toString() const {
            return "Position: " + position.toString() + "\n" +
                   "Rotation: " + rotation.toString() + "\n" +
                   "Scale: " + scale.toString();
        }
    };

    class Transformer {
    public:
        static void transformMesh(ColorMesh &mesh,
                                  const Transform &transform) {
            Model model;
            model.makeModelMatrix(transform.position, transform.rotation, transform.scale);

            for (auto &vertex : mesh.getVertices()) {
                GLESC::getVertexPositionAttr(vertex) = model * GLESC::getVertexPositionAttr(vertex);
            }

            transformBoundingVolume(mesh.getBoundingVolumeMutable(), transform);
        }

        static void transformBoundingVolume(BoundingVolume &boundingVolume,
                                            const Transform &transform) {
            Model model;
            model.makeModelMatrix(transform.position, transform.rotation, transform.scale);

            for (Math::Point &vertex : boundingVolume.getTopologyMutable().getVerticesMutable()) {
                vertex = model * vertex;
            }
        }
    }; // class Transformer
} // namespace GLESC
