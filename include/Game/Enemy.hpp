#include <SDL2/SDL.h>

#include <glm/glm.hpp>
#include <string>

#include "Game/Collider.hpp"
#include "Game/Entity.hpp"
#include "Texture.hpp"
#include "Utilities.hpp"

class Enemy : public Entity {
  public:
  Enemy();
  virtual ~Enemy();

  void Init();
  void Update(float deltaTime);
  void Render();
  void Spawn();
  bool IsActive() const;
  void OnCollision(Collider* collider);
  bool IsOffScreen() const;

  private:
  CoffeeMaker::Texture _texture{"creature.png", true};
  SDL_Rect _clipRect{.x = 0, .y = 0, .w = 32, .h = 32};
  SDL_FRect _clientRect{.x = 0, .y = 0, .w = 32, .h = 32};
  glm::vec2 _movement;
  Ref<Collider> _collider;

  bool _enteredScreen;
  bool _active;
  std::string _id;

  static unsigned int _uid;

  EnemyAnimationState _state{EnemyAnimationState::Idle};
  unsigned int _ticks;
  unsigned int _priorTicks;
  // unsigned int _speed{1};
};
