/**************************************************************************************************
 * @file   ComponentArray.h
 * @author Valentin Dumitru
 * @date   2024-04-17
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

#pragma once

#include "engine/core/asserts/Asserts.h"
#include "engine/ecs/ECSTypes.h"
#include "engine/core/logger/Logger.h"
#include "IComponent.h"

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

        virtual void entityDestroyed(EntityID entity) = 0;

        virtual size_t getSize() = 0;
    };

    /**
     * @brief The ComponentArray class is a template class that stores components of a specific type
     * @tparam Component The type of component to store
     */
    template <typename Component>
    class ComponentArray : public IComponentArray {
    public:
        ComponentArray() = default;
        /**
         * @brief Get the component of the entity
         * @param entity The entity to get the component from
         * @return The component of the entity
         */
        IComponent& getComponent(EntityID entity) override {
            D_ASSERT_TRUE(hasComponent(entity), "Entity does not have component");
            return componentArray[entityToIndexMap.at(entity)];
        }

        /**
         * @brief Inserts the data of the entity into the array
         * @details The entity is added to the end of the array
         * It is also added to some maps for quick lookup
         * @param entity The entity to insert
         * @param component The component to insert
         */
        void insertData(EntityID entity,const Component& component) {
            PRINT_COMPONENT_ARRAY_STATUS(
                "Before inserting component:\n"
                "\t" + component.toString() + "\n"
                "\tfrom entity " + std::to_string(entity));

            // If the entity already has a component in this array, do nothing
            if (hasComponent(entity)) return;
            // Put new entry at end and update the maps
            size_t newIndex = size;
            entityToIndexMap[entity] = newIndex;
            indexToEntityMap[newIndex] = entity;
            //componentArray[newIndex] = component;

            new(&componentArray[newIndex]) Component(std::move(component));
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
        void removeData(EntityID entity) {
            PRINT_COMPONENT_ARRAY_STATUS("Before removing data from entity " + std::to_string(entity));
            D_ASSERT_TRUE(hasComponent(entity), "Entity does not have component");

            // Copy element at end into deleted element's place to maintain density
            size_t indexOfRemovedEntity = entityToIndexMap[entity];
            size_t indexOfLastElement = size - 1;
            // Call destructor on removed component, it is not called automatically causing bugs and memory leaks
            componentArray[indexOfRemovedEntity].~Component();
            new(&componentArray[indexOfRemovedEntity]) Component(std::move(componentArray[indexOfLastElement]));

            // Update map to point to moved spot
            EntityID entityOfLastElement = indexToEntityMap[indexOfLastElement];

            entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
            indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

            // Erase the entity from both maps
            entityToIndexMap.erase(entity);
            indexToEntityMap.erase(indexOfLastElement);
            --size;

            PRINT_COMPONENT_ARRAY_STATUS("After removing data from entity " + std::to_string(entity));
        }

        /**
         * @brief Get the data of the entity
         * @param entity The entity to get the data from
         * @return The data of the entity
         */
        Component& getData(EntityID entity) {
            D_ASSERT_TRUE(hasComponent(entity), "Entity does not have component");

            // Return a reference to the entity's component
            return componentArray[entityToIndexMap[entity]];
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

        /**
         * @brief Called when an entity is destroyed
         * @details The entity is removed from the array
         * @param entity The entity that was destroyed
         */
        void entityDestroyed(EntityID entity) override {
            if (entityToIndexMap.find(entity) != entityToIndexMap.end()) {
                removeData(entity);
            }
        }

    private:
        /**
         * @brief Print the status of the component array
         * @param context The context of the status
         */
        void printStatus(const std::string& context) {
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
