#ifndef _projectile_hpp
#define _projectile_hpp

#include <SDL2/SDL.h>
#include "Texture.hpp"
#include <memory>

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
    SDL_Rect _clientRect;
    double _rotation;
};

#endif
