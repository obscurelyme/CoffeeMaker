#ifndef _game_enemy_hpp
#define _game_enemy_hpp

#include <SDL2/SDL.h>

#include <functional>
#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "Async.hpp"
#include "Audio.hpp"
#include "Event.hpp"
#include "Game/Animations/EnemyAnimations.hpp"
#include "Game/Animations/Explode.hpp"
#include "Game/Collider.hpp"
#include "Game/Echelon.hpp"
#include "Game/Entity.hpp"
#include "Game/Events.hpp"
#include "Game/Projectile.hpp"
#include "Math.hpp"
#include "Texture.hpp"
#include "Timer.hpp"
#include "Utilities.hpp"

class Enemy : public Entity, public CoffeeMaker::IUserEventListener {
  public:
  enum State { Idle, Entering, Exiting, Destroyed, StrafingRight, StrafingLeft, WillExit };
  enum AggressionState { Active, Passive };

  public:
  Enemy();
  virtual ~Enemy();

  virtual void Init();
  virtual void Update(float deltaTime);
  virtual void Render();
  virtual void Pause();
  virtual void Unpause();
  virtual void Fire();

  virtual void Spawn();
  bool IsActive() const;
  virtual void OnCollision(Collider* collider);
  bool IsOffScreen() const;
  void SetAggressionState(AggressionState state);

  virtual void OnSDLUserEvent(const SDL_UserEvent& event);

  protected:
  static unsigned int _uid;

  std::string _id;
  bool _active;
  double _rotation;
  float _speed;
  int _currentProjectile;
  Ref<Collider> _collider;
  std::vector<Projectile*> _projectiles;
  Scope<CoffeeMaker::Sprite> _sprite;
  CoffeeMaker::Math::Vector2D _position;
  Scope<Animations::EnemyEntrance001> _entranceSpline2;
  Scope<Animations::EnemyExit001> _exitSpline;
  Scope<CoffeeMaker::Async::IntervalTask> _fireMissileTask;
  Scope<CoffeeMaker::Async::TimeoutTask> _exitTimeoutTask;
  Scope<CoffeeMaker::Async::TimeoutTask> _respawnTimeoutTask;
  Scope<UCI::Animations::ExplodeSpriteAnimation> _destroyedAnimation;
  Scope<CoffeeMaker::AudioElement> _impactSound;
  State _state;
  AggressionState _aggression;
};

class EchelonEnemy : public Enemy, public EchelonItem {
  using Vec2 = CoffeeMaker::Math::Vector2D;

  public:
  EchelonEnemy();
  virtual ~EchelonEnemy() = default;

  virtual void Update(float deltaTime);
  virtual Vec2 GetEchelonPosition();
  virtual void SetEchelonPosition(const Vec2& echelonPosition);
  virtual float GetEchelonSpace();
  virtual void OnSDLUserEvent(const SDL_UserEvent& event);
};

class Drone : public EchelonEnemy {
  public:
  Drone();
  virtual ~Drone();
};

#endif
