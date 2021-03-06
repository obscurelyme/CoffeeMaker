#include "Game/Player.hpp"

#include <algorithm>
#include <chrono>
#include <functional>
#include <glm/glm.hpp>

#include "Event.hpp"
#include "Game/Events.hpp"
#include "Game/Scene.hpp"
#include "Game/ScoreManager.hpp"
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
    _lives(3),
    _destroyedAnimation(CreateScope<UCI::Animations::ExplodeSpriteAnimation>()),
    _asyncRespawnTask(CreateScope<CoffeeMaker::Async::TimeoutTask>(
        "[PLAYER][RESPAWN-TASK]",
        [] {
          CoffeeMaker::Logger::Debug("[PLAYER_EVENT] - PLAYER_WILL_SPAWN");
          CoffeeMaker::PushUserEvent(UCI::Events::PLAYER_POWER_UP_GAINED_IMMUNITY);
          CoffeeMaker::PushUserEvent(UCI::Events::PLAYER_COMPLETE_SPAWN);
        },
        3000)),
    _asyncImmunityTask(CreateScope<CoffeeMaker::Async::TimeoutTask>(
        "[PLAYER][IMMUNITY-POWER-UP-DURATION]",
        [] { CoffeeMaker::PushUserEvent(UCI::Events::PLAYER_POWER_UP_LOST_IMMUNITY); }, 3000)),
    _impactSound(CreateScope<CoffeeMaker::AudioElement>("effects/ProjectileImpact.ogg")),
    _oscillation(CreateScope<CoffeeMaker::Math::Oscillate>(128.0f, 255.0f, 0.025f)),
    _fireDelay(CreateScope<CoffeeMaker::Async::TimeoutTask>(
        "[PLAYER][FIRE-MISSILE-DELAY]",
        [] {
          CoffeeMaker::Logger::Debug("[PLAYER_EVENT] - FIRE-MISSILE-DELAY event was pushed");
          CoffeeMaker::PushUserEvent(UCI::Events::PLAYER_FIRE_DELAY_END);
        },
        250)),
    _fireMissileState(Player::FireMissileState::Unlocked),
    _warpPowerup(CreateScope<UCI::Warp>()) {
  if (_instance != nullptr) {
    // NOTE: You really messed this one up.
    CoffeeMaker::Logger::Critical("[PLAYER_EVENT][CONSTRUCTION] - An instance of the player class already exists.");
    CoffeeMaker::PushEvent(CoffeeMaker::ApplicationEvents::COFFEEMAKER_GAME_QUIT);
  }
  _firing = false;
  SDL_Rect vp;
  SDL_RenderGetViewport(CoffeeMaker::Renderer::Instance(), &vp);
  _clientRect.x = (vp.w - _clientRect.w) / 2;
  _clientRect.y = (vp.h - _clientRect.h) - 50;
  for (int i = 0; i < 25; i++) {
    _projectiles.emplace_back(
        new Projectile(Collider::Type::Projectile, Projectile::Type::Friendly, Projectile::Size::Small));
  }
  _currentProjectile = 0;
  _collider->clientRect.h = _clientRect.h;
  _collider->clientRect.w = _clientRect.w;
  _collider->Update(_clientRect);
  _collider->OnCollide(std::bind(&Player::OnHit, this, std::placeholders::_1));
  _destroyedAnimation->OnComplete([] { CoffeeMaker::PushUserEvent(UCI::Events::PLAYER_BEGIN_SPAWN); });
  _oscillation->OnEnd = [this] {
    _isImmune = false;
    _texture.SetAlpha(255);
  };
  _instance = this;
}

Player::~Player() {
  _asyncRespawnTask->Cancel();
  _asyncImmunityTask->Cancel();
  _destroyedAnimation->Stop();
  _fireDelay->Cancel();
  _instance = nullptr;
  delete _collider;
  for (auto p : _projectiles) {
    delete p;
  }
  _instance = nullptr;
}

void Player::OnHit(Collider* collider) {
  if (_collider->active) {
    if (collider->GetType() == Collider::Type::EnemyProjectile && !_isImmune) {
      HandleDestroy(collider);
      return;
    }

    if (collider->GetType() == Collider::Type::Enemy && !_isImmune) {
      _impactSound->Play();
      HandleDestroy(collider);
    }
  }
}

void Player::HandleDestroy(Collider* collider) {
  _collider->active = false;
  _active = false;
  if (_lives - 1 == 0) {
    CoffeeMaker::PushUserEvent(UCI::Events::PLAYER_LOST_GAME);
    return;
  }
  _lives--;
  CoffeeMaker::PushUserEvent(UCI::Events::PLAYER_LOST_LIFE);
  CoffeeMaker::PushUserEvent(UCI::Events::PLAYER_DESTROYED);
  CoffeeMaker::Logger::Debug("[PLAYER_EVENT]-PLAYER_DESTROYED {}", collider->ToString());
}

void Player::Init() {}

void Player::Pause() {}

void Player::Unpause() {}

