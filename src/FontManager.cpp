#include "FontManager.hpp"

#include "Logger.hpp"
#include "fmt/core.h"

using namespace CoffeeMaker;

std::map<std::string, TTF_Font*> FontManager::_fonts = {};

void FontManager::Init() {
  if (TTF_Init() == -1) {
    CM_LOGGER_CRITICAL("Could not initialize SDL-TTF");
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Font Manager: Init Failed",
                             "Failed to intialize the FontManager, program will terminate.", nullptr);
    exit(1);
  }
}

void FontManager::Destroy() {
  for (const auto& font : _fonts) {
    TTF_CloseFont(font.second);
  }
  _fonts.clear();
}

TTF_Font* FontManager::UseFont(const std::string& fontName) {
  auto search = _fonts.find(fontName);
  if (search != _fonts.end()) {
    return search->second;
  }
  std::string msg = fmt::format("Could not find font {}", fontName);
  SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Font Manager : Use Font", msg.c_str(), nullptr);
  exit(1);
  return nullptr;
}

void FontManager::LoadFont(const std::string& fontName) {
  std::string fontFilePath =
      fmt::format("{}{}", CoffeeMaker::Utilities::AssetsDirectory(), fmt::format("/fonts/{}.ttf", fontName));
  // TODO recognize DPI Scaling
  TTF_Font* font = TTF_OpenFont(fontFilePath.c_str(), 1 * 16);
  if (font == nullptr) {
    CM_LOGGER_CRITICAL("Could not load font from given filepath: {}", fontFilePath);
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Font Manager: LoadFont Failed",
                             "The Font Mananger failed to load a font, program will terminate.", nullptr);
    exit(1);
  }

  _fonts.emplace(fontName, font);
}
