/**************************************************************************************************
 * @file   EntityStatsManager.cpp
 * @author Valentin Dumitru
 * @date   08/03/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024$ Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#include "engine/subsystems/ingame-debug/EntityStatsManager.h"


// Define the static members
EntityDataFunctions EntityStatsManager::entityDataFuncs = {};

EntityData EntityStatsManager::generateEntityData() {
    EntityData entityData;
    entityData.name = "Entity";
    ComponentData componentData;
    for (auto& component : entityDataFuncs.components) {
        componentData.name = component.name();
        componentData.nameValuePairs["Name"] = component.name();
        componentData.nameValuePairs["Data"] = component.dataString();
    }
    return entityData;
}

EntityData EntityStatsManager::getEntityData() {
    EntityData entityDataResult;
    entityDataResult = generateEntityData();

    return entityDataResult;
}
