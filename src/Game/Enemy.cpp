#include "Game/Enemy.hpp"

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include <iostream>
#include <random>

#include "Event.hpp"
#include "Game/Events.hpp"
#include "Game/Player.hpp"
#include "Game/Scene.hpp"
#include "Logger.hpp"
#include "Renderer.hpp"
#include "Utilities.hpp"

unsigned int Enemy::_uid = 0;
std::random_device device;
std::default_random_engine engine(device());
std::uniform_real_distribution<double> distribution(0, 360);

Enemy::Enemy() :
    _id("Enemy-" + std::to_string(++_uid)),
    _active(false),
    _rotation(0),
    _speed(250.0f),
    _currentProjectile(0),
    _collider(nullptr),
    _sprite(CreateScope<CoffeeMaker::Sprite>("EnemyV1.png")),
    _entranceSpline2(CreateScope<Animations::EnemyEntrance001>()),
    _exitSpline(CreateScope<Animations::EnemyExit>()),
    // TIMEOUTS AND INTERVALS
    _fireMissileTask(CreateScope<CoffeeMaker::Async::IntervalTask>(
        [this] {
          CoffeeMaker::Logger::Trace("[ENEMY_EVENT][ENEMY_FIRE_MISSILE] - Enemy ID: {}", _id);
          CoffeeMaker::PushUserEvent(UCI::Events::ENEMY_FIRE_MISSILE, -1, this);
        },
        3000)),
    _exitTimeoutTask(CreateScope<CoffeeMaker::Async::TimeoutTask>(
        "[ENEMY][EXIT-TIMEOUT-TASK] - " + _id,
        [this] {
          CoffeeMaker::Logger::Trace("[ENEMY_EVENT][EXIT-TIMEOUT-TASK] - Enemy ID: {}", _id);
          CoffeeMaker::PushUserEvent(UCI::Events::ENEMY_BEGIN_EXIT, -1, this);
        },
        12000)),
    _respawnTimeoutTask(CreateScope<CoffeeMaker::Async::TimeoutTask>(
        "[ENEMY][RESPAWN-TIMEOUT-TASK] - " + _id,
        [this] {
          CoffeeMaker::Logger::Trace("[ENEMY_EVENT][RESPAWN-TIMEOUT-TASK] - Enemy ID: {}", _id);
          CoffeeMaker::PushUserEvent(UCI::Events::ENEMY_COMPLETE_EXIT, -1, this);
        },
        3000)),

    // TIMEOUTS AND INTERVALS
    _destroyedAnimation(CreateScope<UCI::Animations::ExplodeSpriteAnimation>()),
    _impactSound(CreateScope<CoffeeMaker::AudioElement>("effects/ProjectileImpact.ogg")),
    _state(Enemy::State::Idle),
    _aggression(Enemy::AggressionState::Active) {
  _position.x = 400;
  _position.y = 150;

  _sprite->clientRect.x = _position.x;
  _sprite->clientRect.y = _position.y;
  _sprite->clientRect.w = 48 * CoffeeMaker::Renderer::DynamicResolutionDownScale();
  _sprite->clientRect.h = 48 * CoffeeMaker::Renderer::DynamicResolutionDownScale();
  _entranceSpline2->OnComplete([this](void*) {
    CoffeeMaker::Logger::Trace("[ENEMY_EVENT][ENEMY_ENTRANCE_SPLINE] Complete Enemy ID: {}", _id);
    CoffeeMaker::Logger::Trace("[ENEMY][STATE_CHANGE][State=StrafingLeft] - {}", _id);
    _state = Enemy::State::StrafingLeft;
    _fireMissileTask->Start();
    _exitTimeoutTask->Start();
  });
  _exitSpline->OnComplete([this](void*) {
    CoffeeMaker::Logger::Trace("[ENEMY_EVENT][ENEMY_EXIT_SPLINE] Complete Enemy ID: {}", _id);
    _active = false;
    CoffeeMaker::Logger::Trace("[ENEMY][STATE_CHANGE][State=Idle] - {}", _id);
    _state = Enemy::State::Idle;
    _respawnTimeoutTask->Start();
  });

  _collider = CreateScope<Collider>(Collider::Type::Enemy, false);
  _collider->clientRect.h = _sprite->clientRect.h;
  _collider->clientRect.w = _sprite->clientRect.w;
  _collider->OnCollide(std::bind(&Enemy::OnCollision, this, std::placeholders::_1));

  for (int i = 0; i < 50; i++) {
    _projectiles.emplace_back(new Projectile(Collider::Type::EnemyProjectile));
  }
  _currentProjectile = 0;

  _destroyedAnimation->OnComplete([this] {
    CoffeeMaker::Logger::Trace("[ENEMY_EVENT][ENEMY_DESTROYED_ANIMATION] Complete Enemy ID: {}", _id);
    CoffeeMaker::Logger::Trace("[ENEMY][STATE_CHANGE][State=Idle] - {}", _id);
    _state = Enemy::State::Idle;
    _respawnTimeoutTask->Start();
  });
}

