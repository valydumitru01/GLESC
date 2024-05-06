/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <cassert>
#include "engine/ecs/ECSTypes.h"
#include "engine/core/logger/Logger.h"
#include "../../backend/component/IComponent.h"
#include "engine/ecs/backend/asserts/component/ComponentArrayAsserts.h"

#ifndef NDEBUG_ECS
#define PRINT_COMPONENT_ARRAY_STATUS(contextMessage) printStatus(contextMessage)
#else
#define PRINT_COMPONENT_ARRAY_STATUS(contextMessage)
#endif


namespace GLESC::ECS {
    class IComponentArray {
    public:
        virtual ~IComponentArray() = default;

        virtual bool hasComponent(EntityID entity) = 0;

        virtual IComponent& getComponent(EntityID entity) = 0;

        virtual void removeData(EntityID entity) = 0;

        virtual size_t getSize() = 0;
    };

    template <typename Component>
    class ComponentArray : public IComponentArray {
    public:
        ComponentArray() = default;

        IComponent& getComponent(EntityID entity) override {
            return componentArray[entityToIndexMap.at(entity)];
        }

        void insertData(EntityID entity, Component component) {
            PRINT_COMPONENT_ARRAY_STATUS(
                "Before inserting component:\n"
                "\t" + component.toString() + "\n"
                "\tfrom entity " + std::to_string(entity));


            // Put new entry at end and update the maps
            size_t newIndex = size;
            entityToIndexMap.insert({entity, newIndex});
            indexToEntityMap.insert({newIndex, entity});
            componentArray[newIndex] = component;
            ++size;


            PRINT_COMPONENT_ARRAY_STATUS(
                "After inserting component:\n"
                "\t" + component.toString() + "\n"
                "\tfrom entity " + std::to_string(entity));
        }


        /**
         * @brief Removes the data of the entity from the array
         * The last element in the array is copied into the place of the removed element
         * The maps are updated to reflect the changes
         * @param entity The entity to remove
         */
        void removeData(EntityID entity) override {
            PRINT_COMPONENT_ARRAY_STATUS("Before removing data from entity " + std::to_string(entity));

            // Copy element at end into deleted element's place to maintain density
            size_t indexOfRemovedEntity = entityToIndexMap.at(entity);
            size_t indexOfLastElement = size - 1;
            componentArray[indexOfRemovedEntity] = componentArray[indexOfLastElement];

            // Update map to point to moved spot
            EntityID entityOfLastElement = entityToIndexMap.at(indexOfLastElement);
            entityToIndexMap.insert({entityOfLastElement, indexOfRemovedEntity});
            indexToEntityMap.insert({indexOfRemovedEntity, entityOfLastElement});

            // Erase the entity from both maps
            entityToIndexMap.erase(entity);
            indexToEntityMap.erase(indexOfLastElement);
            --size;

            PRINT_COMPONENT_ARRAY_STATUS("After removing data from entity " + std::to_string(entity));
        }

        Component& getData(EntityID entity) {
            D_ASSERT_TRUE(entityExists(entity), "Entity does not exist");

            // Return a reference to the entity's component
            return componentArray[entityToIndexMap.at(entity)];
        }

        /**
         * @brief Checks if the entity has a component of type T
         * @details The check is useful to avoid adding or removing unnecessarily
         * The remove and add components does not allow doing so, so this is a way to check
         * @param entity
         * @return
         */
        bool hasComponent(EntityID entity) override {
            return entityToIndexMap.find(entity) != entityToIndexMap.end();
        }

        void entityDestroyed(EntityID entity) {
            if (entityToIndexMap.find(entity) != entityToIndexMap.end()) {
                removeData(entity);
            }
        }

        bool entityExists(EntityID entity) {
            return entityToIndexMap.find(entity) != entityToIndexMap.end();
        }

    private:
        void printStatus(std::string context) {
            Logger::get().importantInfoBlue("ComponentArray Status Report - Context: " + context);
            const char* componentName = typeid(Component).name();
            Logger::get().infoBlue("Component Type: " + std::string(componentName));
            Logger::get().infoBlue("Total Components: " + std::to_string(size));

            Logger::get().infoBlue("\tEntityToIndexMap size: " + std::to_string(entityToIndexMap.size()));
            for (const auto& entry : entityToIndexMap) {
                Logger::get().infoBlue(
                    "\tEntity ID: " + std::to_string(entry.first) + ", Array Index: " + std::to_string(entry.second));
            }

            Logger::get().infoBlue("\tcomponent array with size " + std::to_string(size) + ":");
            for (int i = 0; i < size; i++) {
                Logger::get().infoBlue("\t\t Component number " + i);
                Logger::get().infoBlue("\t\t" + componentArray[i].toString()); // All components have a toString()
            }
        }

        /**
         * @brief The packed array of components (of generic type T),
         * set to a specified maximum amount, matching the maximum number
         * of entities allowed to exist simultaneously, so that each entity
         * has a unique spot.
         */
        std::array<Component, maxEntities> componentArray;

        /**
         * @brief Map from an entity ID to an array index.
         *
         */
        std::unordered_map<EntityID, size_t> entityToIndexMap;
        std::unordered_map<size_t, EntityID> indexToEntityMap;

        /**
         * @brief Total size of valid entries in the array.
         *
         */
        size_t size{};

        size_t getSize() override {
            return size;
        }
    }; // class ComponentArray
} // namespace GLESC::ECS
