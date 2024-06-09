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

#ifndef NDEBUG
    void setOwnerName(const char* ownerName) {
        entityOwnerName = ownerName;
    }

    const char* getOwnerName() const {
        D_ASSERT_NOT_NULLPTR(entityOwnerName, "Owner name not set for EngineComponent");
        return entityOwnerName;
    }

    [[nodiscard]] virtual std::vector<EntityStatsManager::Value> getDebuggingValues() = 0;
    [[nodiscard]] virtual std::string toString() const = 0;

    [[nodiscard]] virtual std::vector<EntityStatsManager::Value> getUpdatedDebuggingValues() {
        return std::vector<EntityStatsManager::Value>();
    }

#endif

private:
#ifndef NDEBUG
    const char* entityOwnerName = nullptr;
#endif
}; // class EngineComponent
