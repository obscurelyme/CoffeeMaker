#include "Game/Player.hpp"
#include "Renderer.hpp"
#include "Logger.hpp"
#include <glm/glm.hpp>
#include "InputManager.hpp"

Player::Player() {
  _firing = false;
  SDL_Rect vp;
  SDL_RenderGetViewport(CoffeeMaker::Renderer::Instance(), &vp);
  // NOTE: center the player sprite in the viewport
  _clientRect.x = (vp.w - _clientRect.w) / 2;
  _clientRect.y = (vp.h - _clientRect.h) / 2;
  Projectile projectile;
  _projectiles.fill(projectile);
  _currentProjectile = 0;
}

void Player::Init() {}

void Player::Update() {
  if (CoffeeMaker::InputManager::IsKeyPressed(SDL_SCANCODE_F)) {
    Fire();
  }

  if (CoffeeMaker::InputManager::IsKeyPressed(SDL_SCANCODE_R)) {
    Reload();
  }

  SDL_GetMouseState(&_mouseX, &_mouseY);
  int xx = _mouseX - _clientRect.x;
  int yy = _mouseY - _clientRect.y;

  _rotation = glm::degrees(glm::atan((float)yy, (float)xx));

  for (auto& projectile : _projectiles) {
    projectile.Update();
  }
}

void Player::Render() {
  _texture.Render(_clipRect, _clientRect, _rotation + 90);
    for (auto& projectile : _projectiles) {
    projectile.Render();
  }
}

void Player::Fire() {
  if (_currentProjectile <= 24) {
    _projectiles[_currentProjectile++].Fire((float)_clientRect.x, (float)_clientRect.y, _rotation);
  }
}

void Player::Reload() {
  for (auto& projectile : _projectiles) {
    projectile.Reload();
  }
  _currentProjectile = 0;
}
