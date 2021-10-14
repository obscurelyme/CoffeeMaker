#include "Color.hpp"

SDL_Color CoffeeMaker::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
  SDL_Color c{.r = r, .g = g, .b = b, .a = a};
  return c;
}

SDL_Color CoffeeMaker::Colors::Black = CoffeeMaker::Color();
SDL_Color CoffeeMaker::Colors::White = CoffeeMaker::Color(255, 255, 255, 255);
SDL_Color CoffeeMaker::Colors::Yellow = CoffeeMaker::Color(255, 255, 0, 255);
