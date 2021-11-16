#ifndef _echelon_hpp
#define _echelon_hpp

#include <SDL2/SDL.h>

#include <vector>

#include "Event.hpp"
#include "Game/Enemy.hpp"
#include "Math.hpp"

/**
 * @brief Formation for Enemy Sprites to travel on screen
 */
class Echelon : public CoffeeMaker::IUserEventListener {
  enum class MovementState { ShiftingLeft, ShiftingRight };

  using Vec2 = CoffeeMaker::Math::Vector2D;

  public:
  Echelon();
  ~Echelon();

  void Add(Enemy* enemy) { _enemies.push_back(enemy); }
  void Remove();

  Uint32 GetHeight();
  Uint32 GetSpacing();
  Uint32 GetWidth();

  void Update(float);
  void OnSDLUserEvent(const SDL_UserEvent&);

  private:
  Uint32 _height;
  Uint32 _width;
  Uint32 _spacing;
  Vec2 _position;
  float _speed;
  std::vector<Enemy*> _enemies;
  MovementState _movementState;
};

#endif
