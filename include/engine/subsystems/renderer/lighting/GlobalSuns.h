/**************************************************************************************************
 * @file   GlobalSuns.h
 * @author Valentin Dumitru
 * @date   2024-04-30
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "GlobalSun.h"
#include "engine/subsystems/transform/Transform.h"


namespace GLESC::Render {
    struct GlobalSunData {
        const GlobalSun *sun;
        const Transform::Transform *transform;

        bool operator==(const GlobalSun *other) const {
            return sun == other;
        }
    }; // struct LightData

    class GlobalSuns {
    public:
        /**
         * @brief Default constructor.
         */
        GlobalSuns() = default;

        void addSun(const GlobalSun &light, const Transform::Transform &transform) {
            if (std::find(suns.begin(), suns.end(), &light) != suns.end()) {
                return;
            }
            suns.push_back({&light, &transform});
        }

        void removeSun(GlobalSun &light) {
            // std::remove orders the elements in the vector and puts the elements to be removed at the end
            // then it returns an iterator to the first element to be removed
            suns.erase(std::remove(suns.begin(), suns.end(), &light), suns.end());
        }

        [[nodiscard]] const auto &getSuns() const {
            return suns;
        }

    private:
        std::vector<GlobalSunData> suns{};
    }; // class LightSpots
}
