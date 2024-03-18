/******************************************************************************
 * @file   SystemManager.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <unordered_map>
#include "engine/ecs/ECSTypes.h"

namespace GLESC::ECS {
    class SystemManager {
        friend class ECSCoordinator;

    public:
        SystemManager() = default;

        ~SystemManager() = default;

        [[nodiscard]] const std::unordered_map<SystemName, std::set<EntityID>>& getAllAssociatedEntities() const {
            return associatedEntities;
        }

        [[nodiscard]] const std::unordered_map<SystemName, Signature>& getSystemSignatures() const {
            return systemSignatures;
        }

        /**
         * @brief Gets the entities associated with a system. The system must be registered.
         * @param name The name of the system
         * @return A set of entities associated with the system
         */
        [[nodiscard]] const std::set<EntityID>& getAssociatedEntitiesOfSystem(const SystemName& name) const;



        /**
         * @brief Registers a system in the system manager. It initializes the system data
         * such as the signature and the associated entities. The system must not be registered.
         * @param name
         */
        void registerSystem(const SystemName& name);

        /**
         * @brief Adds a component requirement to a system, this changes the entities that are considered
         * associated with it. The system must be registered. The component must not be required by the system already.
         * @param name The name of the system
         * @param componentID The ID of the component
         */
        void addComponentRequirementToSystem(const SystemName& name, ComponentID componentID);




        /**
         * @brief Removes the entity from the systems it is associated with.
         * @param entity The ID of the destroyed entity
         */
        void entityDestroyed(EntityID entity);

        /**
         * @brief Adds the entity to the systems it is associated with and removes it from the systems it is no longer
         * associated with.
         * @param entity The ID of the entity
         * @param entitySignature The signature of the entity
         */
        void entitySignatureChanged(EntityID entity, Signature entitySignature);





        /**
         * @brief Checks if a system is registered
         * @param name The name of the system
         * @return True if the system is registered, false otherwise
         */
        [[nodiscard]] bool isSystemRegistered(const SystemName& name) const;

        /**
         * @brief Checks if an entity is associated with a system
         * @param name The name of the system
         * @param entity The ID of the entity
         * @return True if the entity is associated with the system, false otherwise
         */
        [[maybe_unused]] [[nodiscard]] bool isEntityAssociatedWithSystem(const SystemName& name, EntityID entity) const;
        /**
         * @brief Checks if a component is required by a system
         * @param system The name of the system
         * @param component The ID of the component
         * @return True if the component is required by the system, false otherwise
         */
        [[maybe_unused]] [[nodiscard]] bool isComponentRequiredBySystem(const SystemName& system,
                                                                        ComponentID component) const;


    protected:
        /**
         * @brief A map of the names of the systems and their associated entities
         */
        std::unordered_map<SystemName, std::set<EntityID>> associatedEntities{};
        /**
         * @brief A map of the names of the systems and their signatures
         */
        std::unordered_map<SystemName, Signature> systemSignatures{};
    };

} // namespace GLESC::ECS
