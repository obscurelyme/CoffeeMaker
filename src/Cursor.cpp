#include "Cursor.hpp"

#include <SDL2/SDL_image.h>

#include "Logger.hpp"
#include "Texture.hpp"
#include "Utilities.hpp"

using namespace CoffeeMaker;

Cursor::Cursor(const std::string& filePath) : _cursor(nullptr) {
  SDL_Surface* surface = nullptr;
  std::string cursorImgPath =
      fmt::format(fmt::runtime("{}/{}/{}"), CoffeeMaker::Utilities::AssetsDirectory(), "ui", filePath);
  surface = IMG_Load(cursorImgPath.c_str());
  if (surface == nullptr) {
    Logger::Error("Could not load cursor surface");
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "IMG_Load returned NULLPTR", "Could not load cursor surface", NULL);
    exit(1);
  }
  SDL_SetColorKey(surface, SDL_TRUE,
                  SDL_MapRGB(surface->format, CoffeeMaker::Texture::COLOR_KEY.r, CoffeeMaker::Texture::COLOR_KEY.g,
                             CoffeeMaker::Texture::COLOR_KEY.b));
  _cursor = SDL_CreateColorCursor(surface, 0, 0);
  SDL_SetCursor(_cursor);
  SDL_FreeSurface(surface);
}

Cursor::~Cursor() {
  SDL_FreeCursor(_cursor);
  _cursor = nullptr;
}
