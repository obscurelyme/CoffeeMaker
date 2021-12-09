#include "FontManager.hpp"

#include "Logger.hpp"
#include "Window.hpp"
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

  std::string msg = fmt::format(fmt::runtime("Could not find font {}"), fontName);
  SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Font Manager : Use Font", msg.c_str(), nullptr);
  exit(1);
  return nullptr;
}

TTF_Font* FontManager::UseFont(const std::string& fontName, FontSize size) {
  auto search = _fonts.find(fontName + "-" + std::to_string(size));
  if (search != _fonts.end()) {
    return search->second;
  }

  std::string msg = fmt::format(fmt::runtime("Could not find font {}"), fontName + "-" + std::to_string(size));
  SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Font Manager : Use Font", msg.c_str(), nullptr);
  exit(1);
  return nullptr;
}

void FontManager::LoadFont(const std::string& fontName) {
  std::string fontFilePath = fmt::format(fmt::runtime("{}{}"), CoffeeMaker::Utilities::AssetsDirectory(),
                                         fmt::format(fmt::runtime("/fonts/{}.ttf"), fontName));

  // Open 18pt font
  TTF_Font* font18 =
      TTF_OpenFont(fontFilePath.c_str(), static_cast<int>(CoffeeMaker::GlobalWindow::Instance()->DPIScale() * 18.0f));
  if (font18 == nullptr) {
    CM_LOGGER_CRITICAL("Could not load font from given filepath: {}", fontFilePath);
    std::string message =
        "The Font Mananger failed to load the font: " + fontName + " and because of this, the program will terminate.";
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Font Manager: LoadFont Failed", message.c_str(), nullptr);
    exit(1);
  }

  _fonts.emplace(fontName, font18);
  CM_LOGGER_TRACE("Font {} loaded", fontName);

  // Open 24pt font
  TTF_Font* font24 =
      TTF_OpenFont(fontFilePath.c_str(), static_cast<int>(CoffeeMaker::GlobalWindow::Instance()->DPIScale() * 24));
  if (font24 == nullptr) {
    CM_LOGGER_CRITICAL("Could not load font from given filepath: {}", fontFilePath);
    std::string message =
        "The Font Mananger failed to load the font: " + fontName + " and because of this, the program will terminate.";
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Font Manager: LoadFont Failed", message.c_str(), nullptr);
    exit(1);
  }

  _fonts.emplace(fontName + "-" + std::to_string(FontSize::FontSizeMedium), font24);
  CM_LOGGER_TRACE("Font {} loaded", fontName + "-" + std::to_string(FontSize::FontSizeMedium));

  // Open 32pt font
  TTF_Font* font32 =
      TTF_OpenFont(fontFilePath.c_str(), static_cast<int>(CoffeeMaker::GlobalWindow::Instance()->DPIScale() * 32.0f));
  if (font32 == nullptr) {
    CM_LOGGER_CRITICAL("Could not load font from given filepath: {}", fontFilePath);
    std::string message =
        "The Font Mananger failed to load the font: " + fontName + " and because of this, the program will terminate.";
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Font Manager: LoadFont Failed", message.c_str(), nullptr);
    exit(1);
  }

  _fonts.emplace(fontName + "-" + std::to_string(FontSize::FontSizeLarge), font32);
  CM_LOGGER_TRACE("Font {} loaded", fontName + "-" + std::to_string(FontSize::FontSizeLarge));

  // Open 48pt font
  TTF_Font* font48 =
      TTF_OpenFont(fontFilePath.c_str(), static_cast<int>(CoffeeMaker::GlobalWindow::Instance()->DPIScale() * 48.0f));
  if (font48 == nullptr) {
    CM_LOGGER_CRITICAL("Could not load font from given filepath: {}", fontFilePath);
    std::string message =
        "The Font Mananger failed to load the font: " + fontName + " and because of this, the program will terminate.";
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Font Manager: LoadFont Failed", message.c_str(), nullptr);
    exit(1);
  }

  _fonts.emplace(fontName + "-" + std::to_string(FontSize::FontSizeXLarge), font48);
  CM_LOGGER_TRACE("Font {} loaded", fontName + "-" + std::to_string(FontSize::FontSizeXLarge));
}
