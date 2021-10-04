#include <SDL2/SDL.h>

#include "Game/Entity.hpp"
#include "Texture.hpp"

class Enemy : public Entity {
  public:
  Enemy();
  virtual ~Enemy();

  void Init();
  void Update();
  void Render();

  private:
  CoffeeMaker::Texture _texture{"creature.png", true};
  SDL_Rect _clipRect{.x = 0, .y = 0, .w = 32, .h = 32};
  SDL_Rect _clientRect{.x = 0, .y = 625, .w = 32, .h = 32};

  EnemyAnimationState _state{EnemyAnimationState::Idle};
  unsigned int _ticks;
  unsigned int _priorTicks;
  unsigned int _speed{1};
};
