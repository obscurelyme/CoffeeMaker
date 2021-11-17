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
#include "Game/Entity.hpp"
#include "Game/Projectile.hpp"
#include "Math.hpp"
#include "Texture.hpp"
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
  Scope<Animations::BaseSplineAnimation> _entranceSpline;
  Scope<Animations::EnemyExit> _exitSpline;
  Scope<CoffeeMaker::Async::IntervalTask> _fireMissileTask;
  Scope<CoffeeMaker::Async::TimeoutTask> _exitTimeoutTask;
  Scope<CoffeeMaker::Async::TimeoutTask> _respawnTimeoutTask;
  Scope<UCI::Animations::ExplodeSpriteAnimation> _destroyedAnimation;
  Scope<CoffeeMaker::AudioElement> _impactSound;
  State _state;
  AggressionState _aggression;
};

class Drone : public Enemy {
  public:
  Drone();
  virtual ~Drone();
};

// class SpecialEnemy : public Enemy {
//   public:
//   SpecialEnemy();
//   virtual ~SpecialEnemy();

//   virtual void Init();
//   virtual void Update(float deltaTime);
//   virtual void Render();
//   virtual void Pause();
//   virtual void Unpause();

//   virtual void Spawn();

//   protected:
//   CoffeeMaker::Math::Vector2D _transformVector;
//   CoffeeMaker::Math::Vector2D _endVector;
//   float _totalTime{3.0f};
//   float _currentTime{0.0f};
//   bool _moveright{true};
// };

#endif
