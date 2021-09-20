#include "Cursor.hpp"

#include <SDL2/SDL_image.h>

#include "Logger.hpp"
#include "Texture.hpp"
#include "Utilities.hpp"

using namespace CoffeeMaker;

Cursor::Cursor(const std::string& filePath) : _cursor(nullptr) {
  std::string cursorImgPath =
      fmt::format(fmt::runtime("{}/{}/{}"), CoffeeMaker::Utilities::AssetsDirectory(), "images", filePath);
  SDL_Surface* surface = IMG_Load(cursorImgPath.c_str());
  SDL_SetColorKey(surface, SDL_TRUE,
                  SDL_MapRGB(surface->format, CoffeeMaker::Texture::COLOR_KEY.r, CoffeeMaker::Texture::COLOR_KEY.g,
                             CoffeeMaker::Texture::COLOR_KEY.b));
  _cursor = SDL_CreateColorCursor(surface, surface->w / 2, surface->h / 2);
  SDL_SetCursor(_cursor);
  SDL_FreeSurface(surface);
}

Cursor::~Cursor() {
  SDL_FreeCursor(_cursor);
  _cursor = nullptr;
}
