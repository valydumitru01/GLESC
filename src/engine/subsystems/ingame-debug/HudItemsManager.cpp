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
