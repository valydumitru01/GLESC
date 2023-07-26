#pragma once

#include <SDL2/SDL.h>
#include "InputTypes.h"
#include "InputKeys.h"

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
    InputManager();
    
    /**
    * @brief Destructs an instance of the InputManager class.
    */
    ~InputManager();
    
    /**
    * @brief Updates the input manager by processing the current input state.
    */
    void update();
    
    /**
    * @brief Checks if a specific key is currently pressed.
    * @param keycode - The key code to check.
    * @return true if the key is pressed, false otherwise.
    */
    bool isKeyPressed(GLESC::Key keycode);
    
    /**
    * @brief Retrieves the current mouse position.
    * @return the current mouse position as a MousePosition object.
    */
    MousePosition getMousePosition() { return mousePosition; };
private:
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
    
    /**
    * @struct MousePosition
    * @brief Represents the current mouse position.
    */
    MousePosition mousePosition; /**< The current mouse position. */
    KeyMap keyMap; /**< The key map that stores the current state of each key. */
};