#include "Event.hpp"

#include <SDL2/SDL.h>

#include <algorithm>
#include <iostream>
#include <string>

#include "Logger.hpp"
#include "Window.hpp"

using namespace CoffeeMaker;

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

void CoffeeMaker::PushUserEvent(Uint32 type, Sint32 eventCode, void* data1, void* data2) {
  SDL_UserEvent userevent{.type = type,
                          .timestamp = SDL_GetTicks(),
                          .windowID = CoffeeMaker::GlobalWindow::ID(),
                          .code = eventCode,
                          .data1 = data1,
                          .data2 = data2};
  SDL_Event event;
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
