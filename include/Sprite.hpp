#ifndef _coffeemaker_sprite_hpp
#define _coffeemaker_sprite_hpp

#include <string>

#include "Math.hpp"
#include "Texture.hpp"
#include "Utilities.hpp"

namespace CoffeeMaker {
  class Sprite {
    public:
    explicit Sprite(const std::string& filePath);
    Sprite(const std::string& filePath, float width, float height);
    ~Sprite();

    void Render();
    void SetPosition(const CoffeeMaker::Math::Vector2D& pos);

    double rotation;
    SDL_Rect clipRect;
    SDL_FRect clientRect;

    private:
    Scope<CoffeeMaker::Texture> _texture;
  };
}  // namespace CoffeeMaker

#endif
