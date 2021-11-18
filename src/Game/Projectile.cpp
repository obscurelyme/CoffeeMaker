#include "Game/Projectile.hpp"

#include <functional>
#include <glm/glm.hpp>

#include "Logger.hpp"
#include "Renderer.hpp"

Ref<CoffeeMaker::Texture> Projectile::_texture = nullptr;
Ref<CoffeeMaker::AudioElement> Projectile::_fireSound = nullptr;
Ref<CoffeeMaker::AudioElement> Projectile::_impactSound = nullptr;

Projectile::Projectile() : _fired(false), _rotation(0) {
  if (Projectile::_texture == nullptr) {
    _texture = CreateRef<CoffeeMaker::Texture>("StandardMissile.png");
  }
  if (Projectile::_fireSound == nullptr) {
    _fireSound = CreateRef<CoffeeMaker::AudioElement>("effects/StandardMissileFire.ogg");
  }
  if (Projectile::_impactSound == nullptr) {
    _impactSound = CreateRef<CoffeeMaker::AudioElement>("effects/ProjectileImpact.ogg");
  }
  _clientRect.w = 16;
  _clientRect.h = 16;
  collider = new Collider(Collider::Type::Projectile, false);
  collider->clientRect.w = 16;
  collider->clientRect.h = 16;
  collider->clientRect.x = _clientRect.x;
  collider->clientRect.y = _clientRect.y;
  collider->OnCollide(std::bind(&Projectile::OnHit, this, std::placeholders::_1));
}

Projectile::Projectile(Collider::Type colliderType) : Projectile() { collider->SetType(colliderType); }

Projectile::~Projectile() { delete collider; }

void Projectile::OnHit(Collider* c) {
  if (c->GetType() == Collider::Type::Enemy && collider->GetType() == Collider::Type::Projectile) {
    _impactSound->Play();
    Reload();
    return;
  }
  if (c->GetType() == Collider::Type::Player && collider->GetType() == Collider::Type::EnemyProjectile) {
    _impactSound->Play();
    Reload();
    return;
  }
}

void Projectile::Render() {
  if (_fired) {
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SDL_RenderCopyExF(CoffeeMaker::Renderer::Instance(), Projectile::_texture->Handle(), NULL, &_clientRect, _rotation,
                      NULL, flip);
    collider->Render();
  }
}

void Projectile::Update(float deltaTime) {
  if (_fired) {
    _clientRect.x += _movement.x * 300 * deltaTime;
    _clientRect.y += _movement.y * 300 * deltaTime;

    // NOTE: probably want this separated out
    collider->Update(_clientRect);

    if (IsOffScreen()) {
      Reload();
    }
  }
}

void Projectile::Fire(float x, float y, double rotation) {
  if (!_fired) {
    _fireSound->Play();
    _fired = true;
    _clientRect.x = x;
    _clientRect.y = y;
    collider->Update(_clientRect);
    _rotation = rotation + 90;

    _endX = (float)(x + 900 * cos(glm::radians(rotation)));
    _endY = (float)(y + 900 * sin(glm::radians(rotation)));
    glm::vec2 calc;
    calc.x = _endX - x;
    calc.y = _endY - y;
    _movement = glm::normalize(calc);

    collider->active = true;
  }
}

void Projectile::Fire2(float x, float y, float endX, float endY, double rotation) {
  if (!_fired) {
    _fireSound->Play();
    _fired = true;
    _clientRect.x = x;
    _clientRect.y = y;
    collider->Update(_clientRect);
    _rotation = rotation;

    glm::vec2 calc;
    calc.x = endX - x;
    calc.y = endY - y;
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
