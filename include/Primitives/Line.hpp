#ifndef _coffeemaker_primitive_line_hpp
#define _coffeemaker_primitive_line_hpp

#include <SDL2/SDL.h>

namespace CoffeeMaker
{

  namespace Shapes
  {

    class Line
    {
    private:
      explicit Line();

    public:
      explicit Line(int length, int top = 0, int left = 0, float angle = 0.0f);
      ~Line();

      void Render();
      void Rotate(float angle);

      float angleDegrees;
      float angleRadians;
      int top;
      int left;
      int length;
      int endX;
      int endY;
      SDL_Color color;
    };

  } // Primitives

} // CoffeeMaker

#endif
