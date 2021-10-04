#include "Game/Enemy.hpp"

Enemy::Enemy() {
  _priorTicks = SDL_GetTicks();
  _ticks = _priorTicks;
}

Enemy::~Enemy() {}

void Enemy::Init() {}

void Enemy::Render() { _texture.Render(_clipRect, _clientRect); }

void Enemy::Update() {
  _ticks = SDL_GetTicks();
  if (_ticks > _priorTicks + 750) {
    if (_state == EnemyAnimationState::Idle) {
      _state = EnemyAnimationState::Moving;
      _clipRect.y = 32;
    } else {
      _state = EnemyAnimationState::Idle;
      _clipRect.y = 0;
    }
    _priorTicks = _ticks;
  }

  _clientRect.y -= _speed;
  if (_clientRect.y + _clientRect.h <= 0) {
    _clientRect.y = 632;
  }
}
