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
        using Position = Vec3D;
        using Rotation = Vec3F;
        using Scale = Vec3F;

        using Direction = Vec3D;
    } // namespace Transform

    struct Transform {
        TransformTypes::Position position;
        TransformTypes::Rotation rotation;
        TransformTypes::Scale scale;

        TransformTypes::Direction forward() const {
            double yaw = rotation.getY();
            double pitch = rotation.getX();

            double x = cos(yaw) * cos(pitch);
            double y = sin(pitch);
            double z = sin(yaw) * cos(pitch);

            return TransformTypes::Direction(x, y, z);
        }

        TransformTypes::Direction right() const {
            double yaw = rotation.getY();

            double x = cos(yaw + M_PI / 2);
            double z = sin(yaw + M_PI / 2);

            return TransformTypes::Direction(x, 0, z);
        }

        bool operator==(const Transform& other) const {
            return position == other.position && rotation == other.rotation && scale == other.scale;
        }

        std::string toString() {
            return "Position: " + position.toString() + "\n" +
                "Rotation: " + rotation.toString() + "\n" +
                "Scale: " + scale.toString();
                toString();
        }
    };

    class Transformer {
    public:
        static void transformMesh(ColorMesh& mesh,
                                  const Transform& transform) {
            Mat4D model;
            model.makeModelMatrix(transform.position, transform.rotation, transform.scale);

            for (auto& vertex : mesh.getVertices()) {
                GLESC::getVertexPositionAttr(vertex) = model * GLESC::getVertexPositionAttr(vertex);
            }
        }
    }; // class Transformer
} // namespace GLESC
