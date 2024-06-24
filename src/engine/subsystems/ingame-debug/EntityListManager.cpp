/**************************************************************************************************
 * @file   EntityListManager.cpp
 * @author Valentin Dumitru
 * @date   28/05/2024
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

#include "engine/subsystems/ingame-debug/EntityListManager.h"

using namespace GLESC;
std::set<EntityListItem> EntityListManager::entities;
std::string EntityListManager::selectedEntity;

void EntityListManager::addEntity(const std::string& entity, EntityType type) {
    entities.insert({&entity, type});
}

void EntityListManager::entityRemoved(const std::string& entity) {
    entities.erase({&entity, EntityType::Default});
    if(selectedEntity == entity) selectedEntity.clear();
}
