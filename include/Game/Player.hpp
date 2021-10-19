#include <SDL2/SDL.h>

#include <chrono>
#include <vector>

#include "Game/Collider.hpp"
#include "Game/Entity.hpp"
#include "Projectile.hpp"
#include "Texture.hpp"

class Player : public Entity {
  public:
  Player();
  virtual ~Player();

  void Init();
  void Update();
  void Render();
  void Fire();
  void Reload();
  void OnHit(Collider* collider);

  private:
  CoffeeMaker::Texture _texture{"creature.png", true};
  SDL_Rect _clipRect{.x = 0, .y = 0, .w = 32, .h = 32};
  SDL_FRect _clientRect{.x = 400, .y = 300, .w = 32, .h = 32};

  double _rotation;
  int _mouseX;
  int _mouseY;
  std::vector<Projectile*> _projectiles;
  int _currentProjectile;
  bool _firing;
  Collider* _collider;
  bool _active;
  std::chrono::steady_clock::time_point _respawnTimerStart;
  std::chrono::duration<float, std::milli> _respawnTimer;
  unsigned int _lives;
};