Enemy::~Enemy() {
  _destroyedAnimation->Stop();
  _exitTimeoutTask->Cancel();
  _fireMissileTask->Cancel();
  _respawnTimeoutTask->Cancel();
  for (auto p : _projectiles) {
    delete p;
  }
}

void Enemy::Init() {}

void Enemy::Render() {
  if (_state == Enemy::State::Destroyed) {
    _destroyedAnimation->Render();
  } else {
    if (_active) {
      _sprite->Render();
    }
  }

  for (auto& projectile : _projectiles) {
    projectile->Render();
  }
}

void Enemy::Pause() {
  _fireMissileTask->Pause();
  _exitTimeoutTask->Pause();
  _respawnTimeoutTask->Pause();
}

void Enemy::Unpause() {
  _fireMissileTask->Unpause();
  _exitTimeoutTask->Unpause();
  _respawnTimeoutTask->Unpause();
}

void Enemy::Update(float deltaTime) {
  using Vec2 = CoffeeMaker::Math::Vector2D;
  using Pt2 = CoffeeMaker::Math::Point2D;

  switch (_state) {
    case Enemy::State::StrafingLeft: {
      _rotation = 180;
      if (_position.x > 100 - _sprite->clientRect.w) {
        _position += Vec2::Left() * _speed * deltaTime;
      } else {
        _state = Enemy::State::StrafingRight;
      }
    } break;
    case Enemy::State::StrafingRight: {
      _rotation = 180;
      if (_position.x < 700) {
        _position += Vec2::Right() * _speed * deltaTime;
      } else {
        _state = Enemy::State::StrafingLeft;
      }
    } break;
    case Enemy::State::Entering: {
      if (!SceneManager::CurrentScenePaused()) {
        _entranceSpline2->Update(deltaTime);
      }

      Pt2 pt = _entranceSpline2->CurrentPosition();
      Vec2 currentPos{pt.x, pt.y};

      _rotation = CoffeeMaker::Math::rad2deg(_position.LookAt(currentPos)) + 90;
      _position = currentPos;
    } break;
    case Enemy::State::Exiting: {
      if (!SceneManager::CurrentScenePaused()) {
        _exitSpline->Update(deltaTime);
      }

      Vec2 currentPos = _exitSpline->Position();

      _rotation = CoffeeMaker::Math::rad2deg(_position.LookAt(currentPos)) + 90;
      _position = currentPos;
    } break;
    default: {
      // NOTE: do nothing for now...
    } break;
  }

  _sprite->rotation = _rotation;
  _sprite->SetPosition(_position);
  _collider->Update(_sprite->clientRect);

  for (auto& projectile : _projectiles) {
    projectile->Update(deltaTime);
  }
}

void Enemy::Spawn() {
  CoffeeMaker::Logger::Trace("[ENEMY][STATE_CHANGE][State=Entering] - {}", _id);
  _state = Enemy::State::Entering;
  _collider->active = false;
  _collider->Update(_sprite->clientRect);
  _active = true;
  _collider->active = true;
}

bool Enemy::IsActive() const { return _active; }

