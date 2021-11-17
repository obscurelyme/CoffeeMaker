#include "Game/Player.hpp"

#include <algorithm>
#include <chrono>
#include <functional>
#include <glm/glm.hpp>

#include "Event.hpp"
#include "Game/Events.hpp"
#include "Game/Scene.hpp"
#include "InputManager.hpp"
#include "Logger.hpp"
#include "Math.hpp"
#include "Renderer.hpp"

Player* Player::_instance = nullptr;

CoffeeMaker::Math::Vector2D Player::Position() {
  return CoffeeMaker::Math::Vector2D(_instance->_clientRect.x, _instance->_clientRect.y);
}

Player::Player() :
    _isImmune(false),
    _collider(new Collider(Collider::Type::Player, true)),
    _active(true),
    _destroyed(false),
    _lives(999),
    _destroyedAnimation(CreateScope<UCI::Animations::ExplodeSpriteAnimation>()),
    _asyncRespawnTask(CreateScope<CoffeeMaker::Async::TimeoutTask>(
        "[PLAYER][RESPAWN-TASK]",
        [] {
          CM_LOGGER_INFO("[PLAYER_EVENT] - PLAYER_WILL_SPAWN");
          CoffeeMaker::PushEvent(UCI::Events::PLAYER_POWER_UP_GAINED_IMMUNITY);
          CoffeeMaker::PushEvent(UCI::Events::PLAYER_COMPLETE_SPAWN);
        },
        3000)),
    _asyncImmunityTask(CreateScope<CoffeeMaker::Async::TimeoutTask>(
        "[PLAYER][IMMUNITY-POWER-UP-DURATION]",
        [] { CoffeeMaker::PushEvent(UCI::Events::PLAYER_POWER_UP_LOST_IMMUNITY); }, 3000)),
    _impactSound(CreateScope<CoffeeMaker::AudioElement>("effects/ProjectileImpact.ogg")),
    _oscillation(CreateScope<CoffeeMaker::Math::Oscillate>(128.0f, 255.0f, 0.025f)),
    _fireDelay(CreateScope<CoffeeMaker::Async::TimeoutTask>(
        "[PLAYER][FIRE-MISSILE-DELAY]",
        [] {
          CM_LOGGER_INFO("[PLAYER_EVENT] - FIRE-MISSILE-DELAY event was pushed");
          CoffeeMaker::PushEvent(UCI::Events::PLAYER_FIRE_DELAY_END);
        },
        250)),
    _fireMissileState(Player::FireMissileState::Unlocked),
    _fireSDLDelay(CreateScope<CoffeeMaker::SDLTimer>(
        250,
        [](Uint32, void* params) {
          std::pair<CoffeeMaker::SDLTimer*, Player*>* p =
              reinterpret_cast<std::pair<CoffeeMaker::SDLTimer*, Player*>*>(params);
          SDL_LockMutex(p->first->paused);
          CM_LOGGER_INFO("[PLAYER_EVENT] - SDL Timer is up");
          CoffeeMaker::PushEvent(UCI::Events::PLAYER_FIRE_DELAY_END);
          SDL_UnlockMutex(p->first->paused);
          return static_cast<Uint32>(0);
        },
        nullptr)) {
  _firing = false;
  SDL_Rect vp;
  SDL_RenderGetViewport(CoffeeMaker::Renderer::Instance(), &vp);
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
  _destroyedAnimation->OnComplete([] { CoffeeMaker::PushEvent(UCI::Events::PLAYER_BEGIN_SPAWN); });
}

Player::~Player() {
  _asyncRespawnTask->Cancel();
  _asyncImmunityTask->Cancel();
  _destroyedAnimation->Stop();
  _fireDelay->Cancel();
  _fireSDLDelay->Stop();
  _instance = nullptr;
  delete _collider;
  for (auto p : _projectiles) {
    delete p;
  }
}

void Player::OnHit(Collider* collider) {
  if (_collider->active) {
    if (collider->GetType() == Collider::Type::EnemyProjectile && !_isImmune) {
      HandleDestroy();
      return;
    }

    if (collider->GetType() == Collider::Type::Enemy && !_isImmune) {
      _impactSound->Play();
      HandleDestroy();
    }
  }
}

