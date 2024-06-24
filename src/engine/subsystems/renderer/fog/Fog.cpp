/**************************************************************************************************
 * @file   Fog.cpp
 * @author Valentin Dumitru
 * @date   14/06/2024
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

#include "engine/subsystems/renderer/fog/Fog.h"
using namespace GLESC::Render;
#ifndef NDEBUG_GLESC
  std::vector<EntityStatsManager::Value> Fog::getDebuggingValues()  {
 std::vector<EntityStatsManager::Value> values;
 EntityStatsManager::Value densityValue;
 densityValue.name = "Density";
 densityValue.data = reinterpret_cast<void*>(&density.getModifiable());
 densityValue.type = EntityStatsManager::ValueType::FLOAT;
 densityValue.isModifiable = true;
 densityValue.usesSlider = true;
 densityValue.min = 0.0f;
 densityValue.max = 1.0f;
 values.push_back(densityValue);

 EntityStatsManager::Value endValue;
 endValue.name = "End";
 endValue.data = reinterpret_cast<void*>(&end);
 endValue.type = EntityStatsManager::ValueType::FLOAT;
 endValue.isModifiable = true;
 endValue.usesSlider = true;
 endValue.min = 0.0f;
 endValue.max = 1000.0f;
 values.push_back(endValue);

 EntityStatsManager::Value colorValue;
 colorValue.name = "Color";
 colorValue.data = reinterpret_cast<void*>(&color);
 colorValue.type = EntityStatsManager::ValueType::VEC3F;
 colorValue.isModifiable = true;
 colorValue.usesSlider = true;
 colorValue.min = 0.0f;
 colorValue.max = 255.0f;
 values.push_back(colorValue);


 return values;
}
#endif
std::string Fog::toString() const {
    std::string str = "Density: " + std::to_string(density.get()) + "\n";
    str += "Color: " + color.toString() + "\n";

    return str;
}
