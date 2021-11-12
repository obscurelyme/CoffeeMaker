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
    _fireMissileTask(nullptr),
    _destroyedAnimation(CreateScope<UCI::Animations::ExplodeSpriteAnimation>()),
    _collider(nullptr),
    _sprite(CreateScope<CoffeeMaker::Sprite>("EnemyV1.png")),
    _entranceSpline(CreateScope<Animations::EnemyEntrance>()),
    _exitSpline(CreateScope<Animations::EnemyExit>()),
    _exitTimeoutTask(CreateScope<CoffeeMaker::Async::TimeoutTask>(
        "[ENEMY][EXIT-TIMEOUT-TASK] - " + _id,
        [this] {
          CM_LOGGER_INFO("[ENEMY_EVENT] _exitTimeoutTask completed Enemy ID: {}", _id);
          CoffeeMaker::PushEvent(UCI::Events::ENEMY_BEGIN_EXIT, this);
        },
        12000)),
    _respawnTimeoutTask(CreateScope<CoffeeMaker::Async::TimeoutTask>(
        "[ENEMY][RESPAWN-TIMEOUT-TASK] - " + _id,
        [this] { CoffeeMaker::PushEvent(UCI::Events::ENEMY_COMPLETE_EXIT, this); }, 3000)),
    _impactSound(CreateScope<CoffeeMaker::AudioElement>("effects/ProjectileImpact.ogg")),
    _state(Enemy::State::Idle) {
  _position.x = 400;
  _position.y = 150;

  _sprite->clientRect.x = _position.x;
  _sprite->clientRect.y = _position.y;
  _sprite->clientRect.w = 48;
  _sprite->clientRect.h = 48;
  _entranceSpline->OnComplete([this](void*) {
    // CM_LOGGER_INFO("[ENEMY_EVENT] _entranceSpline Complete Enemy ID: {}", _id);
    _state = Enemy::State::StrafingLeft;
    _fireMissileTask->Start();
    // __debugbreak();
    CM_LOGGER_INFO("[ENEMY_EVENT] Entrance Animation Complete Enemy ID: {}", _id);
    _exitTimeoutTask->Start();
  });
  _exitSpline->OnComplete([this](void*) {
    // CM_LOGGER_INFO("[ENEMY_EVENT] _exitSpline Complete Enemy ID: {}", _id);
    _active = false;
    _state = Enemy::State::Idle;
    CM_LOGGER_INFO("[ENEMY_EVENT] Exit Animation Complete Enemy ID: {}", _id);
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
    // CM_LOGGER_INFO("[ENEMY_EVENT] Destroyed Animation Complete - Enemy ID: {}", _id);
    _state = Enemy::State::Idle;
    _respawnTimeoutTask->Start();
  });
  _fireMissileTask = CreateScope<CoffeeMaker::Async::IntervalTask>(
      [this] {
        // CM_LOGGER_INFO("[ENEMY_EVENT] _fireMissileTask Complete Enemy ID: {}", _id);
        CoffeeMaker::PushEvent(UCI::Events::ENEMY_FIRE_MISSILE, this);
      },
      3000);
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

  switch (_state) {
    // case Enemy::State::WillExit_StrafeLeft: {
    //   MoveLeft(deltaTime);
    //   if (_position.x <= 400) {
    //     _state = Enemy::State::Exiting;
    //   }
    // } break;
    // case Enemy::State::WillExit_StrafeRight: {
    //   MoveRight(deltaTime);
    //   if (_position.x >= 400) {
    //     _state = Enemy::State::Exiting;
    //   }
    // } break;
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
        _entranceSpline->Update(deltaTime);
      }

      Vec2 currentPos = _entranceSpline->Position();

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
  }

  _sprite->rotation = _rotation;
  _sprite->SetPosition(_position);
  _collider->Update(_sprite->clientRect);

  for (auto& projectile : _projectiles) {
    projectile->Update(deltaTime);
  }
}

