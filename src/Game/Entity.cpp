#include "Game/Entity.hpp"
#include "Renderer.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Logger.hpp"

Enemy::Enemy() {
  _priorTicks = SDL_GetTicks();
  _ticks = _priorTicks;
}

void Enemy::Render() {
  _texture.Render(_clipRect, _clientRect);
}

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

Player::Player() {
  _firing = false;
  SDL_Rect vp;
  SDL_RenderGetViewport(CoffeeMaker::Renderer::Instance(), &vp);
  // NOTE: center the player sprite in the viewport
  _clientRect.x = (vp.w - _clientRect.w) / 2;
  _clientRect.y = (vp.h - _clientRect.h) / 2;
}

void Player::Update() {
  const Uint8* states = SDL_GetKeyboardState(NULL);

  if (states[SDL_SCANCODE_F]) {
    Fire();
  }

  if (states[SDL_SCANCODE_R]) {
    _projectile.Reload();
  }

  SDL_GetMouseState(&_mouseX, &_mouseY);
  int xx = _mouseX - _clientRect.x;
  int yy = _mouseY - _clientRect.y;
  if (xx == 0) {
    // Dividing by 0 will result in a crash
    _rotation = 0;
    return;
  }
  float t = (float)(yy / xx);
  _rotation = (atan2(yy, xx) * (180/M_PI)) + 360;
  _projectile.Update();
}

void Player::Render() {
  // SDL_RendererFlip flip = SDL_FLIP_NONE;
  _texture.Render(_clipRect, _clientRect, _rotation + 90);
  _projectile.Render();
  // SDL_RenderCopyEx(CoffeeMaker::Renderer::Instance(), _texture.Handle(), &_clipRect, &_clientRect, _rotation + 90, NULL, flip);
}

void Player::Fire() {
  _projectile.Fire(_clientRect.x, _clientRect.y, _rotation + 90);
}
