#include "Game/Player.hpp"

#include <chrono>
#include <functional>
#include <glm/glm.hpp>

#include "Event.hpp"
#include "Game/GameEvents.hpp"
#include "Game/Scene.hpp"
#include "InputManager.hpp"
#include "Logger.hpp"
#include "Renderer.hpp"

Player* Player::_instance = nullptr;

CoffeeMaker::Math::Vector2D Player::Position() {
  return CoffeeMaker::Math::Vector2D(_instance->_clientRect.x, _instance->_clientRect.y);
}

Player::Player() : _isImmune(false), _collider(new Collider(Collider::Type::Player, true)), _active(true), _lives(3) {
  _firing = false;
  SDL_Rect vp;
  SDL_RenderGetViewport(CoffeeMaker::Renderer::Instance(), &vp);
  // NOTE: center the player sprite in the viewport
  _clientRect.x = (vp.w - _clientRect.w) / 2;
  _clientRect.y = (vp.h - _clientRect.h) - 50;
  for (int i = 0; i < 25; i++) {
    _projectiles.emplace_back(new Projectile());
  }
  _currentProjectile = 0;
  _collider->clientRect.h = _clientRect.h;
  _collider->clientRect.w = _clientRect.w;
  _collider->Update(_clientRect);
  _collider->OnCollide(std::bind(&Player::OnHit, this, std::placeholders::_1));
  _instance = this;
}

Player::~Player() {
  _instance = nullptr;
  delete _collider;
  for (auto p : _projectiles) {
    delete p;
  }
}

void Player::OnHit(Collider* collider) {
  if (_collider->active) {
    if (collider->GetType() == Collider::Type::EnemyProjectile && !_isImmune) {
      _collider->active = false;
      _active = false;
      if (_lives == 0) {
        SceneManager::LoadScene(0);
        return;
      }
      _lives--;
      CoffeeMaker::PushEvent(GameEvents::PLAYER_LOST_LIFE);
      _respawnTimer.Start();
    }
  }
}

void Player::Init() {}

void Player::UpdateRespawnImmunity() {
  if (_active && _isImmune) {
    if (_immunityTimer.GetTicks() >= 3000) {
      _isImmune = false;
      _immunityTimer.Stop();
    }
  }
}

void Player::Pause() {
  _respawnTimer.Pause();
  _immunityTimer.Pause();
}

void Player::Unpause() {
  _immunityTimer.Unpause();
  _respawnTimer.Unpause();
}

void Player::Update(float deltaTime) {
  UpdateRespawnImmunity();

  if (!_active) {
    if (_respawnTimer.GetTicks() >= 3000) {
      _active = true;
      _collider->active = true;
      _respawnTimer.Stop();
      _immunityTimer.Start();
      _isImmune = true;
    }
  }

  if (_active) {
    _rotation = -90;
    if (IsOffScreenLeft()) {
      _clientRect.x = 800;
    } else if (IsOffScreenRight()) {
      _clientRect.x = 0 - _clientRect.w;
    }

    if (CoffeeMaker::InputManager::IsKeyPressed(SDL_SCANCODE_SPACE)) {
      Fire();
    }

    if (CoffeeMaker::InputManager::IsKeyDown(SDL_SCANCODE_LEFT)) {
      // strafe left
      _clientRect.x -= deltaTime * _speed;
      _rotation -= 8;
    }

    if (CoffeeMaker::InputManager::IsKeyDown(SDL_SCANCODE_RIGHT)) {
      // strafe right
      _clientRect.x += deltaTime * _speed;
      _rotation += 8;
    }

    // SDL_GetMouseState(&_mouseX, &_mouseY);
    // float xx = (_mouseX - _clientRect.x) * deltaTime;
    // float yy = (_mouseY - _clientRect.y) * deltaTime;
    _collider->Update(_clientRect);
  }

  // NOTE: projectiles that have already been fired are still fine to be updated
  for (auto& projectile : _projectiles) {
    projectile->Update(deltaTime);
  }
}

void Player::Render() {
  if (_active) {
    _texture.Render(_clipRect, _clientRect, _rotation + 90);
    // _collider->Render();
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

bool Player::IsOffScreenLeft() { return _clientRect.x + _clientRect.w <= 0; }
bool Player::IsOffScreenRight() { return _clientRect.x >= 800; }
