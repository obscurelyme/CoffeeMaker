#ifndef _projectile_hpp
#define _projectile_hpp

#include <SDL2/SDL.h>
#include "Texture.hpp"
#include <memory>
#include <glm/glm.hpp>

class Projectile {
  public:
    Projectile();
    void Fire(int initialXPosition, int initialYPosition, double rotation);
    void Reload();
    void Update();
    void Render();
  private:
    static std::shared_ptr<CoffeeMaker::Texture> _texture;
    bool _fired;
    SDL_FRect _clientRect;
    double _rotation;
    int _endX;
    int _endY;
    glm::vec2 _movement;
};

#endif
