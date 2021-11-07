#include "Event.hpp"

#include <SDL2/SDL.h>

#include <algorithm>
#include <iostream>
#include <string>

#include "Logger.hpp"

using namespace CoffeeMaker;

int Delegate::_uid = 0;
int Delegate2::_uid = 0;

Sint32 CoffeeMaker::GameEvents::Marker = 1'000'000;
std::map<std::string, Sint32> CoffeeMaker::GameEvents::Events = {};
std::map<Sint32, GameEvent*> CoffeeMaker::GameEvents::Events2 = {};

void CoffeeMaker::GameEvents::AddEvent(const std::string& event) { Events[event] = CoffeeMaker::GameEvents::Marker++; };

void CoffeeMaker::GameEvents::PushEvent(const std::string& name, Sint32, void* data1, void* data2) {
  if (CoffeeMaker::GameEvents::Events.contains(name)) {
    SDL_Event event;
    SDL_UserEvent userevent{.type = SDL_USEREVENT, .code = GameEvents::Events[name], .data1 = data1, .data2 = data2};
    event.type = SDL_USEREVENT;
    event.user = userevent;
    SDL_PushEvent(&event);
  }
}

void CoffeeMaker::GameEvents::ProcessEvent(const SDL_UserEvent& event) {
  if (CoffeeMaker::GameEvents::Events2.contains(event.code)) {
    CoffeeMaker::GameEvents::Events2[event.code]->Emit();
  }

  // if (event.code == CoffeeMaker::GameEvents::Events["ENEMY_SPAWN"]) {
  //   SceneManager::HandleSceneEvent(event.code, event.data1, event.data2);
  // }

  // if (event.code == CoffeeMaker::ApplicationEvents::COFFEEMAKER_GAME_PAUSE) {
  //   paused = true;
  //   SceneManager::PauseScene();
  //   CoffeeMaker::Timeout::PauseAllTimeouts();
  // }
  // if (event.code == CoffeeMaker::ApplicationEvents::COFFEEMAKER_GAME_UNPAUSE ||
  //     event.code == CoffeeMaker::ApplicationEvents::COFFEEMAKER_SCENE_LOAD) {
  //   paused = false;
  //   SceneManager::UnpauseScene();
  //   CoffeeMaker::Timeout::UnpauseAllTimeouts();
  // }
  // if (event.code == CoffeeMaker::ApplicationEvents::COFFEEMAKER_SCENE_EVENT) {
  //   SceneManager::HandleSceneEvent(event.code, event.data1, event.data2);
  // }
  // if (event.code == 1245) {
  //   if (event.data2 != nullptr) {
  //     void (*p)(void*) = reinterpret_cast<void (*)(void*)>(event.data1);
  //     p(event.data2);
  //   } else {
  //     void (*p)() = reinterpret_cast<void (*)()>(event.data1);
  //     p();
  //   }
  //   break;
  // }
}

void CoffeeMaker::PushCoffeeMakerEvent(CoffeeMaker::ApplicationEvents appEvent) {
  if (appEvent == ApplicationEvents::COFFEEMAKER_GAME_QUIT) {
    SDL_Event event;
    event.type = SDL_QUIT;
    SDL_PushEvent(&event);
    return;
  }
  SDL_UserEvent userevent{.type = SDL_USEREVENT, .code = appEvent, .data1 = nullptr, .data2 = nullptr};
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
