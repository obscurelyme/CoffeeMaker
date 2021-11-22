#include "Events/UserEvents.hpp"

unsigned int CoffeeMaker::IUserEventListener::_uid = 0;
std::vector<CoffeeMaker::IUserEventListener*> CoffeeMaker::IUserEventListener::_listeners = {};

void CoffeeMaker::IUserEventListener::ProcessUserEvent(const SDL_UserEvent& event) {
  // NOTE: process the listeners for the current frame.
  // any added listeners during this process loop are not counted.
  unsigned int currentSize = _listeners.size();

  for (unsigned int i = 0; i < currentSize; i++) {
    if (_listeners[i] != nullptr) {
      _listeners[i]->OnSDLUserEvent(event);
    }
  }
}

void CoffeeMaker::IUserEventListener::RemoveStaleListeners() {
  for (auto it = _listeners.begin(); it != _listeners.end();) {
    if ((*it) == nullptr) {
      it = _listeners.erase(it);
    } else {
      ++it;
    }
  }
}

CoffeeMaker::IUserEventListener::~IUserEventListener() { _listeners[_index] = nullptr; }

CoffeeMaker::IUserEventListener::IUserEventListener() : _id(++_uid) {
  _listeners.push_back(this);
  _index = _listeners.size() - 1;
}
