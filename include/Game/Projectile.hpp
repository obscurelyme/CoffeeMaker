#ifndef _projectile_hpp
#define _projectile_hpp

#include <SDL2/SDL.h>
#include "Texture.hpp"
#include <memory>
#include <glm/glm.hpp>

#include "Game/Collider.hpp"

class Projectile {
  public:
    Projectile();
    ~Projectile();

    void Fire(float initialXPosition, float initialYPosition, double rotation);
    void Reload();
    void Update();
    void Render();

  private:
    static std::shared_ptr<CoffeeMaker::Texture> _texture;
    bool _fired;
    SDL_FRect _clientRect;
    double _rotation;
    float _endX;
    float _endY;
    glm::vec2 _movement;
    Collider* collider;
};

#endif
