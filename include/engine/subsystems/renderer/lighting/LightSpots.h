/**************************************************************************************************
 * @file   LightSpots.h
 * @author Valentin Dumitru
 * @date   2024-04-02
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include <vector>
#include <algorithm>

#include "engine/subsystems/renderer/lighting/LightSpot.h"
#include "engine/subsystems/transform/Transform.h"

namespace GLESC::Render {

    struct LightData {
        const LightSpot *light;
        const Transform::Transform *transform;

        bool operator==(const LightSpot *other) const {
            return light == other;
        }
    }; // struct LightData

    class LightSpots {
    public:
        /**
         * @brief Default constructor.
         */
        LightSpots() = default;

        void addLight(const LightSpot &light, const Transform::Transform &transform) {
            if (std::find(lights.begin(), lights.end(), &light) != lights.end()) {
                return;
            }
            lights.push_back({&light, &transform});
        }

        void removeLight(LightSpot *light) {
            // std::remove orders the elements in the vector and puts the elements to be removed at the end
            // then it returns an iterator to the first element to be removed
            lights.erase(std::remove(lights.begin(), lights.end(), light), lights.end());
        }

        [[nodiscard]] const auto &getLights() const {
            return lights;
        }

    private:
        std::vector<LightData> lights{};
    }; // class LightSpots
} // namespace GLESC::Render
