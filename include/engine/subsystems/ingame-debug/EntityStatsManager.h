/**************************************************************************************************
 * @file   EntityStatsManager.h
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

#include "engine/ecs/ECSTypes.h"


class EntityStatsManager {
public:

    enum class ValueType {
        INT,
        FLOAT,
        STRING,
        BOOL,
        VEC2F,
        VEC3F,
        VEC4F,
        VEC2I,
        VEC3I,
        VEC4I,
        MAT2F,
        MAT3F,
        MAT4F,
        VEC2B,
        VEC3B,
        VEC4B,
    };
    struct Value {
        std::string name;
        std::string stringData;
        bool isString = false;

        void* data = nullptr;
        bool* valueDirty = nullptr;
        ValueType type;

        float min = 0.0f;
        float max = 1.0f;
        /**
         * @brief It only affects number values, including vectors
         */
        bool usesSlider = false;
        bool isModifiable = true;

    };


    struct ComponentData {
        std::string name;
        std::vector<Value>* values;
        std::function<std::vector<Value>()> getUpdatedValues;
    };

    struct EntityData {
        std::string name;
        std::vector<ComponentData> components;
    };

    static void setEntityData(EntityData data) { entityData = data; }
    static EntityData& getEntityData();
private:
    static EntityData entityData;
}; // class EntityStatsManager

