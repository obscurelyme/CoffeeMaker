#ifndef _game_player_hpp
#define _game_player_hpp

#include <SDL2/SDL.h>

#include <chrono>
#include <glm/glm.hpp>
#include <vector>

#include "Async.hpp"
#include "Audio.hpp"
#include "Game/Animations/Explode.hpp"
#include "Game/Collider.hpp"
#include "Game/Entity.hpp"
#include "Math.hpp"
#include "PowerUps/BasePowerUp.hpp"
#include "Projectile.hpp"
#include "Texture.hpp"
#include "Timer.hpp"
#include "Utilities.hpp"

class Player : public Entity, public CoffeeMaker::IUserEventListener {
  enum FireMissileState { Locked, Unlocked };

  public:
  static CoffeeMaker::Math::Vector2D Position();
  // NOTE: This is to keep track of stupid developers doing stupid things.
  static Player* _instance;

  public:
  Player();
  virtual ~Player();

  void Init();
  void Update(float deltaTime);
  void Render();
  void Pause();
  void Unpause();

  void Fire();
  void Reload();
  void OnHit(Collider* collider);

  void OnSDLUserEvent(const SDL_UserEvent& event);

  private:
  void UpdateRespawnImmunity();
  bool IsOffScreenLeft();
  bool IsOffScreenRight();
  void HandleDestroy(Collider* collider);
  void HandlePowerUpGained(Sint32 eventCode);
  void HandlePowerUpLost(Sint32 eventCode);

  CoffeeMaker::Texture _texture{"PlayerV1.png", true};
  SDL_Rect _clipRect{.x = 0, .y = 0, .w = 32, .h = 32};
  SDL_FRect _clientRect{.x = 0, .y = 0, .w = 48, .h = 48};

  bool _isImmune;
  double _rotation;
  std::vector<Projectile*> _projectiles;
  int _currentProjectile;
  bool _firing;
  Collider* _collider;
  bool _active;
  bool _destroyed;
  unsigned int _lives;
  glm::vec2 _direction{1.0f, 0.0f};
  int _speed = 225;
  Scope<UCI::Animations::ExplodeSpriteAnimation> _destroyedAnimation;
  Scope<CoffeeMaker::Async::TimeoutTask> _asyncRespawnTask;
  Scope<CoffeeMaker::Async::TimeoutTask> _asyncImmunityTask;
  Scope<CoffeeMaker::AudioElement> _impactSound;
  Scope<CoffeeMaker::Math::Oscillate> _oscillation;
  Scope<CoffeeMaker::Async::TimeoutTask> _fireDelay;
  Player::FireMissileState _fireMissileState;
  Scope<UCI::Warp> _warpPowerup;
};

#endif