void Enemy::OnCollision(Collider* collider) {
  if (_collider->active) {
    if (collider->GetType() == Collider::Type::Projectile && _collider->active) {
      CoffeeMaker::PushUserEvent(UCI::Events::ENEMY_DESTROYED, -1, this);
      CoffeeMaker::PushUserEvent(UCI::Events::PLAYER_INCREMENT_SCORE);
      return;
    }

    if (collider->GetType() == Collider::Type::Player && _collider->active) {
      _impactSound->Play();
      CoffeeMaker::PushUserEvent(UCI::Events::ENEMY_DESTROYED, -1, this);
      return;
    }
  }
}

bool Enemy::IsOffScreen() const {
  // TODO: screen width and height should be dynamic
  return _position.x + _sprite->clientRect.w <= 0 || _position.x >= 800 || _position.y + _sprite->clientRect.h <= 0 ||
         _position.y >= 600;
}

void Enemy::Fire() {
  // NOTE: sloppy but should kinda work for now
  float rot =
      CoffeeMaker::Math::rad2deg(_position.LookAt(Player::Position())) + CoffeeMaker::Math::PolarRotate::QUARTER;
  if (_currentProjectile < 24) {
    if (!_projectiles[_currentProjectile + 1]->IsFired()) {
      _projectiles[_currentProjectile++]->Fire2(_position.x, _position.y, Player::Position().x, Player::Position().y,
                                                rot);
    } else {
      _currentProjectile += 2;
    }
  } else if (_currentProjectile == 24) {
    _currentProjectile = 0;
    // NOTE: fire the next, or else projectiles are unavailable for a frame.
    _projectiles[_currentProjectile++]->Fire2(_position.x, _position.y, Player::Position().x, Player::Position().y,
                                              rot);
  }
}

void Enemy::SetAggressionState(AggressionState state) { _aggression = state; }

void Enemy::OnSDLUserEvent(const SDL_UserEvent& event) {
  if (event.type == UCI::Events::ENEMY_DESTROYED && event.data1 == this) {
    CoffeeMaker::Logger::Trace("[ENEMY_EVENT][ENEMY_DESTROYED]: Enemy ID: {}", _id);
    using Vec2 = CoffeeMaker::Math::Vector2D;
    _fireMissileTask->Cancel();
    _exitTimeoutTask->Cancel();
    _active = false;
    _collider->active = false;
    CoffeeMaker::Logger::Trace("[ENEMY][STATE_CHANGE][State=Destroyed] - {}", _id);
    _state = State::Destroyed;
    _destroyedAnimation->SetPosition(Vec2{_position.x, _position.y});
    _destroyedAnimation->Start();
    return;
  }
  if (event.type == UCI::Events::ENEMY_SPAWNED && event.data1 == this) {
    CoffeeMaker::Logger::Trace("[ENEMY_EVENT][ENEMY_SPAWNED]: Enemy ID: {}", _id);
    _entranceSpline2->Reset();
    _exitSpline->Reset();
    Spawn();
    return;
  }
  if (event.type == UCI::Events::ENEMY_FIRE_MISSILE && event.data1 == this) {
    CoffeeMaker::Logger::Trace("[ENEMY_EVENT][ENEMY_FIRE_MISSILE]: Enemy ID: {}", _id);
    if (_aggression == Enemy::AggressionState::Active) {
      Fire();
    }
    return;
  }
  if (event.type == UCI::Events::ENEMY_BEGIN_EXIT && event.data1 == this) {
    CoffeeMaker::Logger::Trace("[ENEMY_EVENT][ENEMY_BEGIN_EXIT]: Enemy ID: {}", _id);
    CoffeeMaker::Logger::Trace("[ENEMY][STATE_CHANGE][State=Exiting] - {}", _id);
    _state = State::Exiting;
    _fireMissileTask->Cancel();
    return;
  }
  if (event.type == UCI::Events::ENEMY_COMPLETE_EXIT && event.data1 == this) {
    // NOTE: Does the same thing as Spawned right now
    CoffeeMaker::Logger::Trace("[ENEMY_EVENT][ENEMY_COMPLETE_EXIT]: Enemy ID: {}", _id);
    _entranceSpline2->Reset();
    _exitSpline->Reset();
    Spawn();
  }
  if (event.type == UCI::Events::PLAYER_DESTROYED || event.type == UCI::Events::PLAYER_LOST_GAME) {
    CoffeeMaker::Logger::Trace("[ENEMY_EVENT][ENEMY_AGGRESSION_STATE_CHANGED]: Enemy [ id={}, aggression=Passive ]",
                               _id);
    _aggression = Enemy::AggressionState::Passive;
  }
  if (event.type == UCI::Events::PLAYER_COMPLETE_SPAWN) {
    CoffeeMaker::Logger::Trace("[ENEMY_EVENT][ENEMY_AGGRESSION_STATE_CHANGED]: Enemy [ id={}, aggression=Active ]",
                               _id);
    _aggression = Enemy::AggressionState::Active;
  }
}

