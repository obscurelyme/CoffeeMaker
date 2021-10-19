#include "Game/Player.hpp"

#include <chrono>
#include <functional>
#include <glm/glm.hpp>

#include "Game/PlayerEvents.hpp"
#include "Game/Scene.hpp"
#include "InputManager.hpp"
#include "Logger.hpp"
#include "Renderer.hpp"

Player::Player() : _collider(new Collider(Collider::Type::Player, true)), _active(true), _lives(3) {
  _firing = false;
  SDL_Rect vp;
  SDL_RenderGetViewport(CoffeeMaker::Renderer::Instance(), &vp);
  // NOTE: center the player sprite in the viewport
  _clientRect.x = (vp.w - _clientRect.w) / 2;
  _clientRect.y = (vp.h - _clientRect.h) / 2;
  for (int i = 0; i < 25; i++) {
    _projectiles.emplace_back(new Projectile());
  }
  _currentProjectile = 0;
  _collider->Update(_clientRect);
  _collider->OnCollide(std::bind(&Player::OnHit, this, std::placeholders::_1));
}

Player::~Player() {
  delete _collider;
  for (auto p : _projectiles) {
    delete p;
  }
}

void Player::OnHit(Collider* collider) {
  if (collider->GetType() == Collider::Type::Enemy) {
    _collider->active = false;
    _active = false;
    if (_lives == 0) {
      SceneManager::LoadScene(0);
      return;
    }
    _lives--;
    decLife->Emit();
    _respawnTimerStart = std::chrono::steady_clock::now();
  }
}

void Player::Init() {}

void Player::Update() {
  if (!_active) {
    _respawnTimer = std::chrono::steady_clock::now() - _respawnTimerStart;
    if (_respawnTimer.count() >= 3000) {
      _active = true;
      _collider->active = true;
    }
  }

  if (_active) {
    if (CoffeeMaker::InputManager::IsKeyPressed(SDL_SCANCODE_F)) {
      Fire();
    }

    SDL_GetMouseState(&_mouseX, &_mouseY);
    int xx = _mouseX - (int)_clientRect.x;
    int yy = _mouseY - (int)_clientRect.y;

    _rotation = glm::degrees(glm::atan((float)yy, (float)xx));
  }

  // NOTE: projectiles that have already been fired are still fine to be updated
  for (auto& projectile : _projectiles) {
    projectile->Update();
  }
}

void Player::Render() {
  if (_active) {
    _texture.Render(_clipRect, _clientRect, _rotation + 90);
    _collider->Render();
  }

  // NOTE: projectiles that have already been fired are still fine to be rendered
  for (auto& projectile : _projectiles) {
    projectile->Render();
  }
}

void Player::Fire() {
  // NOTE: sloppy but should kinda work for now
  if (_currentProjectile < 24) {
    if (!_projectiles[_currentProjectile + 1]->IsFired()) {
      _projectiles[_currentProjectile++]->Fire((float)_clientRect.x, (float)_clientRect.y, _rotation);
    } else {
      _currentProjectile += 2;
    }
  } else if (_currentProjectile == 24) {
    _currentProjectile = 0;
    // NOTE: fire the next, or else projectiles are unavailable for a frame.
    _projectiles[_currentProjectile++]->Fire((float)_clientRect.x, (float)_clientRect.y, _rotation);
  }
}

void Player::Reload() {
  for (auto& projectile : _projectiles) {
    projectile->Reload();
  }
  _currentProjectile = 0;
}
