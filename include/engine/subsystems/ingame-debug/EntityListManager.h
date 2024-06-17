/**************************************************************************************************
 * @file   EntityListManager.h
 * @author Valentin Dumitru
 * @date   28/05/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "engine/EntityTypes.h"

#include <set>
#include <string>


namespace GLESC {
    struct EntityListItem {
        const std::string* name;
        GLESC::EntityType type;

        bool operator<(const EntityListItem& other) const {
            return *name < *other.name;
        }

        bool operator==(const EntityListItem& other) const {
            return *name == *other.name;
        }
    };

    class EntityListManager {
    public:
        static void addEntity(const std::string& entity, GLESC::EntityType type);
        [[nodiscard]] static auto& getEntities() { return entities; }
        static void setSelectedEntity(const std::string& entityName) { selectedEntity = entityName; }
        [[nodiscard]] static auto getSelectedEntity() { return selectedEntity; }
        static void entityRemoved(const std::string& entity);

    private:
        static std::set<EntityListItem> entities;
        static std::string selectedEntity;
    }; // class EntityListManager
}