EchelonEnemy::EchelonEnemy() {
  _entranceSpline2->OnComplete([this](void*) {
    // NOTE: sync with the echelon once we've entered the scene
    _echelonState = EchelonItem::EchelonState::Synced;
  });

  _exitTimeoutTask = CreateScope<CoffeeMaker::Async::TimeoutTask>(
      "[ENEMY][EXIT-TIMEOUT-TASK] - " + _id,
      [this] {
        _echelonState = EchelonItem::EchelonState::Solo;
        CoffeeMaker::PushUserEvent(UCI::Events::ENEMY_BEGIN_EXIT, -1, this);
        CoffeeMaker::Logger::Trace("[ENEMY_EVENT][EXIT-TIMEOUT-TASK] - Enemy ID: {}", _id);
      },
      12000);
}

void EchelonEnemy::Update(float deltaTime) {
  if (_echelonState == EchelonItem::EchelonState::Synced) {
    // Synced state stuff
    _sprite->rotation = 180;
    _sprite->SetPosition(_position);
    _collider->Update(_sprite->clientRect);

    for (auto& projectile : _projectiles) {
      projectile->Update(deltaTime);
    }
  }
  if (_echelonState == EchelonItem::EchelonState::Solo) {
    // Solo state stuff
    if (_state == Enemy::State::Entering) {
      // Set to would-be position in echelon
      using Pt2 = CoffeeMaker::Math::Point2D;
      using Vec2 = CoffeeMaker::Math::Vector2D;
      Vec2 currentPos = GetEchelonPosition();
      _entranceSpline2->SetFinalPosition(Pt2{.x = currentPos.x, .y = currentPos.y});
    }
    Enemy::Update(deltaTime);
  }
}

CoffeeMaker::Math::Vector2D EchelonEnemy::GetEchelonPosition() {
  using Vec2 = CoffeeMaker::Math::Vector2D;

  if (_echelon != nullptr) {
    Vec2 currentPos{0, 0};
    Vec2 echelonPos = _echelon->GetPosition();
    currentPos.y = echelonPos.y;
    currentPos.x = echelonPos.x + (GetEchelonSpace() * static_cast<float>(_echelonIndex)) +
                   (_echelon->GetSpacing() * static_cast<float>(_echelonIndex));
    return currentPos;
  }

  return Vec2{0, 0};
}

void EchelonEnemy::SetEchelonPosition(const Vec2& echelonPosition) {
  _position.x = echelonPosition.x + (GetEchelonSpace() * static_cast<float>(_echelonIndex)) +
                (_echelon->GetSpacing() * static_cast<float>(_echelonIndex));
  _position.y = echelonPosition.y;
}

float EchelonEnemy::GetEchelonSpace() { return _sprite->clientRect.w; }

void EchelonEnemy::OnSDLUserEvent(const SDL_UserEvent& event) {
  if (event.type == UCI::Events::ENEMY_DESTROYED) {
    if (event.data1 == this) {
      _echelonState = EchelonItem::EchelonState::Solo;
    }
  }

  Enemy::OnSDLUserEvent(event);
}

Drone::Drone() {
  _entranceSpline2 = CreateScope<Animations::EnemyEntrance001>(true);
  _entranceSpline2->OnComplete([this](void*) {
    _echelonState = EchelonItem::EchelonState::Synced;
    _fireMissileTask->Start();
    _exitTimeoutTask->Start();
  });
}

Drone::~Drone() {}
