#ifndef _coffeemaker_button_hpp
#define _coffeemaker_button_hpp

#include <SDL2/SDL.h>

namespace CoffeeMaker
{

  class Button
  {
  public:
    void Draw();

    void OnMouseover();
    void OnClick();
    void OnMouseleave();

    int top;
    int left;
    int width;
    int height;
    int padding;
    void *children;
    SDL_Rect _clientRect;
  };

}

#endif