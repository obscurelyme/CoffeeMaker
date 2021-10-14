#ifndef _coffeemaker_color_hpp
#define _coffeemaker_color_hpp

#include <SDL2/sdl.h>

namespace CoffeeMaker {
  SDL_Color Color(unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, unsigned char a = 255);

  namespace Colors {
    extern SDL_Color Black;
    extern SDL_Color Yellow;
    extern SDL_Color White;
    extern SDL_Color Green;
    extern SDL_Color Red;
    extern SDL_Color Blue;
    extern SDL_Color Purple;
  }  // namespace Colors
}  // namespace CoffeeMaker

#endif
