#include "Events/MouseEvents.hpp"

unsigned int CoffeeMaker::IMouseListener::_uid = 0;
std::vector<CoffeeMaker::IMouseListener*> CoffeeMaker::IMouseListener::_listeners = {};

void CoffeeMaker::MouseEventHandler::HandleMouseEvents(const SDL_Event& event) {
  if (event.type == SDL_MOUSEBUTTONUP || event.type == SDL_MOUSEBUTTONDOWN) {
    CoffeeMaker::IMouseListener::ProcessMouseButtonEvent(event.button);
  }

  if (event.type == SDL_MOUSEMOTION) {
    CoffeeMaker::IMouseListener::ProcessMouseMotionEvent(event.motion);
  }

  if (event.type == SDL_MOUSEWHEEL) {
    CoffeeMaker::IMouseListener::ProcessMouseWheelEvent(event.wheel);
  }

  ClearMouseEvents();
}

void CoffeeMaker::MouseEventHandler::ClearMouseEvents() { CoffeeMaker::IMouseListener::RemoveStaleListeners(); }

CoffeeMaker::IMouseListener::IMouseListener() : _active(true), _id(++_uid) {
  _listeners.push_back(this);
  _index = _listeners.size() - 1;
}

CoffeeMaker::IMouseListener::~IMouseListener() { _listeners[_index] = nullptr; }

void CoffeeMaker::IMouseListener::RemoveStaleListeners() {
  for (auto it = _listeners.begin(); it != _listeners.end();) {
    if ((*it) == nullptr) {
      it = _listeners.erase(it);
    } else {
      ++it;
    }
  }
}

void CoffeeMaker::IMouseListener::ProcessMouseWheelEvent(const SDL_MouseWheelEvent& event) {
  // NOTE: process the listeners for the current frame.
  // any added listeners during this process loop are not counted.
  unsigned int currentSize = _listeners.size();

  for (unsigned int i = 0; i < currentSize; i++) {
    if (_listeners[i] != nullptr) {
      _listeners[i]->OnMouseWheel(event);
    }
  }
}

void CoffeeMaker::IMouseListener::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& event) {
  // NOTE: process the listeners for the current frame.
  // any added listeners during this process loop are not counted.
  unsigned int currentSize = _listeners.size();

  for (unsigned int i = 0; i < currentSize; i++) {
    if (_listeners[i] != nullptr) {
      _listeners[i]->OnMouseMove(event);
    }
  }
}

void CoffeeMaker::IMouseListener::ProcessMouseButtonEvent(const SDL_MouseButtonEvent& event) {
  // NOTE: process the listeners for the current frame.
  // any added listeners during this process loop are not counted.
  unsigned int currentSize = _listeners.size();

  if (event.type == SDL_MOUSEBUTTONDOWN) {
    for (unsigned int i = 0; i < currentSize; i++) {
      if (_listeners[i] != nullptr) {
        _listeners[i]->OnMouseDown(event);
      }
    }
    return;
  }
  if (event.type == SDL_MOUSEBUTTONUP) {
    for (unsigned int i = 0; i < currentSize; i++) {
      if (_listeners[i] != nullptr) {
        _listeners[i]->OnMouseUp(event);
      }
    }
  }
}
