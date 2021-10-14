#include "Color.hpp"

SDL_Color CoffeeMaker::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
  SDL_Color c{.r = r, .g = g, .b = b, .a = a};
  return c;
}

SDL_Color CoffeeMaker::Colors::Black = CoffeeMaker::Color();
SDL_Color CoffeeMaker::Colors::White = CoffeeMaker::Color(255, 255, 255, 255);
SDL_Color CoffeeMaker::Colors::Yellow = CoffeeMaker::Color(255, 255, 0, 255);
SDL_Color CoffeeMaker::Colors::Green = CoffeeMaker::Color(0, 255, 0, 255);
SDL_Color CoffeeMaker::Colors::Red = CoffeeMaker::Color(255, 0, 0, 255);
SDL_Color CoffeeMaker::Colors::Blue = CoffeeMaker::Color(0, 0, 255, 255);
SDL_Color CoffeeMaker::Colors::Purple = CoffeeMaker::Color(255, 0, 255, 255);
