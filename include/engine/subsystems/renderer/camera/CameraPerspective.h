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

        [[nodiscard]] float getFovDegrees() const {
            return fovDegrees;
        }

        [[nodiscard]] float getViewWidth() const {
            return viewWidth;
        }

        [[nodiscard]] float getViewHeight() const {
            return viewHeight;
        }

        [[nodiscard]] float getNearPlane() const {
            return nearPlane;
        }

        [[nodiscard]] float getFarPlane() const {
            return farPlane;
        }

        void setFovDegrees(Math::Distance fovDegrees) {
            this->fovDegrees = fovDegrees;
            dirty = true;
        }

        void setViewWidth(Math::Distance viewWidth) {
            this->viewWidth = viewWidth;
            dirty = true;
        }

        void setViewHeight(Math::Distance viewHeight) {
            this->viewHeight = viewHeight;
            dirty = true;
        }

        void setNearPlane(Math::Distance nearPlane) {
            this->nearPlane = nearPlane;
            dirty = true;
        }

        void setFarPlane(Math::Distance farPlane) {
            this->farPlane = farPlane;
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

#ifndef NDEBUG_GLESC
        [[nodiscard]] std::vector<EntityStatsManager::Value> getDebuggingValues() ;
#endif
        [[nodiscard]] std::string toString() const ;

    private:
        Math::Distance fovDegrees{60.0f};
        Math::Distance viewWidth{1000};
        Math::Distance viewHeight{600};
        Math::Distance nearPlane{0.1f};
        Math::Distance farPlane{300};
        mutable bool dirty{true};

    }; // class CameraPerspective
} // namespace GLESC::Render
