/**************************************************************************************************
 * @file   HudItemsManager.cpp
 * @author Valentin Dumitru
 * @date   2024-04-17
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#include "engine/subsystems/ingame-debug/HudItemsManager.h"

#ifndef NDEBUG_GLESC
  std::vector<Item> HudItemsManager::items = {};
std::mutex HudItemsManager::itemsMutex{};


void HudItemsManager::addItem(HudItemType type, const GLESC::Transform::Position& worldPosition) {
    Item item;
    item.worldPosition = &worldPosition;
    item.type = type;
    {
        std::lock_guard lock(itemsMutex);
        items.push_back(item);
    }
}

#endif
