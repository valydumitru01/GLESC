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

#include <mutex>

#include "engine/subsystems/renderer/texture/Texture.h"
#include "engine/subsystems/transform/TransformTypes.h"


enum class HudItemType {
    LIGHT_SPOT,
    SUN,
    FOG
};

[[nodiscard]] inline std::string itemToString(HudItemType type) {
    switch (type) {
    case HudItemType::LIGHT_SPOT:
        return "LIGHT";
    case HudItemType::SUN:
        return "SUN";
    case HudItemType::FOG:
        return "FOG";
    default:
        return "UNKNOWN";
    }
}

struct Item {
    HudItemType type{};
    const GLESC::Transform::Position* worldPosition{};
};

/**
 * @brief Class that manages the items that are displayed in the HUD.
 * @details This class stores the items that are not displayed by the renderer but are displayed in the HUD while
 * debugging.
 */
class HudItemsManager {
public:
#ifndef NDEBUG_GLESC
    static void addItem(HudItemType type, const GLESC::Transform::Position& worldPosition);
    [[nodiscard]] static std::vector<Item> getItems() { return items; }
    static void clearItems() { items.clear(); }
#else
    static void addItem(HudItemType type, const GLESC::Transform::Position& worldPosition) {
        (void)type;
        (void)worldPosition;
    }
    [[nodiscard]] static std::vector<Item> getItems() { return {}; }
#endif
private:
#ifndef NDEBUG_GLESC

    static std::vector<Item> items;
    static std::mutex itemsMutex;
#endif
}; // class HudItemsManager