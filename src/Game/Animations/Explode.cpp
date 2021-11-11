#include "Game/Animations/Explode.hpp"

Ref<CoffeeMaker::Sprite> UCI::Animations::ExplodeSpriteAnimation::_sprite = nullptr;
// CreateRef<CoffeeMaker::Sprite>("Explode.png");

UCI::Animations::ExplodeSpriteAnimation::ExplodeSpriteAnimation() : _position(Vec2{0.0f, 0.0f}) {
  if (_sprite == nullptr) {
    _sprite = CreateRef<CoffeeMaker::Sprite>("Explode.png");
    _sprite->clientRect.w = 48;
    _sprite->clientRect.h = 48;
  }

  _animation = CreateScope<::Animations::SpriteAnimation>(_sprite, 750, 0);

  // NOTE: may want to leverage the same SDL_Rect array to save on memory
  _animation->AddFrame(SDL_Rect{.x = 0, .y = 0, .w = 32, .h = 32});
  _animation->AddFrame(SDL_Rect{.x = 32, .y = 0, .w = 32, .h = 32});
  _animation->AddFrame(SDL_Rect{.x = 0, .y = 32, .w = 32, .h = 32});
  _animation->AddFrame(SDL_Rect{.x = 32, .y = 32, .w = 32, .h = 32});
  _animation->AddFrame(SDL_Rect{.x = 0, .y = 64, .w = 32, .h = 32});
  _animation->AddFrame(SDL_Rect{.x = 32, .y = 64, .w = 32, .h = 32});
}

UCI::Animations::ExplodeSpriteAnimation::~ExplodeSpriteAnimation() { Stop(); }

void UCI::Animations::ExplodeSpriteAnimation::SetPosition(const Vec2& pos) { _position = pos; }

void UCI::Animations::ExplodeSpriteAnimation::Render() {
  _sprite->SetPosition(_position);
  _animation->Render();
}

void UCI::Animations::ExplodeSpriteAnimation::Start() { _animation->Start(); }

void UCI::Animations::ExplodeSpriteAnimation::Stop() { _animation->Stop(); }

void UCI::Animations::ExplodeSpriteAnimation::OnSDLUserEvent(const SDL_UserEvent& event) {
  if (event.code == CoffeeMaker::ApplicationEvents::COFFEEMAKER_GAME_PAUSE) {
    _animation->Pause();
    return;
  }

  if (event.code == CoffeeMaker::ApplicationEvents::COFFEEMAKER_GAME_UNPAUSE) {
    _animation->Unpause();
    return;
  }
}

void UCI::Animations::ExplodeSpriteAnimation::OnComplete(std::function<void(void)> callback) {
  _animation->OnComplete(callback);
}
