/**************************************************************************************************
 * @file   HudItemsManager.cpp
 * @author Valentin Dumitru
 * @date   2024-04-17
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#include "engine/subsystems/ingame-debug/HudItemsManager.h"

std::vector<Item> HudItemsManager::items = {};


void HudItemsManager::addItem(HudItemType type, const GLESC::Transform::Position& worldPosition) {
    bool found = std::any_of(items.begin(), items.end(), [worldPosition](const Item& item) {
        return item.worldPosition == &worldPosition;
    });
    if (found) {
        return;
    }
    Item item;
    item.worldPosition = &worldPosition;
    item.type = type;
    items.push_back(item);
}
