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
    enum class Axis {
        X = 0,
        Y = 1,
        Z = 2
    };
    struct Transform {
        static Math::Direction worldUp;
        static Math::Direction worldRight;
        static Math::Direction worldForward;

        Transform() = default;

        Transform(Position position, Rotation rotation, Scale scale);

        const Position& getPosition() const {
            return position;
        }
        const Rotation& getRotation() const {
            return rotation;
        }
        const Scale& getScale() const {
            return scale;
        }

        void setPosition(const Position& position) {
            this->position = position;
        }
        void setRotation(const Rotation& rotation) {
            dirtyRotation = true;
            this->rotation = rotation;
        }
        void setScale(const Scale& scale) {
            this->scale = scale;
        }

        void addPosition(const Position& position) {
            this->position += position;
        }
        void addRotation(const Rotation& rotation) {
            dirtyRotation = true;
            this->rotation += rotation;
        }
        void addScale(const Scale& scale) {
            this->scale += scale;
        }



        void setPosition(Axis axis, PosComp value) {
            int index = static_cast<int>(axis);
            position.set(index, value);
        }
        void setRotation(Axis axis, RotComp value) {
            int index = static_cast<int>(axis);
            dirtyRotation = true;
            rotation.set(index, value);
        }
        void setScale(Axis axis, ScaleComp value) {
            int index = static_cast<int>(axis);
            scale.set(index, value);
        }

        void addPosition(Axis axis, PosComp value) {
            int index = static_cast<int>(axis);
            position.set(index, position.get(index) + value);
        }
        void addRotation(Axis axis, RotComp value) {
            int index = static_cast<int>(axis);
            dirtyRotation = true;
            rotation.set(index, rotation.get(index) + value);
        }
        void addScale(Axis axis, ScaleComp value) {
            int index = static_cast<int>(axis);
            scale.set(index, scale.get(index) + value);
        }




        [[nodiscard]] Math::Direction forward() const;

        [[nodiscard]] Math::Direction right() const;

        [[nodiscard]] Math::Direction up() const;

        [[nodiscard]] bool operator==(const Transform &other) const;

        [[nodiscard]] std::string toString() const;



    private:
        Math::Direction calculateForward() const;
        Math::Direction calculateRight() const;
        Math::Direction calculateUp() const;

        Position position = Position(0.0f, 0.0f, 0.0f);
        Rotation rotation = Rotation(0.0f, 0.0f, 0.0f);
        Scale scale = Scale(1.0f, 1.0f, 1.0f);

        bool dirtyRotation = true;

        Math::Direction forwardDirection;
        Math::Direction rightDirection;
        Math::Direction upDirection;
    };

    class Transformer {
    public:
        static void transformMesh(Render::ColorMesh &mesh,
                                  const Transform &transform);

        static void transformBoundingVolume(Render::BoundingVolume &boundingVolume,
                                            const Transform &transform) ;
    }; // class Transformer
} // namespace GLESC
