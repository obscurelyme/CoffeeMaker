#include "Game/Enemy.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include <iostream>
#include <random>

#include "Game/Player.hpp"
#include "Logger.hpp"
#include "Renderer.hpp"

unsigned int Enemy::_uid = 0;
std::random_device device;
std::default_random_engine engine(device());
std::uniform_real_distribution<double> distribution(0, 360);

Enemy::Enemy() : _collider(nullptr), _active(false) {
  // _priorTicks = SDL_GetTicks();
  // _ticks = _priorTicks;
  _id = "Enemy-" + std::to_string(++_uid);
  _collider = std::make_shared<Collider>(Collider::Type::Enemy, _active);
  _collider->OnCollide(std::bind(&Enemy::OnCollision, this, std::placeholders::_1));
}

Enemy::~Enemy() { std::cout << "deleted " << _id << std::endl; }

void Enemy::Init() {}

void Enemy::Render() {
  SDL_RendererFlip flip = SDL_FLIP_NONE;
  SDL_RenderCopyExF(CoffeeMaker::Renderer::Instance(), _texture.Handle(), &_clipRect, &_clientRect, 90, NULL, flip);
  _collider->Render();
}

void Enemy::Update() {
  if (_active) {
    // _ticks = SDL_GetTicks();
    // if (_ticks > _priorTicks + 750) {
    //   if (_state == EnemyAnimationState::Idle) {
    //     _state = EnemyAnimationState::Moving;
    //     _clipRect.y = 32;
    //   } else {
    //     _state = EnemyAnimationState::Idle;
    //     _clipRect.y = 0;
    //   }
    //   _priorTicks = _ticks;
    // }

    // _clientRect.y -= _speed;
    // if (_clientRect.y + _clientRect.h <= 0) {
    //   _clientRect.y = 632;
    // }
    _clientRect.x += _movement.x;
    _clientRect.y += _movement.y;
    _collider->Update(_clientRect);

    if (_clientRect.x + _clientRect.w <= 0 || _clientRect.x >= 800 || _clientRect.y + _clientRect.h <= 0 ||
        _clientRect.y >= 600) {
      // Enemy is off screen
      Spawn();
    }
  }
}

void Enemy::Spawn() {
  // Pick a random location around the player

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
