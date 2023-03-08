#pragma once
#include <memory>
#include <bitset>

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
 * @brief Maximum amount of entities can there be at once
 *
 */
const static EntityID Max_Entities = static_cast<EntityID>(5000);
/**
 * @brief Maximum amount of components each entity can have
 *
 */
const static ComponentID Max_Components = static_cast<ComponentID>(16);

/**
 * @brief type of the signature of each entity.
 * I.e. if Transform has type 0, RigidBody has type 1, Gravity has type 2 and
 * an entity that “has” those three components would have a signature of 0b111
 * (bits 0, 1, and 2 are set).
 *
 */
using Signature = std::bitset<Max_Components>;

