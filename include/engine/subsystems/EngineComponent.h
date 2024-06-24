/**************************************************************************************************
 * @file   EngineComponent.h
 * @author Valentin Dumitru
 * @date   05/06/2024
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include <string>

#include "ingame-debug/EntityStatsManager.h"

/**
 * @brief Class that represents a component of the engine
 * @details A component in the engine is a encapsulated piece of data with functionality that can be attached to an
 * entity. It can be a camera, a physics component, a transform component, etc.
 * This abstraction is useful for, for example, debugging purposes, where we can get all the debugging values as
 * a list and abstrat away the implementation details of the component iterating over all the components.
 * Also allows storing the owner name (the entity name) for debugging purposes.
 */
class EngineComponent {
public:
    virtual ~EngineComponent() = default;
    [[nodiscard]] virtual std::string toString() const = 0;

#ifndef NDEBUG_GLESC
    /**
     * @brief Set the owner name of the component for debugging purposes
     * @details Having the owener associated with the component is specially useful when debugging, as it allows
     * to know which entity the component belongs to no matter the context of debugging.
     * @param ownerName The name of the owner entity
     */
    void setOwnerName(const char* ownerName) {
        entityOwnerName = ownerName;
    }

    /**
     * @brief Get the owner name of the component for debugging purposes
     * @details Having the owener associated with the component is specially useful when debugging, as it allows
     * to know which entity the component belongs to no matter the context of debugging.
     * @return The name of the owner entity
     */
    [[nodiscard]] const char* getOwnerName() const {
        D_ASSERT_NOT_NULLPTR(entityOwnerName, "Owner name not set for EngineComponent");
        return entityOwnerName;
    }

    /**
     * @brief Get the debugging values of the component
     * @details This function can be overriden by the derived class to return the debugging values of the component
     * It starts as an empty vector, so that the components that accumulates all the debugging values can add the
     * debugging values of the component even if the component does not have any debugging values (adding an empty
     * array)
     * @return A vector of debugging values
     */
    [[nodiscard]] virtual std::vector<EntityStatsManager::Value> getDebuggingValues() {
        return {};
    }

    /**
     * @brief Get the updated debugging values of the component
     * @details This function can be overriden by the derived class to return the updated debugging values of the
     * component
     * It starts as an empty vector, so that the components that accumulates all the debugging values can add the
     * debugging values of the component even if the component does not have any debugging values (adding an empty
     * array)
     * @return A vector of debugging values
     */
    [[nodiscard]] virtual std::vector<EntityStatsManager::Value> getUpdatedDebuggingValues() {
        return {};
    }
#else
    /**
     * @brief In release mode, this function is empty
     * @param ownerName The name of the owner entity
     */
    void setOwnerName(const char* ownerName) {}

#endif

private:
#ifndef NDEBUG_GLESC
    const char* entityOwnerName = nullptr;
#endif
}; // class EngineComponent
