#include "Event.hpp"

#include <SDL2/SDL.h>

#include <algorithm>
#include <iostream>
#include <string>

#include "Logger.hpp"
#include "Window.hpp"

using namespace CoffeeMaker;

unsigned int CoffeeMaker::IMouseListener::_uid = 0;
unsigned int CoffeeMaker::IUserEventListener::_uid = 0;

std::vector<CoffeeMaker::IMouseListener*> CoffeeMaker::IMouseListener::_instances = {};
std::vector<CoffeeMaker::IMouseListener*> CoffeeMaker::IMouseListener::_listeners = {};
std::vector<CoffeeMaker::IUserEventListener*> CoffeeMaker::IUserEventListener::_listeners = {};

void CoffeeMaker::MouseEventHandler::AddNewMouseHandlers() {
  // Add any newly created listeners
  for (auto& instance : CoffeeMaker::IMouseListener::_instances) {
    if (!instance->_live) {
      CoffeeMaker::IMouseListener::_listeners.push_back(instance);
      instance->_live = true;
    }
  }
  CoffeeMaker::IMouseListener::_instances.clear();
}

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
}

CoffeeMaker::IMouseListener::IMouseListener() : _id(++_uid), _live(false) {
  _instances.push_back(this);
  // _listeners.push_back(this);
}

CoffeeMaker::IMouseListener::~IMouseListener() {
  // First, check if deleted before added to the listeners vector
  for (auto it = _instances.begin(); it != _instances.end();) {
    if (_id == (*it)->_id) {
      it = _instances.erase(it);
      break;
    } else {
      ++it;
    }
  }
  // Second, remove from the listeners vector
  for (auto it = _listeners.begin(); it != _listeners.end();) {
    if (_id == (*it)->_id) {
      it = _listeners.erase(it);
      break;
    } else {
      ++it;
    }
  }
}

void CoffeeMaker::IMouseListener::ProcessMouseWheelEvent(const SDL_MouseWheelEvent& event) {
  for (auto& listener : _listeners) {
    listener->OnMouseWheel(event);
  }
}

void CoffeeMaker::IMouseListener::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& event) {
  for (auto& listener : _listeners) {
    listener->OnMouseMove(event);
  }
}

void CoffeeMaker::IMouseListener::ProcessMouseButtonEvent(const SDL_MouseButtonEvent& event) {
  if (event.type == SDL_MOUSEBUTTONDOWN) {
    for (auto& listener : _listeners) {
      listener->OnMouseDown(event);
    }
    return;
  }
  if (event.type == SDL_MOUSEBUTTONUP) {
    for (auto& listener : _listeners) {
      listener->OnMouseUp(event);
    }
  }
}

void CoffeeMaker::IUserEventListener::ProcessUserEvent(const SDL_UserEvent& event) {
  for (auto& listener : _listeners) {
    listener->OnSDLUserEvent(event);
  }
}

CoffeeMaker::IUserEventListener::~IUserEventListener() {
  for (auto it = _listeners.begin(); it != _listeners.end();) {
    if (_id == (*it)->_id) {
      it = _listeners.erase(it);
      break;
    } else {
      ++it;
    }
  }
}

CoffeeMaker::IUserEventListener::IUserEventListener() : _id(++_uid) { _listeners.push_back(this); }

int Delegate::_uid = 0;

void CoffeeMaker::PushCoffeeMakerEvent(CoffeeMaker::ApplicationEvents appEvent) {
  if (appEvent == ApplicationEvents::COFFEEMAKER_GAME_QUIT) {
    SDL_Event event;
    event.type = SDL_QUIT;
    SDL_PushEvent(&event);
    return;
  }
  SDL_UserEvent userevent{
      .type = SDL_USEREVENT,
      .timestamp = SDL_GetTicks(),
      .windowID = CoffeeMaker::GlobalWindow::ID(),
      .code = appEvent,
      .data1 = nullptr,
      .data2 = nullptr,

  };
  SDL_Event event;
  event.type = SDL_USEREVENT;
  event.user = userevent;
  SDL_PushEvent(&event);
}

void CoffeeMaker::PushEvent(Sint32 eventCode, void* data1, void* data2) {
  SDL_UserEvent userevent{.type = SDL_USEREVENT,
                          .timestamp = SDL_GetTicks(),
                          .windowID = CoffeeMaker::GlobalWindow::ID(),
                          .code = eventCode,
                          .data1 = data1,
                          .data2 = data2};
  SDL_Event event;
  event.type = SDL_USEREVENT;
  event.user = userevent;
  SDL_PushEvent(&event);
}

Delegate::Delegate(std::function<void(const Event& event)> cb) {
  _function = cb;
  _id = ++_uid;
}

Delegate::~Delegate() { _function = nullptr; }

void Event::Emit() {
  auto e = [this](EventListener& listener) { std::invoke(listener.Get(), *this); };
  std::for_each(_listeners.begin(), _listeners.end(), e);
}

Event::~Event() {
  RemoveAllListeners();
  // TODO: fix logger
  // CM_LOGGER_INFO("Event was deleted");
}

void Event::AddListener(EventListener listener) {
  // insert into the array
  _listeners.emplace_back(listener);
}

void Event::RemoveListener(EventListener listener) {
  for (auto it = _listeners.begin(); it != _listeners.end();) {
    if (listener == *it) {
      it = _listeners.erase(it);
      break;
    } else {
      ++it;
    }
  }
}

void Event::RemoveAllListeners() { _listeners.clear(); }
