#include <SDL2/SDL.h>

#include <chrono>
#include <glm/glm.hpp>
#include <vector>

#include "Game/Collider.hpp"
#include "Game/Entity.hpp"
#include "Projectile.hpp"
#include "Texture.hpp"
#include "Timer.hpp"

class Player : public Entity {
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

  private:
  void UpdateRespawnImmunity();

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
  // std::chrono::steady_clock::time_point _respawnTimerStart;
  // std::chrono::duration<float, std::milli> _respawnTimer;
  CoffeeMaker::Timer _immunityTimer;
  CoffeeMaker::Timer _respawnTimer;
  unsigned int _lives;
  glm::vec2 _direction{1.0f, 0.0f};
  int _speed = 225;
};
