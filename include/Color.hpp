#ifndef _coffeemaker_color_hpp
#define _coffeemaker_color_hpp

#include <SDL2/sdl.h>

namespace CoffeeMaker {
SDL_Color Color(unsigned char r = 0, unsigned char g = 0, unsigned char b = 0,
                unsigned char a = 255);
}

#endif