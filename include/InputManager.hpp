#ifndef _coffeemaker_inputmanager_hpp
#define _coffeemaker_inputmanager_hpp

#include <SDL2/SDL.h>

#include <array>

namespace CoffeeMaker {

  struct KeyboardInputEvent {
    /**
     * Approximately 0.5 seconds if the key does not receive a keyup event,
     * then the key will be considered held down.
     */
    bool IsHeld;
    /**
     * Key is considered pressed only in the frame in which the keydown event
     * was received.
     */
    bool IsPressed;
    /**
     * Key is declared "down" so long as the game received a keydown event, this
     * will remain true until a corresponding keyup event is received.
     */
    bool IsDown;
  };

  class InputManager {
    public:
    void static Init();
    bool static IsKeyDown(SDL_Scancode scanCode);
    bool static IsKeyUp(SDL_Scancode scanCode);
    bool static IsKeyPressed(SDL_Scancode scanCode);
    bool static IsKeyHeld(SDL_Scancode scanCode);

    void static KeyPressed(SDL_KeyboardEvent* event);
    void static KeyReleased(SDL_KeyboardEvent* event);
    void static ClearAllPresses();

    void static HandleKeyBoardEvent(SDL_KeyboardEvent* event);

    private:
    static std::array<KeyboardInputEvent, SDL_NUM_SCANCODES> _keys;
  };

}  // namespace CoffeeMaker

#endif
