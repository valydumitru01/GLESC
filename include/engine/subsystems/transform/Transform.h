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
#include "TransformTypes.h"
#include "engine/core/math/geometry/GeometryTypes.h"
#include "engine/subsystems/ingame-debug/EntityStatsManager.h"
#include "engine/subsystems/renderer/RendererTypes.h"
#include "engine/subsystems/renderer/mesh/Mesh.h"

/**
 * @brief Namespace that contains all the classes and functions related to the Transform subsystem.
 * @details The Transform subsystem is responsible for managing the position, rotation, and scale of entities in the
 * game world. Also stores functinality for transforming meshes and bounding volumes.
 */
namespace GLESC::Transform {
    /**
     * @brief Enum class that represents the axis of a 3D space.
     */
    enum class Axis {
        X = 0,
        Y = 1,
        Z = 2
    };

    /**
     * @brief Enum class that represents the rotation axis of a 3D space.
     */
    enum class RotationAxis {
        Pitch = static_cast<int>(Axis::X),
        Yaw = static_cast<int>(Axis::Y),
        Roll = static_cast<int>(Axis::Z)
    };

    /**
     * @brief Struct that represents the position, rotation, and scale of an entity in the game world.
     * @details This is the component of Transform, and allows the entity to exist in the game world.
     */
    struct Transform : public EngineComponent {
        static Math::Direction worldUp;
        static Math::Direction worldRight;
        static Math::Direction worldForward;

        Transform() {
            modelMat.makeModelMatrix(position, rotationDegrees.toRads(), scale);
        }


        /**
         * @brief Constructor that initializes the transform with the given position, rotation, and scale.
         * @param position The position of the transform.
         * @param rotation The rotation of the transform.
         * @param scale The scale of the transform.
         */
        Transform(Position position, Rotation rotation, Scale scale);

        const Position& getPosition() const { return position; }
        const Rotation& getRotation() const { return rotationDegrees; }
        const Scale& getScale() const { return scale; }

        void setPosition(const Position& position) {
            dirty = true;
            translateDirty = true;
            this->position = position;
        }

        void setRotation(const Rotation& rotation) {
            dirty = true;
            rotateDirty = true;
            this->rotationDegrees = rotation;
        }

        void setScale(const Scale& scale) {
            dirty = true;
            scaleDirty = true;
            this->scale = scale;
        }

        void setPosition(Axis axis, PosComp value) {
            dirty = true;
            translateDirty = true;
            int index = static_cast<int>(axis);
            position.set(index, value);
        }

        void setRotation(RotationAxis axis, RotComp value) {
            dirty = true;
            rotateDirty = true;
            int index = static_cast<int>(axis);
            rotationDegrees.set(index, value);
        }

        void setScale(Axis axis, ScaleComp value) {
            dirty = true;
            scaleDirty = true;
            int index = static_cast<int>(axis);
            scale.set(index, value);
        }


        void addPosition(const Position& position) {
            setPosition(this->position + position);
        }

        void addRotation(const Rotation& rotation) {
            setRotation(this->rotationDegrees + rotation);
        }

        void addScale(const Scale& scale) {
            setScale(this->scale + scale);
        }

        void addPosition(Axis axis, PosComp value) {
            setPosition(axis, position.get(static_cast<int>(axis)) + value);
        }

        void addRotation(RotationAxis axis, RotComp value) {
            setRotation(axis, rotationDegrees.get(static_cast<int>(axis)) + value);
        }

        void addScale(Axis axis, ScaleComp value) {
            setScale(axis, scale.get(static_cast<int>(axis)) + value);
        }

        /**
         * @brief Returns the model matrix of the transform.
         * @return The model matrix of the transform.
         */
        Render::Model getModelMatrix() const {
            if (modelDirty) {
                modelMat.makeModelMatrix(position, rotationDegrees.toRads(), scale);
                modelDirty = false;
            }
            return modelMat;
        }

        /**
         * @brief Returns the translation matrix of the transform.
         * @details Will not be recalculated if the position has not changed.
         * @return The translation matrix of the transform.
         */
        Render::TranslateMat getTranslationMatrix() const {
            if (translateDirty) {
                translateMat.makeTranslationMatrix(position);
                translateDirty = false;
            }
            return translateMat;
        }

        /**
         * @brief Returns the rotation matrix of the transform.
         * @details Will not be recalculated if the rotation has not changed.
         * @return The rotation matrix of the transform.
         */
        Render::RotateMat getRotationMatrix() const {
            if (rotateDirty) {
                rotateMat.makeRotationMatrix(rotationDegrees.toRads());
                rotateDirty = false;
            }
            return rotateMat;
        }

        /**
         * @brief Returns the scale matrix of the transform.
         * @details Will not be recalculated if the scale has not changed.
         * @return The scale matrix of the transform.
         */
        Render::ScaleMat getScaleMatrix() const {
            if (scaleDirty) {
                scaleMat.makeScaleMatrix(scale);
                scaleDirty = false;
            }
            return scaleMat;
        }

        [[nodiscard]] std::vector<EntityStatsManager::Value> getDebuggingValues();
        /**
         * @brief Calculates the forward vector using the rotation
         * @return The forward vector
         */
        [[nodiscard]] Math::Direction forward() const;

        /**
         * @brief Calculates the right vector using the rotation
         * @return The right vector
         */
        [[nodiscard]] Math::Direction right() const;


        /**
         * @brief Calculates the up vector using the rotation
         * @return The up vector
         */
        [[nodiscard]] Math::Direction up() const;

        [[nodiscard]] bool operator==(const Transform& other) const;

