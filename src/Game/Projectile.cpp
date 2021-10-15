#include "Game/Projectile.hpp"

#include <functional>
#include <glm/glm.hpp>

#include "Logger.hpp"
#include "Renderer.hpp"

std::shared_ptr<CoffeeMaker::Texture> Projectile::_texture = nullptr;

Projectile::Projectile() : _fired(false), _rotation(0) {
  if (Projectile::_texture == nullptr) {
    _texture = std::make_shared<CoffeeMaker::Texture>("missile.png", true);
  }
  _clientRect.w = 16;
  _clientRect.h = 16;
  collider = new Collider(Collider::Type::Projectile, false);
  collider->clientRect.w = 32;
  collider->clientRect.h = 32;
  collider->clientRect.x = _clientRect.x;
  collider->clientRect.y = _clientRect.y;
  collider->OnCollide(std::bind(&Projectile::OnHit, this, std::placeholders::_1));
}

Projectile::~Projectile() { delete collider; }

void Projectile::OnHit(Collider* c) {
  if (c->GetType() == Collider::Type::Enemy) {
    // this projectile will be considered "used", it can be deactivated and reloaded.
    Reload();
  }
}

void Projectile::Render() {
  if (_fired) {
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SDL_RenderCopyExF(CoffeeMaker::Renderer::Instance(), Projectile::_texture->Handle(), NULL, &_clientRect,
                      _rotation + 90, NULL, flip);
    collider->Render();
  }
}

void Projectile::Update() {
  if (_fired) {
    _clientRect.x += _movement.x * 5;
    _clientRect.y += _movement.y * 5;

    // NOTE: probably want this separated out
    collider->Update(_clientRect);

    if (IsOffScreen()) {
      Reload();
    }
  }
}

void Projectile::Fire(float x, float y, double rotation) {
  if (!_fired) {
    _fired = true;
    _clientRect.x = x;
    _clientRect.y = y;
    collider->Update(_clientRect);
    _rotation = rotation;

    _endX = (float)(x + 900 * cos(glm::radians(rotation)));
    _endY = (float)(y + 900 * sin(glm::radians(rotation)));
    glm::vec2 calc;
    calc.x = _endX - x;
    calc.y = _endY - y;
    _movement = glm::normalize(calc);

    collider->active = true;
  }
}

void Projectile::Reload() {
  if (_fired) {
    collider->active = false;
    _fired = false;
  }
}

bool Projectile::IsFired() const { return _fired; }

bool Projectile::IsOffScreen() const {
  // TODO: screen width and height should be dynamic
  return _clientRect.x + _clientRect.w <= 0 || _clientRect.x >= 800 || _clientRect.y + _clientRect.h <= 0 ||
         _clientRect.y >= 600;
}
