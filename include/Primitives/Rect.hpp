#ifndef _coffeemaker_primitive_rect_hpp
#define _coffeemaker_primitive_rect_hpp

#include <SDL2/SDL.h>

#include "Color.hpp"

namespace CoffeeMaker
{

  namespace Shapes
  {

    class Rect
    {
    public:
      explicit Rect();
      Rect(int height, int width);
      Rect(int height, int width, int top, int left);

      void Render();

      int Height();
      int Width();
      int Top();
      int Left();

      SDL_Rect clientRect;
      SDL_Color color;
      bool filled;
    };

  }

}

#endif
