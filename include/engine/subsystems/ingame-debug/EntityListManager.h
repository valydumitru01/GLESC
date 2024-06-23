/**************************************************************************************************
 * @file   EntityListManager.h
 * @author Valentin Dumitru
 * @date   28/05/2024
 * @brief  Class that manages the list of entities in the scene.
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "engine/EntityTypes.h"

#include <set>
#include <string>


namespace GLESC {
    /**
     * @brief Struct that holds the name and type of an entity.
     */
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

    /**
     * @brief Class that manages the list of entities in the scene.
     * @details It allows adding, removing, and selecting entities.
     * This class will be rendered by the EntityListHUD.
     * It is static because it's logic and data are simple and it benefits from being accessed from anywhere.
     */
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