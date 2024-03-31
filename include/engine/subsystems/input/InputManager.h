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

namespace GLESC {
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
        InputManager(HUDManager &hudManager);

        /**
        * @brief Destructs an instance of the InputManager class.
        */
        ~InputManager() = default;

        /**
        * @brief Updates the input manager by processing the current input state.
        */
        void update(bool &running);

        /**
        * @brief Checks if a specific key is currently pressed.
        * @param keyInput - The key to check.
        * @return true if the key is pressed, false otherwise.
        */
        bool checkKeyAction(const KeyInput &keyInput);

        /**
        * @brief Retrieves the current mouse position.
        * @return the current mouse position as a MousePosition object.
        */
        const MousePosition getMousePosition() const { return mousePosition; } ;

        const std::vector<GLESC::Key> getPressedKeys() const {
            std::vector<GLESC::Key> pressedKeys;
            for (auto &key : keyMap) {
                if (key.second.pressed) {
                    pressedKeys.push_back(key.first);
                }
            }
            return pressedKeys;
        }

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
        void updateKeyState(GLESC::Key key, bool pressed);


        /**
         * @brief Handles the SDL event by determining the type of event and calling the appropriate event handling function.
         * @param event - The SDL event to handle.
         */
        void handleEvent(const SDL_Event &event);

        /**
        * @brief Handles the keyboard event by updating the key map with the current key state.
        * @param event - The keyboard event to handle.
        */
        void handleKeyEvent(const SDL_Event &event);

        /**
        * @brief Handles the mouse event by updating the mouse position with the current mouse coordinates.
        * @param event - The mouse event to handle.
        */
        void handleMouseEvent(const SDL_Event &event);

        void addToBuffer(int dx, int dy);

        MousePosition getSmoothedMousePos();

        /**
        * @struct MousePosition
        * @brief Represents the current mouse position.
        */
        MousePosition mousePosition; /* The current mouse position. */
        KeyMap keyMap; /* The key map that stores the current state of each key. */
        /**
         * @brief A map of bools used to detect if a key was pressed once. Will be initialized dynamically, if a key is
         * checked and its one time press is not initialized, it will be initialized with true (has been pressed once).
         */
        std::unordered_map<const KeyInput *, bool> pressedOnceDetection;

        /**
         * @brief The HUDManager instance used to handle HUD events.
         */
        HUDManager &hudManager;

        /**
         * @brief The buffer used to store the delta values of the mouse position.
         * @details This helps to smooth out the mouse movement.
         */
        std::deque<SDL_Point> deltaBuffer;
        /**
         * @brief The size of the buffer used to store the delta values of the mouse position.
         */
        const size_t bufferSize = 5;
        /**
         * @brief The deadzone used to filter out small mouse movements.
         * @details SDL reports small mouse movements even when the mouse is not moving.
         * This deadzone helps to filter out.
         */
        const int deadzone = 1;
    };
}
