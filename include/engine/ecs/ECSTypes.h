/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <memory>
#include <bitset>
#include <cstdint>

#include "engine/Config.h"

namespace GLESC::ECS {
    class IComponentArray;

    using SystemID = std::uint8_t;
    /**
     * @brief Type of each ID of each entity
     */
    using EntityID = std::uint16_t;
    /**
     * @brief Type of the ID of each instance type (e.g. enemy, bullet, etc.)
     */
    using InstanceID = std::uint16_t;
    /**
     * @brief Type of the ID of each component
     */
    using ComponentID = std::uint8_t;
    /**
     * @brief Component name
     */
    using ComponentName = std::string;
    /**
     * @brief System name
     */
    using SystemName = std::string;
    /**
     * @brief Entity name
     */
    using EntityName = std::string;
    /**
     * @brief Redefinition of the type of the pointer to the component array to
     * reduce verbosity
     */
    using IComponentArrayPtr = std::shared_ptr<IComponentArray>;
    /**
     * @brief Maximum amount of entities can there be at once
     */
    const static EntityID maxEntities = GLESC_ECS_MAX_ENTITIES;
    /**
     * @brief Maximum amount of components each entity can have
     */
    const static ComponentID maxComponents = GLESC_ECS_MAX_COMPONENTS;

    /**
     * @brief type of the signature of each entity.
     * I.e. if Transform has type 0, RigidBody has type 1, Gravity has type 2 and
     * an entity that “has” those three components would have a signature of 0b111
     * (bits 0, 1, and 2 are set).
     */
    using Signature = std::bitset<maxComponents>;
} // namespace GLESC::ECS
