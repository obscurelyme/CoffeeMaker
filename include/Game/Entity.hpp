#ifndef _game_entity_hpp
#define _game_entity_hpp

#include <SDL2/SDL.h>
#include "Texture.hpp"
#include "Projectile.hpp"

enum class EnemyAnimationState {
  Idle,
  Moving
};

class Enemy {
  public:
    Enemy();
    ~Enemy() = default;

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

class Player {
  public:
    Player();
    ~Player() = default;

    void Update();
    void Render();
    void Fire();

  private:
    CoffeeMaker::Texture _texture{"creature.png", true};
    SDL_Rect _clipRect{.x = 0, .y = 0, .w = 32, .h = 32};
    SDL_Rect _clientRect{.x = 400, .y = 300, .w = 32, .h = 32};

    double _rotation;
    int _mouseX;
    int _mouseY;
    Projectile _projectile;
    bool _firing;
};

#endif
