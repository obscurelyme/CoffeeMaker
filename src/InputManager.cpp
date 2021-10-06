#include "InputManager.hpp"

#include "Logger.hpp"

using namespace CoffeeMaker;

std::array<KeyboardInputEvent, SDL_NUM_SCANCODES> InputManager::_keys = {};

void InputManager::Init() {
  KeyboardInputEvent e = {.IsHeld = false, .IsPressed = false};
  _keys.fill(e);
}

void InputManager::KeyPressed(SDL_KeyboardEvent* event) { _keys[event->keysym.scancode].IsPressed = true; }

void InputManager::KeyReleased(SDL_KeyboardEvent* event) { _keys[event->keysym.scancode].IsPressed = false; }

void InputManager::ClearAllPresses() {
  for (auto& key : _keys) {
    key.IsPressed = false;
  }
}

void InputManager::HandleKeyBoardEvent(SDL_KeyboardEvent* event) {
  if (event->state == SDL_PRESSED) {
    if (!event->repeat) {
      _keys[event->keysym.scancode].IsPressed = true;
      _keys[event->keysym.scancode].IsHeld = false;
    } else {
      _keys[event->keysym.scancode].IsPressed = false;
      _keys[event->keysym.scancode].IsHeld = true;
    }
  }

  if (event->state == SDL_RELEASED) {
    _keys[event->keysym.scancode].IsPressed = false;
    _keys[event->keysym.scancode].IsHeld = false;
  }
}

bool InputManager::IsKeyDown(SDL_Scancode scanCode) { return _keys[scanCode].IsPressed; }

bool InputManager::IsKeyUp(SDL_Scancode scanCode) { return !_keys[scanCode].IsPressed; }

bool InputManager::IsKeyPressed(SDL_Scancode scanCode) { return _keys[scanCode].IsPressed; }

bool InputManager::IsKeyHeld(SDL_Scancode scanCode) { return _keys[scanCode].IsHeld; }