void Enemy::Spawn() {
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
      CoffeeMaker::PushEvent(UCI::Events::ENEMY_DESTROYED, this);
      CoffeeMaker::PushEvent(UCI::Events::PLAYER_INCREMENT_SCORE);
      return;
    }

    if (collider->GetType() == Collider::Type::Player && _collider->active) {
      _impactSound->Play();
      CoffeeMaker::PushEvent(UCI::Events::ENEMY_DESTROYED, this);
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

void Enemy::OnSDLUserEvent(const SDL_UserEvent& event) {
  if (event.code == UCI::Events::ENEMY_DESTROYED && event.data1 == this) {
    // CM_LOGGER_INFO("[ENEMY_EVENT] - ENEMY_DESTROYED: Enemy ID: {}", _id);

    using Vec2 = CoffeeMaker::Math::Vector2D;
    // _respawnTimeoutTask->Cancel();
    _fireMissileTask->Cancel();
    _exitTimeoutTask->Cancel();
    _active = false;
    _collider->active = false;
    _state = State::Destroyed;
    _destroyedAnimation->SetPosition(Vec2{_position.x, _position.y});
    _destroyedAnimation->Start();
    return;
  }
  if (event.code == UCI::Events::ENEMY_SPAWNED && event.data1 == this) {
    // CM_LOGGER_INFO("[ENEMY_EVENT] - ENEMY_SPAWNED: Enemy ID: {}", _id);
    // _exitTimeoutTask->Reset();
    _entranceSpline->Reset();
    _exitSpline->Reset();
    Spawn();
    return;
  }
  if (event.code == UCI::Events::ENEMY_FIRE_MISSILE && event.data1 == this) {
    // CM_LOGGER_INFO("[ENEMY_EVENT] - ENEMY_FIRE_MISSILE: Enemy ID: {}", _id);
    Fire();
    return;
  }
  if (event.code == UCI::Events::ENEMY_BEGIN_EXIT && event.data1 == this) {
    // CM_LOGGER_INFO("[ENEMY_EVENT] - ENEMY_BEGIN_EXIT: Enemy ID: {}", _id);
    _state = State::Exiting;
    _fireMissileTask->Cancel();
    return;
  }
  if (event.code == UCI::Events::ENEMY_COMPLETE_EXIT && event.data1 == this) {
    // NOTE: Does the same thing as Spawned right now
    // CM_LOGGER_INFO("[ENEMY_EVENT] - ENEMY_COMPLETE_EXIT: Enemy ID: {}", _id);
    _entranceSpline->Reset();
    _exitSpline->Reset();
    Spawn();
  }
}

Drone::Drone() {
  // NOTE: override the parent _entranceSpline
  _entranceSpline = CreateScope<::Animations::EnemyBriefEntrance>();
  _entranceSpline->OnComplete([this](void*) {
    _state = Enemy::State::StrafingLeft;
    // _fireMissileTask->Start();
    // _exitTimeoutTask->Start();
  });
}

Drone::~Drone() {}

// SpecialEnemy::SpecialEnemy() {}

// SpecialEnemy::~SpecialEnemy() {}

// void SpecialEnemy::Init() {
//   _transformVector.x = 0;
//   _transformVector.y = 600;
//   _endVector.x = 400;
//   _endVector.y = 300;
//   _clientRect.x = _transformVector.x;
//   _clientRect.y = _transformVector.y;
// }

// void SpecialEnemy::Update(float deltaTime) {
//   using Vec2 = CoffeeMaker::Math::Vector2D;
//   if (_active) {
//     _currentTime += deltaTime;
//     float weight = _currentTime / 1.5f;
//     Vec2 pos{_clientRect.x, _clientRect.y};
//     _rotation = CoffeeMaker::Math::rad2deg(pos.LookAt(Player::Position())) + 90;
//     if (weight <= 1.0f) {
//       CoffeeMaker::Math::Vector2D currentPos = CoffeeMaker::Math::CubicBezierCurve(
//           CoffeeMaker::Math::Vector2D(-200.0f, 600.0f), CoffeeMaker::Math::Vector2D(0.0f, -50.0f),
//           CoffeeMaker::Math::Vector2D(800.0f, 0.0f), CoffeeMaker::Math::Vector2D(400.0f, 150.0f), weight);
//       _clientRect.x = currentPos.x;
//       _clientRect.y = currentPos.y;
//       _collider->Update(_clientRect);
//     } else {
//       // NOTE: side to side motion
//       if (_moveright) {
//         // move right
//         _clientRect.x += deltaTime * (_speed);
//         _collider->Update(_clientRect);
//         if (_clientRect.x >= 700) {
//           _moveright = false;
//         }
//       } else {
//         // move left
//         _clientRect.x -= deltaTime * (_speed);
//         _collider->Update(_clientRect);
//         if (_clientRect.x <= 100) {
//           _moveright = true;
//         }
//       }
//     }

//     if (!_enteredScreen && !IsOffScreen()) {
//       _enteredScreen = true;
//     }

//     if (IsOffScreen() && _enteredScreen) {
//       // Enemy went off screen
//       Spawn();
//     }
//   }
//   // NOTE: projectiles that have already been fired are still fine to be updated
//   for (auto& projectile : _projectiles) {
//     projectile->Update(deltaTime);
//   }
// }

// void SpecialEnemy::Render() {
//   if (_destroyed) {
//     _destroyedAnimation->Render();
//   } else {
//     SDL_RendererFlip flip = SDL_FLIP_NONE;
//     SDL_RenderCopyExF(CoffeeMaker::Renderer::Instance(), _texture.Handle(), &_clipRect, &_clientRect, _rotation,
//     NULL,
//                       flip);
//   }

//   for (auto& projectile : _projectiles) {
//     projectile->Render();
//   }
// }

// void SpecialEnemy::Pause() { _fireMissileTask->Pause(); }

// void SpecialEnemy::Unpause() { _fireMissileTask->Unpause(); }

// void SpecialEnemy::Spawn() {
//   _currentTime = 0.0f;
//   _enteredScreen = false;
//   _collider->active = false;
//   _moveright = false;

//   _clientRect.x = _transformVector.x;
//   _clientRect.y = _transformVector.y;
//   _collider->Update(_clientRect);

//   _active = true;
//   _collider->active = true;
// }
