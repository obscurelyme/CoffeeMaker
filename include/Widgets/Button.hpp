#ifndef _coffeemaker_button_hpp
#define _coffeemaker_button_hpp

#include <SDL2/SDL.h>
#include <string>
#include "Color.hpp"
#include "Texture.hpp"

namespace CoffeeMaker
{

  class Button
  {
  public:
    Button();

    void Draw();

    void OnEvent(SDL_Event *e);
    void OnMouseover();
    void OnClick();
    void OnMouseleave();

    void Render();

    int top;
    int left;
    int width;
    int height;
    int padding;
    void *children;
    SDL_Rect _clientRect;
    Texture _texture;
  };

} // CoffeeMaker

#endif
