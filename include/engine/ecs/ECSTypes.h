/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <memory>
#include <bitset>
#include <set>

#include "engine/Config.h"

class IComponentArray;


using SystemID = std::uint8_t;
/**
 * @brief Type of each ID of each entity
 *
 */
using EntityID = std::uint16_t;
/**
 * @brief Type of the ID of each component
 *
 */
using ComponentID = std::uint8_t;
/**
 * @brief Component name
 */
using ComponentName = const char *;
/**
 * @brief System name
 */
using SystemName = const char *;
/**
 * @brief
 */
using EntityName = const char *;
/**
 * @brief
 */
using IComponentArrayPtr = std::shared_ptr <IComponentArray>;
/**
 * @brief Maximum amount of entities can there be at once
 *
 */
const static EntityID maxEntities = static_cast<EntityID>(GLESC_ECS_MAX_ENTITIES);
/**
 * @brief Maximum amount of components each entity can have
 *
 */
const static ComponentID maxComponents = static_cast<ComponentID>(GLESC_ECS_MAX_COMPONENTS);

/**
 * @brief type of the signature of each entity.
 * I.e. if Transform has type 0, RigidBody has type 1, Gravity has type 2 and
 * an entity that “has” those three components would have a signature of 0b111
 * (bits 0, 1, and 2 are set).
 *
 */
using Signature = std::bitset<maxComponents>;

/**
 * @brief Type of each system
 * @details A system is a pair of a signature and a set of entities.
 */
typedef std::pair <Signature, std::set <EntityID>> SystemData;