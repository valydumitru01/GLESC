/******************************************************************************
 * @file   IComponent.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once
#include <string>

#include "engine/subsystems/ingame-debug/EntityStatsManager.h"

namespace GLESC::ECS {
    /**
     * @brief Base class for all components
     * @details All components must inherit from this class and
     * must implement all the pure virtual functions.
     * This is necessary for the derived classes to be used in the ECS.
     */
    struct IComponent {
        virtual ~IComponent() = default;
        /**
         * @brief Each component must have a toString function
         * @details This is needed because when we want to debug the
         * content of the components, we need to be able to
         * do it without knowing the specific type of the component.
         * This is because we are using a vector of IComponents.
         * @return
         */
        [[nodiscard]] virtual std::string toString() const = 0;

        [[nodiscard]] virtual std::string getName() const = 0;
#ifndef NDEBUG_GLESC
        /**
         * @brief Get the debugging values of the component
         * @details This function is used to get the debugging values
         * of the component. The values are stored in a vector of
         * EntityStatsManager::Value. This vector is used by the
         * EntityStatsManager to display the debugging values of
         * all the components of an entity.
         * This will be used by the HUD to display the values of each
         * component and allow mid-game debugging and modifications.
         * This function is called only once when the values vector
         * so it will not be called every frame and there will be not
         * update.
         * @return The debugging values of the component
         */
        std::vector<EntityStatsManager::Value>& getDebuggingValues() {
            if (!values.empty()) return values;
            setDebuggingValues();
            return values;
        }

        /**
         * @brief Get the updated debugging values of the component
         * @details This function is used to get the updated debugging values
         * of the component. The values are stored in a vector of
         * EntityStatsManager::Value. This vector is used by the
         * EntityStatsManager to display the debugging values of
         * all the components of an entity.
         * This will be used by the HUD to display the values of each
         * component and allow mid-game debugging and modifications.
         * This function is called every frame to get the updated values
         * of the component.
         * @return The updated debugging values of the component
         */
        std::vector<EntityStatsManager::Value> getUpdatedDebuggingValues() {
            setUpdatedDebuggingValues();
            std::vector<EntityStatsManager::Value> updatedValuesAux = updatedValues;
            updatedValues.clear();
            return updatedValuesAux;
        }
#endif
    protected:
#ifndef NDEBUG_GLESC
        /**
         * @brief Set the debugging values of the component
         * @details This function must be implemented by the derived
         * classes. This function is used to set the specific debugging values
         * of the component.
         * @return The specifc debugging values of the component
         */
        virtual void setDebuggingValues() = 0;
        /**
         * @brief Set the updated debugging values of the component
         * @details This function can be implemented by the derived
         * classes, but not always necessary.
         * This function is used to set the specific updated debugging values
         * of the component.
         * @return The specifc updated debugging values of the component
         */
        virtual void setUpdatedDebuggingValues() {}
        /**
         * @brief The debugging values of the component
         * @details This vector is used to store the debugging values
         * of the component. This vector is used by the EntityStatsManager
         * to store the debugging values of the component. And then used
         * by the HUD to display the values of each component and allow
         * mid-game debugging and modifications.
         */
        std::vector<EntityStatsManager::Value> values;
        /**
         * @brief The updated debugging values of the component
         * @details This vector is used to store the updated debugging values
         * of the component. This vector is used by the EntityStatsManager
         * to store the updated debugging values of the component. And then used
         * by the HUD to display the values of each component and allow
         * mid-game debugging and modifications.
         * These values will be updated every frame.
         */
        std::vector<EntityStatsManager::Value> updatedValues;
#endif
    };
} // namespace GLESC::ECS
