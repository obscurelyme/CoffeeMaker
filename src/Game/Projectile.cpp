#include "Game/Projectile.hpp"
#include <glm/glm.hpp>
#include "Logger.hpp"
#include "Renderer.hpp"

std::shared_ptr<CoffeeMaker::Texture> Projectile::_texture = nullptr;

Projectile::Projectile(): _fired(false), _rotation(0) {
  if (Projectile::_texture == nullptr) {
    _texture = std::make_shared<CoffeeMaker::Texture>("missile.png", true);
  }
  _clientRect.w = 16;
  _clientRect.h = 16;
  collider = new Collider(false);
  collider->clientRect.w = 32;
  collider->clientRect.h = 32;
  collider->clientRect.x = _clientRect.x;
  collider->clientRect.y = _clientRect.y;
}

Projectile::~Projectile() {
  // TODO: fix clean up here. uncommenting in current state will crash application due to this being called
  // from Player constructor
  // delete collider;
}

void Projectile::Render() {
  if (_fired) {
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SDL_RenderCopyExF(CoffeeMaker::Renderer::Instance(), Projectile::_texture->Handle(), NULL, &_clientRect, _rotation + 90, NULL, flip);
    collider->Render();
  }
}

void Projectile::Update() {
  if (_fired) {
    _clientRect.x += _movement.x * 5;
    _clientRect.y += _movement.y * 5;

    // NOTE: probably want this separated out
    collider->Update(_clientRect);
  }
}

void Projectile::Fire(float x, float y, double rotation) {
  if (!_fired) {
    _fired = true;
    _clientRect.x = x;
    _clientRect.y = y;
    _rotation = rotation;

    _endX = (float)(x + 900 * cos(glm::radians(rotation)));
    _endY = (float)(y + 900 * sin(glm::radians(rotation)));
    glm::vec2 calc;
    calc.x = _endX - x;
    calc.y = _endY - y;
    _movement = glm::normalize(calc);

    collider->active = true;
    // CM_LOGGER_INFO("({}, {})", _movement.x, _movement.y);
  }
}

void Projectile::Reload() {
  if (_fired) {
    _fired = false;
  }
}
