#include "Game/Projectile.hpp"

std::shared_ptr<CoffeeMaker::Texture> Projectile::_texture = nullptr;

Projectile::Projectile(): _fired(false), _rotation(0) {
  if (Projectile::_texture == nullptr) {
    _texture = std::make_shared<CoffeeMaker::Texture>("missile.png", true);
  }
  _clientRect.w = 16;
  _clientRect.h = 16;
}

void Projectile::Render() {
  if (_fired) {
    Projectile::_texture->Render(_clientRect, _rotation);
  }
}

void Projectile::Update() {
  if (_fired) {
    _clientRect.y += 1;
    _clientRect.x += 1;
  }
}

void Projectile::Fire(int x, int y, double rotation) {
  if (!_fired) {
    _fired = true;
    _clientRect.x = x;
    _clientRect.y = y;
    _rotation = rotation;
  }
}

void Projectile::Reload() {
  if (_fired) {
    _fired = false;
  }
}
