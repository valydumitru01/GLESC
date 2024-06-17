/**************************************************************************************************
 * @file   EngineComponent.h
 * @author Valentin Dumitru
 * @date   05/06/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include <string>

#include "ingame-debug/EntityStatsManager.h"

class EngineComponent {
public:
    virtual ~EngineComponent() = default;
    [[nodiscard]] virtual std::string toString() const = 0;

#ifndef NDEBUG_GLESC
    /**
     * @brief Set the owner name of the component for debugging purposes
     * @param ownerName The name of the owner entity
     */
    void setOwnerName(const char* ownerName) {
        entityOwnerName = ownerName;
    }

    [[nodiscard]] const char* getOwnerName() const {
        D_ASSERT_NOT_NULLPTR(entityOwnerName, "Owner name not set for EngineComponent");
        return entityOwnerName;
    }

    [[nodiscard]] virtual std::vector<EntityStatsManager::Value> getDebuggingValues() {
        return {};
    }

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
