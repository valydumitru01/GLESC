/**************************************************************************************************
 * @file   EntityDataManager.h
 * @author Valentin Dumitru
 * @date   08/03/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024$ Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

struct ComponentDataFunctions {
    std::function<std::string()> name;
    std::unordered_map<std::string, std::function<std::string()>> nameValuePairs;
};


struct EntityDataFunctions {
    std::function<std::string()> name;
    std::vector<ComponentDataFunctions> components;
};

struct ComponentData {
    std::string name;
    std::unordered_map<std::string, std::string> nameValuePairs;
};

struct EntityData {
    std::string name;
    std::vector<ComponentData> components;
};

class EntityStatsManager {
public:
    void setEntityData(EntityDataFunctions data) { entityDataFuncs = data; }
    static EntityData getEntityData();
private:
    static EntityData generateEntityData();
    static EntityDataFunctions entityDataFuncs;
}; // class EntityStatsManager

