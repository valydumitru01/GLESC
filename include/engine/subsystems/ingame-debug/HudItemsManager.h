/**************************************************************************************************
 * @file   HudItemsManager.h
 * @author Valentin Dumitru
 * @date   2024-04-17
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

#include "engine/core/low-level-renderer/texture/Texture.h"
#include "engine/subsystems/transform/TransformTypes.h"


enum class HudItemType {
    LIGHT
};

[[nodiscard]] inline std::string itemToString(HudItemType type) {
    switch (type) {
    case HudItemType::LIGHT:
        return "LIGHT";
    }
    return "UNKNOWN";
}

struct Item {
    HudItemType type{};
    const GLESC::Transform::Position* worldPosition{};
};

class HudItemsManager {
public:
    static void addItem(HudItemType type, const GLESC::Transform::Position& worldPosition);
    [[nodiscard]] static std::vector<Item> getItems() { return items; }

private:
    static std::vector<Item> items;
}; // class HudItemsManager
