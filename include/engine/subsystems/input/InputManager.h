/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <deque>

#include "InputTypes.h"
#include "engine/core/window/WindowManager.h"
#include "engine/subsystems/hud/HUDManager.h"

namespace GLESC::Input {
    /**
     * @class InputManager
     * @brief The InputManager class handles user input events such as keyboard and mouse events.
     * It provides methods to initialize the input manager, update the input state, and check if a specific key is pressed.
     * The class also handles event handling functions for keyboard and mouse events.
     * The mouse position and key map are stored as private member variables.
     */
    class InputManager {
    public:
        /**
         * @brief Constructs an instance of the InputManager class.
         */
        InputManager(HUDManager& hudManager, WindowManager& windowManager);
        /**
        * @brief Nothing to delete, use default destructor.
        */
        ~InputManager() = default;

        /**
        * @brief Updates the input manager by processing the current input state.
        */
        void update(bool& running);

        /**
        * @brief Checks if a specific key is currently pressed.
        * @param keyInput - The key to check.
        * @return true if the key is pressed, false otherwise.
        */
        bool checkKeyAction(const KeyInput& keyInput);

        /**
        * @brief Retrieves the current mouse position.
        * @return the current mouse position as a MousePosition object.
        */
        const MousePosition getMousePosition() const { return mousePos; } ;
        /**
         * @brief Get the current pressed keys
         * @return A vector of all keys that are currently pressed
         */
        std::vector<Key> getPressedKeys() const;

        /**
         * @brief Enables mouse
         * If enabled mouse is visible and position is absolute (allows moving it across the window)
         * If disabled mouse is hidden and position is relative (stays in center)
         *
         * @param enabled true to enable, false to disable
         */
        void setMouseRelative(bool enabled);

        /**
         * @brief Gets whether the mouse is relative or not
         * @return true if mouse is relative, false otherwise
         */
        [[nodiscard]] bool isMouseRelative();

    private:
        // ============================================================================================
        // =========================================== Mouse ==========================================
        // ============================================================================================
        /**
         * @brief Adds the delta values of the mouse position to the delta buffer.
         * @param posDx - The delta x value of the mouse position.
         * @param posDy - The delta y value of the mouse position.
         */
        void addToBuffer(int posDx, int posDy);
        /**
         * @brief Calculates the average postion of the mouse from the delta buffer.
         * If the position is less than the deadzone, it will be set to 0.
         * @return the average mouse position of the mouse
         */
        MousePosition getAvgMousePos() const;
        /**
         * @brief Linearly interpolates the mouse position to smooth out the mouse movement.
         * @param oldMousePos - The old mouse position to interpolate from. This will get updated, it is not const.
         * @param targetMousePos - The target mouse position to interpolate to.
         */
        void lerpMousePos(MousePosition& oldMousePos, const MousePosition& targetMousePos) const;
        /**
         * @brief Handles the mouse event by updating the mouse position with the current mouse coordinates.
         * @param event - The mouse event to handle.
         */
        void handleMouseEvent(const SDL_Event& event);

        /**
         * @brief The buffer used to store the delta values of the mouse position.
         * @details This helps to smooth out the mouse movement.
         */
        std::deque<Vec2F> deltaBuffer;
        /**
         * @brief The size of the buffer used to store the delta values of the mouse position.
         */
        const size_t bufferSize = 5;
        /**
         * @brief The deadzone used to filter out small mouse movements.
         * @details SDL reports small mouse movements even when the mouse is not moving.
         * This deadzone helps to filter out.
         */
        const float deadzone = 1;
        /**
        * @brief Represents the current mouse position.
        */
        MousePosition mousePos{};
        /**
         * @brief The target mouse position used to smooth out the mouse movement.
         */
        MousePosition targetMousePos{};
        /**
         * @brief The smooth factor used to smooth out the mouse movement.
         */
        float mouseSmoothFactor{0.1f};


        // ============================================================================================
        // ============================================ Keys ==========================================
        // ============================================================================================


        /**
         * @brief Handles the keyboard event by updating the key map with the current key state.
         * @param event - The keyboard event to handle.
         */
        void handleKeyEvent(const SDL_Event& event);
        /**
         * @brief Updates the state of a specific key in the key map.
         * @details If the key is pressed, the key state is updated to pressed. If the key has just been pressed,
         * the key state is updated to just pressed. Also resets the key state if the key has been released.
         * @param key - The key to update.
         * @param pressed - The state of the key.
         */
        void updateKeyState(Key key, bool pressed);
        /**
         * @brief The key map used to store the state of each key.
         */
        KeyMap keyMap{};
        /**
         * @brief A map of bools used to detect if a key was pressed once. Will be initialized dynamically, if a key is
         * checked and its one time press is not initialized, it will be initialized with true (has been pressed once).
         */
        std::unordered_map<const KeyInput*, bool> pressedOnceDetection;

        // ============================================================================================
        // =========================================== Window =========================================
        // ============================================================================================
        void handleWindowEvent(const SDL_Event& event);

        WindowManager& windowManager;


        /**
         * @brief The HUDManager instance used to handle HUD events.
         */
        HUDManager& hudManager;
    };
}