        [[nodiscard]] std::string toString() const;

    private:
        Math::Direction calculateForward() const;
        Math::Direction calculateRight() const;
        Math::Direction calculateUp() const;

        Position position = Position(0.0f, 0.0f, 0.0f);
        Rotation rotationDegrees = Rotation(0.0f, 0.0f, 0.0f);
        Scale scale = Scale(1.0f, 1.0f, 1.0f);

        Math::Direction forwardDirection;
        Math::Direction rightDirection;
        Math::Direction upDirection;


        mutable Render::Model modelMat;
        mutable bool modelDirty = true;
        mutable Render::TranslateMat translateMat;
        mutable bool translateDirty = true;
        mutable Render::RotateMat rotateMat;
        mutable bool rotateDirty = true;
        mutable Render::ScaleMat scaleMat;
        mutable bool scaleDirty = true;

        mutable bool dirty = true;
    };

    /**
     * @brief Class that contains functions for transforming meshes and bounding volumes.
     * @details This allows transforming all the vertices or points of a mesh or bounding volume by a given transform.
     * Iterating over all the elements and transforming them.
     */
    class Transformer {
    public:
        /**
         * @brief Translates a mesh by a given position.
         * @details This function will translate all the vertices of the mesh by the given position, iterating over
         * all of them and applying the translation.
         * @param mesh The mesh to translate.
         * @param translation The translation to apply.
         */
        static void translateMesh(Render::ColorMesh& mesh, const Position& translation);
        /**
         * @brief Rotates a mesh by a given rotation.
         * @details This function will rotate all the vertices of the mesh by the given rotation, iterating over
         * all of them and applying the rotation.
         * @param mesh The mesh to rotate.
         * @param rotationDegrees The rotation to apply.
         */
        static void rotateMesh(Render::ColorMesh& mesh, const Rotation& rotationDegrees);
        /**
         * @brief Scales a mesh by a given scale.
         * @details This function will transform all the vertices of the mesh by the given transform, iterating over
         * all of them and applying the scale.
         * @param mesh The mesh to scale.
         */
        static void transformMesh(Render::ColorMesh& mesh, const Transform& transform);

        static Rotation lookAt(const Position& from, const Position& to, const Math::Direction& up);

        /**
         * @brief Transforms a bounding volume by a given transform.
         * @details This function will transform all the points of the bounding volume by the given transform, iterating
         * over all of them and applying the transform.
         * @param boundingVolume The bounding volume to transform.
         * @param transform The transform to apply.
         * @return The transformed bounding volume.
         */
        static Math::BoundingVolume transformBoundingVolume(const Math::BoundingVolume& boundingVolume,
                                                            const Transform& transform);
        /**
         * @brief Transforms a bounding volume by a given matrix matrix.
         * @details This function will transform all the points of the bounding volume by the given matrix,
         * iterating over all of them and applying the matrix.
         * @param boundingVolume The bounding volume to transform.
         * @param matrix The model matrix to apply.
         * @return The transformed bounding volume.
         */
        static Math::BoundingVolume transformBoundingVolume(const Math::BoundingVolume& boundingVolume,
                                                            const Render::Model& matrix);

        /**
         * @brief Transforms a position by a given matrix.
         * @details It will just multiply the position by the matrix and return the result.
         * @param position The position to transform.
         * @param matrix The matrix to apply.
         */
        static Position transformVector(const Position& position, const Render::Model& matrix);

        /**
         * @brief Transforms the clip position to normalized device coordinates.
         * @details This is done by just dehomogenizing the clip position.
         * @param clipPos The clip position to transform.
         * @return The normalized device coordinates.
         */
        static Position clipToNDC(const HomogeneousPosition& clipPos);
        /**
         * @brief Transforms the normalized device coordinates to viewport coordinates.
         * @details This is done by just scaling the clip position by the viewport width and height.
         * @param clipPos The normalized device coordinates to transform.
         * @param vpWidth The viewport width.
         * @param vpHeight The viewport height.
         * @return The viewport coordinates.
         */
        static Position NDCToViewport(const Position& clipPos, float vpWidth, float vpHeight);
        /**
         * @brief Transforms the world position to viewport coordinates.
         * @details This is done by transforming the world position to clip position, then to normalized device
         * coordinates, and finally to viewport coordinates.
         * @param worldPos The world position to transform.
         * @param viewProj The view projection matrix.
         * @param vpWidth The viewport width.
         * @param vpHeight The viewport height.
         * @return The viewport coordinates.
         */
        static Position worldToViewport(const Position& worldPos, const Render::VP& viewProj, float vpWidth,
                                        float vpHeight);

    private:
        static void transformMesh(Render::ColorMesh& mesh, const Mat4F& matrix);
    }; // class Transformer

    /**
     * @brief Class that contains functions for interpolating between two transforms.
     * @details This allows interpolating between two transforms to get a smooth transition between two states.
     * It contains two transforms, the current and the last one.
     * Once there is two transforms, the next time you call interpolate, it will return a transform that is between the
     * two.
     */
    struct Interpolator {
        Interpolator() = default;
        /**
         * @brief Pushes a new transform to the interpolator.
         * @param transform The transform to push.
         */
        void pushTransform(const Transform& transform);
        /**
         * @brief Interpolates between the current and the last transform.
         * @param alphaParam The alpha value of the interpolation (alpha is a value between 0 and 1 and represents the
         * percentage of the interpolation).
         * @return The interpolated transform.
         */
        Transform interpolate(float alphaParam) const;

    private:
        Transform currentTransform{};
        Transform lastTransform{};
    }; // struct Interpolator
} // namespace GLESC
