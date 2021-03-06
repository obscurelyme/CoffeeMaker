#include "Game/Projectile.hpp"

#include <functional>
#include <glm/glm.hpp>

#include "Logger.hpp"
#include "Renderer.hpp"

Ref<CoffeeMaker::Texture> Projectile::_standardMissile = nullptr;
Ref<CoffeeMaker::Texture> Projectile::_laserSmallRed = nullptr;
Ref<CoffeeMaker::Texture> Projectile::_laserSmallGreen = nullptr;
Ref<CoffeeMaker::Texture> Projectile::_laserLargeRed = nullptr;
Ref<CoffeeMaker::Texture> Projectile::_laserLargeGreen = nullptr;
Ref<CoffeeMaker::AudioElement> Projectile::_fireSound = nullptr;
Ref<CoffeeMaker::AudioElement> Projectile::_impactSound = nullptr;

Projectile::Projectile() : _fired(false), _rotation(0), _speed(500.0f) {
  if (Projectile::_standardMissile == nullptr) {
    _standardMissile = CreateRef<CoffeeMaker::Texture>("StandardMissile.png");
    _laserSmallRed = CreateRef<CoffeeMaker::Texture>("Laser-Small-Red.png");
    _laserSmallGreen = CreateRef<CoffeeMaker::Texture>("Laser-Small-Green.png");
    _laserLargeRed = CreateRef<CoffeeMaker::Texture>("Laser-Large-Red.png");
    _laserLargeGreen = CreateRef<CoffeeMaker::Texture>("Laser-Large-Green.png");
  }
  if (Projectile::_fireSound == nullptr) {
    _fireSound = CreateRef<CoffeeMaker::AudioElement>("effects/StandardMissileFire.ogg");
  }
  if (Projectile::_impactSound == nullptr) {
    _impactSound = CreateRef<CoffeeMaker::AudioElement>("effects/ProjectileImpact.ogg");
  }
  _clientRect.w = 16 * CoffeeMaker::Renderer::DynamicResolutionDownScale();
  _clientRect.h = 16 * CoffeeMaker::Renderer::DynamicResolutionDownScale();
  collider = new Collider(Collider::Type::Projectile, false);
  collider->clientRect.w = 16 * CoffeeMaker::Renderer::DynamicResolutionDownScale();
  collider->clientRect.h = 16 * CoffeeMaker::Renderer::DynamicResolutionDownScale();
  collider->clientRect.x = _clientRect.x;
  collider->clientRect.y = _clientRect.y;
  collider->OnCollide(std::bind(&Projectile::OnHit, this, std::placeholders::_1));
}

Projectile::Projectile(Collider::Type colliderType) : Projectile() { collider->SetType(colliderType); }

Projectile::Projectile(Collider::Type colliderType, Projectile::Type type, Projectile::Size size) : Projectile() {
  if (type == Projectile::Type::Friendly) {
    // green laser
    if (size == Projectile::Size::Small) {
      // small laser
      _texture = _laserSmallGreen;
    } else if (size == Projectile::Size::Large) {
      // large laser
      _texture = _laserLargeGreen;
    }
  } else if (type == Projectile::Type::Hostile) {
    // red laser
    if (size == Projectile::Size::Small) {
      // small laser
      _texture = _laserSmallRed;
    } else if (size == Projectile::Size::Large) {
      // large laser
      _texture = _laserLargeRed;
    }
  }
  collider->SetType(colliderType);
}

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
    // collider->Render();
  }
}

void Projectile::Update(float deltaTime) {
  if (_fired) {
    _clientRect.x += _movement.x * _speed * CoffeeMaker::Renderer::DynamicResolutionDownScale() * deltaTime;
    _clientRect.y += _movement.y * _speed * CoffeeMaker::Renderer::DynamicResolutionDownScale() * deltaTime;

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
  return _clientRect.x + _clientRect.w <= 0 || _clientRect.x >= CoffeeMaker::Renderer::GetOutputWidth() ||
         _clientRect.y + _clientRect.h <= 0 || _clientRect.y >= CoffeeMaker::Renderer::GetOutputHeight();
}
