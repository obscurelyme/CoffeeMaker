#include "Color.hpp"

SDL_Color CoffeeMaker::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
  SDL_Color c{.r = r, .g = g, .b = b, .a = a};
  return c;
}
