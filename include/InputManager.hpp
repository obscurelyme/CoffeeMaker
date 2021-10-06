#ifndef _coffeemaker_inputmanager_hpp
#define _coffeemaker_inputmanager_hpp

#include <SDL2/SDL.h>

#include <array>

namespace CoffeeMaker {

  struct KeyboardInputEvent {
    bool IsHeld;
    bool IsPressed;
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
