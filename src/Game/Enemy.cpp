#include "Game/Enemy.hpp"

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include <iostream>
#include <random>

#include "Game/Player.hpp"
#include "Game/PlayerEvents.hpp"
#include "Logger.hpp"
#include "Renderer.hpp"

unsigned int Enemy::_uid = 0;
std::random_device device;
std::default_random_engine engine(device());
std::uniform_real_distribution<double> distribution(0, 360);

Enemy::Enemy() : _collider(nullptr), _enteredScreen(false), _active(false) {
  _priorTicks = SDL_GetTicks();
  _ticks = _priorTicks;
  _id = "Enemy-" + std::to_string(++_uid);
  _collider = std::make_shared<Collider>(Collider::Type::Enemy, _active);
  _collider->clientRect.h = _clientRect.h;
  _collider->clientRect.w = _clientRect.w;
  _collider->OnCollide(std::bind(&Enemy::OnCollision, this, std::placeholders::_1));
  for (int i = 0; i < 50; i++) {
    _projectiles.emplace_back(new Projectile(Collider::Type::EnemyProjectile));
  }
  _currentProjectile = 0;
}

Enemy::~Enemy() {
  for (auto p : _projectiles) {
    delete p;
  }
}

void Enemy::Init() {}

void Enemy::Render() {
  SDL_RendererFlip flip = SDL_FLIP_NONE;

  float xx = (400 - _clientRect.x);
  float yy = (300 - _clientRect.y);

  float rotation = glm::degrees(glm::atan(yy, xx));
  SDL_RenderCopyExF(CoffeeMaker::Renderer::Instance(), _texture.Handle(), &_clipRect, &_clientRect, rotation + 90, NULL,
                    flip);

  for (auto& projectile : _projectiles) {
    projectile->Render();
  }
  // _collider->Render();
}

void Enemy::Pause() {}

void Enemy::Unpause() {}

void Enemy::Update(float deltaTime) {
  if (_active) {
    _clientRect.x += _movement.x * _speed * deltaTime;
    _clientRect.y += _movement.y * _speed * deltaTime;
    _collider->Update(_clientRect);

    if (!_enteredScreen && !IsOffScreen()) {
      _enteredScreen = true;
    }

    if (IsOffScreen() && _enteredScreen) {
      // Enemy went off screen
      Spawn();
    }
  }
}

void Enemy::Spawn() {
  // Pick a random location around the player
  _enteredScreen = false;
  _collider->active = false;

  double randomAngle = glm::radians(distribution(engine));

  _clientRect.x = (float)(300 + 400 * cos(randomAngle));
  _clientRect.y = (float)(400 + 400 * sin(randomAngle));
  _collider->Update(_clientRect);

  CM_LOGGER_INFO("Enemy {} spawned at position ({}, {})", _id, _clientRect.x, _clientRect.y);

  _movement = glm::normalize(glm::vec2(400 - _clientRect.x, 300 - _clientRect.y));

  _active = true;
  _collider->active = true;
}

bool Enemy::IsActive() const { return _active; }

void Enemy::OnCollision(Collider* collider) {
  if (collider->GetType() == Collider::Type::Projectile) {
    incScore->Emit();
    Spawn();
  }
}

bool Enemy::IsOffScreen() const {
  // TODO: screen width and height should be dynamic
  return _clientRect.x + _clientRect.w <= 0 || _clientRect.x >= 800 || _clientRect.y + _clientRect.h <= 0 ||
         _clientRect.y >= 600;
}

void Enemy::Fire() {
  // NOTE: sloppy but should kinda work for now
  if (_currentProjectile < 24) {
    if (!_projectiles[_currentProjectile + 1]->IsFired()) {
      _projectiles[_currentProjectile++]->Fire2(_clientRect.x, _clientRect.y, Player::Position().x,
                                                Player::Position().y, _rotation);
    } else {
      _currentProjectile += 2;
    }
  } else if (_currentProjectile == 24) {
    _currentProjectile = 0;
    // NOTE: fire the next, or else projectiles are unavailable for a frame.
    _projectiles[_currentProjectile++]->Fire2(_clientRect.x, _clientRect.y, Player::Position().x, Player::Position().y,
                                              _rotation);
  }
}

SpecialEnemy::SpecialEnemy() {}

SpecialEnemy::~SpecialEnemy() {}

void SpecialEnemy::Init() {
  _transformVector.x = 0;
  _transformVector.y = 600;
  _endVector.x = 400;
  _endVector.y = 300;
  _clientRect.x = _transformVector.x;
  _clientRect.y = _transformVector.y;
}

void SpecialEnemy::Update(float deltaTime) {
  using Vec2 = CoffeeMaker::Math::Vector2D;
  if (_active) {
    _to.Start();
    _currentTime += deltaTime;
    float weight = _currentTime / 1.5f;
    Vec2 pos{_clientRect.x, _clientRect.y};
    _rotation = CoffeeMaker::Math::rad2deg(pos.LookAt(Player::Position())) + 90;
    if (weight <= 1.0f) {
      CoffeeMaker::Math::Vector2D currentPos = CoffeeMaker::Math::CubicBezierCurve(
          CoffeeMaker::Math::Vector2D(-200.0f, 600.0f), CoffeeMaker::Math::Vector2D(0.0f, -50.0f),
          CoffeeMaker::Math::Vector2D(800.0f, 0.0f), CoffeeMaker::Math::Vector2D(400.0f, 150.0f), weight);
      _clientRect.x = currentPos.x;
      _clientRect.y = currentPos.y;
      _collider->Update(_clientRect);
    } else {
      // NOTE: side to side motion
      if (_moveright) {
        // move right
        _clientRect.x += deltaTime * (_speed);
        _collider->Update(_clientRect);
        if (_clientRect.x >= 700) {
          _moveright = false;
        }
      } else {
        // move left
        _clientRect.x -= deltaTime * (_speed);
        _collider->Update(_clientRect);
        if (_clientRect.x <= 100) {
          _moveright = true;
        }
      }

      _to.Act();  // NOTE: runs the Fire function on an interval
    }

    if (!_enteredScreen && !IsOffScreen()) {
      _enteredScreen = true;
    }

    if (IsOffScreen() && _enteredScreen) {
      // Enemy went off screen
      Spawn();
    }
  }
  // NOTE: projectiles that have already been fired are still fine to be updated
  for (auto& projectile : _projectiles) {
    projectile->Update(deltaTime);
  }
}

void SpecialEnemy::Render() {
  SDL_RendererFlip flip = SDL_FLIP_NONE;
  SDL_RenderCopyExF(CoffeeMaker::Renderer::Instance(), _texture.Handle(), &_clipRect, &_clientRect, _rotation, NULL,
                    flip);
  for (auto& projectile : _projectiles) {
    projectile->Render();
  }
}

void SpecialEnemy::Pause() { _to.Pause(); }

void SpecialEnemy::Unpause() { _to.Unpause(); }

void SpecialEnemy::Spawn() {
  _currentTime = 0.0f;
  _enteredScreen = false;
  _collider->active = false;
  _moveright = false;

  _clientRect.x = _transformVector.x;
  _clientRect.y = _transformVector.y;
  _collider->Update(_clientRect);

  _active = true;
  _collider->active = true;
}