void Player::HandleDestroy() {
  using Vec2 = CoffeeMaker::Math::Vector2D;
  _collider->active = false;
  _active = false;
  if (_lives - 1 == 0) {
    // TODO: timeout here and then boot to main menu
    SceneManager::LoadScene(0);
    return;
  }
  _lives--;
  CoffeeMaker::PushEvent(UCI::Events::PLAYER_LOST_LIFE);
  CoffeeMaker::PushEvent(UCI::Events::PLAYER_DESTROYED);
  _destroyed = true;
  _destroyedAnimation->SetPosition(Vec2{_clientRect.x, _clientRect.y});
  _destroyedAnimation->Start();
  CM_LOGGER_INFO("[PLAYER_EVENT] - PLAYER_DESTROYED");
}

void Player::Init() {}

void Player::Pause() {}

void Player::Unpause() {}

void Player::Update(float deltaTime) {
  if (_active) {
    _rotation = -90;

    if (CoffeeMaker::InputManager::IsKeyPressed(SDL_SCANCODE_SPACE)) {
      if (_fireMissileState == Player::FireMissileState::Unlocked) {
        Fire();
        _fireDelay->Start2();
        //_fireSDLDelay->Start();
      }
    }

    if (CoffeeMaker::InputManager::IsKeyDown(SDL_SCANCODE_LEFT)) {
      // strafe left
      _clientRect.x = std::max(_clientRect.x - deltaTime * _speed, 50.0f);
      _rotation -= 8;
    }

    if (CoffeeMaker::InputManager::IsKeyDown(SDL_SCANCODE_RIGHT)) {
      // strafe right
      _clientRect.x = std::min(_clientRect.x + deltaTime * _speed, 702.0f);
      _rotation += 8;
    }

    _collider->Update(_clientRect);
  }

  // NOTE: projectiles that have already been fired are still fine to be updated
  for (auto& projectile : _projectiles) {
    projectile->Update(deltaTime);
  }

  if (_isImmune) {
    _texture.SetAlpha(static_cast<Uint8>(_oscillation->Update()));
  }
}

void Player::Render() {
  if (_destroyed) {
    _destroyedAnimation->Render();
  }

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
  CM_LOGGER_INFO("[PLAYER_EVENT] - FIRED-MISSILE");
  _fireMissileState = Player::FireMissileState::Locked;
}

void Player::Reload() {
  for (auto& projectile : _projectiles) {
    projectile->Reload();
  }
  _currentProjectile = 0;
}

bool Player::IsOffScreenLeft() { return _clientRect.x + _clientRect.w <= 0; }
bool Player::IsOffScreenRight() { return _clientRect.x >= 800; }

void Player::OnSDLUserEvent(const SDL_UserEvent& event) {
  if (event.code == CoffeeMaker::ApplicationEvents::COFFEEMAKER_GAME_PAUSE) {
    // CM_LOGGER_INFO("[PLAYER_EVENT] - COFFEEMAKER_GAME_PAUSE");

    _asyncRespawnTask->Pause();
    _asyncImmunityTask->Pause();
    _fireDelay->Pause();
    _fireSDLDelay->Pause();
    return;
  }

  if (event.code == CoffeeMaker::ApplicationEvents::COFFEEMAKER_GAME_UNPAUSE) {
    // CM_LOGGER_INFO("[PLAYER_EVENT] - COFFEEMAKER_GAME_UNPAUSE");

    _asyncRespawnTask->Unpause();
    _asyncImmunityTask->Unpause();
    _fireDelay->Unpause();
    _fireSDLDelay->Unpause();
    return;
  }

  if (event.code == UCI::Events::PLAYER_BEGIN_SPAWN) {
    // CM_LOGGER_INFO("[PLAYER_EVENT] - PLAYER_BEGIN_SPAWN");
    _destroyed = false;
    _asyncRespawnTask->Start2();
    return;
  }

  if (event.code == UCI::Events::PLAYER_POWER_UP_GAINED_IMMUNITY) {
    // CM_LOGGER_INFO("[PLAYER_EVENT] - PLAYER_POWER_UP_GAINED_IMMUNITY");
    _isImmune = true;
    _asyncImmunityTask->Start2();
    _oscillation->Start();
    return;
  }

  if (event.code == UCI::Events::PLAYER_POWER_UP_LOST_IMMUNITY) {
    // CM_LOGGER_INFO("[PLAYER_EVENT] - PLAYER_POWER_UP_LOST_IMMUNITY");
    _isImmune = false;
    _oscillation->Stop();
    return;
  }

  if (event.code == UCI::Events::PLAYER_COMPLETE_SPAWN) {
    _active = true;
    _collider->active = true;
    return;
  }

  if (event.code == UCI::Events::PLAYER_FIRE_DELAY_END) {
    CM_LOGGER_INFO("[PLAYER_EVENT] - FIRE-MISSILE-DELAY event was received");
    _fireMissileState = Player::FireMissileState::Unlocked;
  }
}