void Player::Update(float deltaTime) {
  if (_active) {
    _rotation = -90;

    if (CoffeeMaker::InputManager::IsKeyPressed(SDL_SCANCODE_W)) {
      _warpPowerup->Use();
    }

    if (CoffeeMaker::InputManager::IsKeyPressed(SDL_SCANCODE_SPACE)) {
      if (_fireMissileState == Player::FireMissileState::Unlocked) {
        Fire();
        _fireDelay->Start();
      }
    }

    if (CoffeeMaker::InputManager::IsKeyDown(SDL_SCANCODE_LEFT)) {
      // strafe left
      _clientRect.x = std::max(_clientRect.x - deltaTime * _speed, 50.0f);
      _rotation -= 8;
    }

    if (CoffeeMaker::InputManager::IsKeyDown(SDL_SCANCODE_RIGHT)) {
      // strafe right
      _clientRect.x = std::min(_clientRect.x + deltaTime * _speed, CoffeeMaker::Renderer::GetOutputWidth() - 50.0f);
      _rotation += 8;
    }

    _collider->Update(_clientRect);
  }

  // NOTE: projectiles that have already been fired are still fine to be updated
  for (auto& projectile : _projectiles) {
    projectile->Update(deltaTime);
  }

  if (_isImmune && !_oscillation->Ended()) {
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
  CoffeeMaker::Logger::Debug("[PLAYER_EVENT] - FIRED-MISSILE");
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

void Player::HandlePowerUpGained(Sint32 event) {
  if (event == UCI::PowerUp::PowerUpType::Warp) {
    CoffeeMaker::Logger::Debug("[PLAYER_EVENT][PLAYER_POWER_UP_GAINED][WARP]");
    _speed = 1800.0f * CoffeeMaker::Renderer::DynamicResolutionDownScale();
  }
}

void Player::HandlePowerUpLost(Sint32 event) {
  if (event == UCI::PowerUp::PowerUpType::Warp) {
    CoffeeMaker::Logger::Debug("[PLAYER_EVENT][PLAYER_POWER_UP_LOST][WARP]");
    _speed = 350.0f * CoffeeMaker::Renderer::DynamicResolutionDownScale();
  }
}

void Player::OnSDLUserEvent(const SDL_UserEvent& event) {
  if (event.type == UCI::Events::PLAYER_POWER_UP_GAINED) {
    HandlePowerUpGained(event.code);
    return;
  }

  if (event.type == UCI::Events::PLAYER_POWER_UP_LOST) {
    HandlePowerUpLost(event.code);
    return;
  }

  if (event.code == CoffeeMaker::ApplicationEvents::COFFEEMAKER_GAME_PAUSE) {
    _asyncRespawnTask->Pause();
    _asyncImmunityTask->Pause();
    _fireDelay->Pause();
    return;
  }

  if (event.code == CoffeeMaker::ApplicationEvents::COFFEEMAKER_GAME_UNPAUSE) {
    _asyncRespawnTask->Unpause();
    _asyncImmunityTask->Unpause();
    _fireDelay->Unpause();
    return;
  }

  if (event.type == UCI::Events::PLAYER_BEGIN_SPAWN) {
    CoffeeMaker::Logger::Debug("[PLAYER_EVENT] - PLAYER_BEGIN_SPAWN");
    _destroyed = false;
    _asyncRespawnTask->Start();
    return;
  }

  if (event.type == UCI::Events::PLAYER_POWER_UP_GAINED_IMMUNITY) {
    CoffeeMaker::Logger::Debug("[PLAYER_EVENT] - PLAYER_POWER_UP_GAINED_IMMUNITY");
    _isImmune = true;
    _asyncImmunityTask->Start();
    _oscillation->Start();
    return;
  }

  if (event.type == UCI::Events::PLAYER_POWER_UP_LOST_IMMUNITY) {
    CoffeeMaker::Logger::Debug("[PLAYER_EVENT] - PLAYER_POWER_UP_LOST_IMMUNITY");
    _oscillation->Stop();
    return;
  }

  if (event.type == UCI::Events::PLAYER_COMPLETE_SPAWN) {
    _active = true;
    _collider->active = true;
    return;
  }

  if (event.type == UCI::Events::PLAYER_FIRE_DELAY_END) {
    CoffeeMaker::Logger::Debug("[PLAYER_EVENT] - FIRE-MISSILE-DELAY event was received");
    _fireMissileState = Player::FireMissileState::Unlocked;
  }

  if (event.type == UCI::Events::PLAYER_DESTROYED) {
    _destroyed = true;
    _destroyedAnimation->SetPosition(CoffeeMaker::Math::Vector2D{_clientRect.x, _clientRect.y});
    _destroyedAnimation->Start();
  }

  if (event.type == UCI::Events::PLAYER_LOST_GAME) {
    _destroyed = true;
    _destroyedAnimation->OnComplete([] { CoffeeMaker::PushUserEvent(UCI::LOAD_NEW_SCENE, 2); });
    _destroyedAnimation->SetPosition(CoffeeMaker::Math::Vector2D{_clientRect.x, _clientRect.y});
    _destroyedAnimation->Start();
  }
}
