/**************************************************************************************************
 * @file   CameraPerspective.h
 * @author Valentin Dumitru
 * @date   2024-04-10
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "engine/core/math/geometry/GeometryTypes.h"
#include "engine/subsystems/ingame-debug/EntityStatsManager.h"

namespace GLESC::Render {
    class CameraPerspective {
    public:
        CameraPerspective() = default;

        CameraPerspective(const Math::Distance& fovDegrees, const Math::Distance& nearPlane,
                          const Math::Distance& farPlane, const Math::Distance& viewWidth,
                          const Math::Distance& viewHeight)
            : fovDegrees(fovDegrees), viewWidth(viewWidth), viewHeight(viewHeight), nearPlane(nearPlane),
              farPlane(farPlane) {
        }

        float getFovDegrees() const {
            return fovDegrees;
        }

        float getViewWidth() const {
            return viewWidth;
        }

        float getViewHeight() const {
            return viewHeight;
        }

        float getNearPlane() const {
            return nearPlane;
        }

        float getFarPlane() const {
            return farPlane;
        }

        void setFovDegrees(float fovDegrees) {
            this->fovDegrees = Math::Distance(fovDegrees);
            dirty = true;
        }

        void setViewWidth(float viewWidth) {
            this->viewWidth = Math::Distance(viewWidth);
            dirty = true;
        }

        void setViewHeight(float viewHeight) {
            this->viewHeight = Math::Distance(viewHeight);
            dirty = true;
        }

        void setNearPlane(float nearPlane) {
            this->nearPlane = Math::Distance(nearPlane);
            dirty = true;
        }

        void setFarPlane(float farPlane) {
            this->farPlane = Math::Distance(farPlane);
            dirty = true;
        }

        void setDirty() const {
            dirty = true;
        }

        void setClean() const {
            dirty = false;
        }

        [[nodiscard]] bool& isDirty() const {
            return dirty;
        }


        [[nodiscard]] std::vector<EntityStatsManager::Value> getDebuggingValues() {
            std::vector<EntityStatsManager::Value> values;
            EntityStatsManager::Value fovValue;
            fovValue.name = "Fov";
            fovValue.data = reinterpret_cast<void*>(&fovDegrees);
            fovValue.type = EntityStatsManager::ValueType::FLOAT;
            fovValue.isModifiable = true;
            fovValue.usesSlider = true;
            fovValue.valueDirty = &dirty;
            fovValue.min = 0.0f;
            fovValue.max = 180.0f;
            values.push_back(fovValue);

            EntityStatsManager::Value viewWidthValue;
            viewWidthValue.name = "View Width";
            viewWidthValue.data = reinterpret_cast<void*>(&viewWidth);
            viewWidthValue.type = EntityStatsManager::ValueType::FLOAT;
            viewWidthValue.isModifiable = true;
            viewWidthValue.usesSlider = true;
            viewWidthValue.valueDirty = &dirty;
            viewWidthValue.min = 0.0f;
            viewWidthValue.max = 1000.0f;
            values.push_back(viewWidthValue);

            EntityStatsManager::Value viewHeightValue;
            viewHeightValue.name = "View Height";
            viewHeightValue.data = reinterpret_cast<void*>(&viewHeight);
            viewHeightValue.type = EntityStatsManager::ValueType::FLOAT;
            viewHeightValue.isModifiable = true;
            viewHeightValue.usesSlider = true;
            viewHeightValue.valueDirty = &dirty;
            viewHeightValue.min = 0.0f;
            viewHeightValue.max = 1000.0f;
            values.push_back(viewHeightValue);

            EntityStatsManager::Value nearPlaneValue;
            nearPlaneValue.name = "Near Plane";
            nearPlaneValue.data = reinterpret_cast<void*>(&nearPlane);
            nearPlaneValue.type = EntityStatsManager::ValueType::FLOAT;
            nearPlaneValue.isModifiable = true;
            nearPlaneValue.usesSlider = true;
            nearPlaneValue.valueDirty = &dirty;
            nearPlaneValue.min = 0.0f;
            nearPlaneValue.max = 1000.0f;
            values.push_back(nearPlaneValue);

            EntityStatsManager::Value farPlaneValue;
            farPlaneValue.name = "Far Plane";
            farPlaneValue.data = reinterpret_cast<void*>(&farPlane);
            farPlaneValue.type = EntityStatsManager::ValueType::FLOAT;
            farPlaneValue.isModifiable = true;
            farPlaneValue.usesSlider = true;
            farPlaneValue.valueDirty = &dirty;
            farPlaneValue.min = 0.0f;
            farPlaneValue.max = 1000.0f;
            values.push_back(farPlaneValue);

            return values;
        }

        [[nodiscard]] std::string toString() const {
            return std::string("\n\tfov: ")
                + std::to_string(fovDegrees)
                + std::string("\n\tviewWidth: ")
                + std::to_string(viewWidth)
                + std::string("\n\tviewHeight: ")
                + std::to_string(viewHeight)
                + std::string("\n\tnearPlane: ")
                + std::to_string(nearPlane)
                + std::string("\n\tfarPlane: ")
                + std::to_string(farPlane);
        }

    private:
        Math::Distance fovDegrees{60.0f};
        Math::Distance viewWidth{1000};
        Math::Distance viewHeight{600};
        Math::Distance nearPlane{0.1f};
        Math::Distance farPlane{300};
        mutable bool dirty{true};

    }; // class CameraPerspective
} // namespace GLESC::Render
