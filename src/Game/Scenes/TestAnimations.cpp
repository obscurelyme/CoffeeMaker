#include "Game/Scenes/TestAnimations.hpp"

#include "Color.hpp"
#include "Event.hpp"
#include "InputManager.hpp"
#include "Logger.hpp"
#include "Renderer.hpp"

TestAnimations::TestAnimations() : _backgroundColor(CoffeeMaker::Colors::Black), _paused(false) {
  _sprite = CreateRef<CoffeeMaker::Sprite>("Explode.png");
  _sprite->clientRect.w = 48;
  _sprite->clientRect.h = 48;
  _sprite->clientRect.x = 400;
  _sprite->clientRect.y = 300;
  _sprite->clipRect.w = 32;
  _sprite->clipRect.h = 32;
  _explosiveAnimation = CreateRef<Animations::SpriteAnimation>(_sprite, 750, 5);
}

void TestAnimations::Render() {
  using namespace CoffeeMaker;
  SDL_SetRenderDrawColor(Renderer::Instance(), _backgroundColor.r, _backgroundColor.g, _backgroundColor.b,
                         _backgroundColor.a);
  SDL_RenderClear(Renderer::Instance());
  _explosiveAnimation->Render();
}

void TestAnimations::Update(float) {
  if (CoffeeMaker::InputManager::IsKeyPressed(SDL_SCANCODE_ESCAPE)) {
    if (_paused) {
      CoffeeMaker::PushCoffeeMakerEvent(CoffeeMaker::ApplicationEvents::COFFEEMAKER_GAME_UNPAUSE);
      _paused = false;
    } else {
      CoffeeMaker::PushCoffeeMakerEvent(CoffeeMaker::ApplicationEvents::COFFEEMAKER_GAME_PAUSE);
      _paused = true;
    }
  }
}

void TestAnimations::Init() {
  // Set up all frames here...
  _explosiveAnimation->AddFrame(SDL_Rect{.x = 0, .y = 0, .w = 32, .h = 32});
  _explosiveAnimation->AddFrame(SDL_Rect{.x = 32, .y = 0, .w = 32, .h = 32});
  _explosiveAnimation->AddFrame(SDL_Rect{.x = 0, .y = 32, .w = 32, .h = 32});
  _explosiveAnimation->AddFrame(SDL_Rect{.x = 32, .y = 32, .w = 32, .h = 32});
  _explosiveAnimation->AddFrame(SDL_Rect{.x = 0, .y = 64, .w = 32, .h = 32});
  _explosiveAnimation->AddFrame(SDL_Rect{.x = 32, .y = 64, .w = 32, .h = 32});
  _explosiveAnimation->Start();
}

void TestAnimations::Destroy() { _explosiveAnimation->Stop(); }

void TestAnimations::Pause() { _explosiveAnimation->Pause(); }

void TestAnimations::Unpause() { _explosiveAnimation->Unpause(); }

void TestAnimations::OnSDLUserEvent(const SDL_UserEvent& event) {
  using Event = CoffeeMaker::ApplicationEvents;
  if (event.code == Event::COFFEEMAKER_GAME_PAUSE) {
    CM_LOGGER_INFO("Game paused");
  }

  if (event.code == Event::COFFEEMAKER_GAME_UNPAUSE) {
    CM_LOGGER_INFO("Game resumed");
  }
}
