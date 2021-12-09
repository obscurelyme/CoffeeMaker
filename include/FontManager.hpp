#ifndef _coffeemaker_fontmanager_hpp
#define _coffeemaker_fontmanager_hpp

#include <SDL2/SDL_ttf.h>
#include <fmt/core.h>
#include <spdlog/spdlog.h>

#include <filesystem>
#include <map>
#include <string>

#include "Utilities.hpp"

namespace CoffeeMaker {

  class FontManager {
    public:
    enum FontSize {
      FontSizeSmall = 16,
      FontSizeRegular = 18,
      FontSizeMedium = 24,
      FontSizeLarge = 32,
      FontSizeXLarge = 48
    };
    ~FontManager() = default;
    /**
     * Load a font within the /assets/font directory
     */
    static void LoadFont(const std::string& name);
    static void Init();
    static void Destroy();
    static TTF_Font* UseFont(const std::string& fontName);
    static TTF_Font* UseFont(const std::string& fontName, FontSize size);

    private:
    FontManager();

    static std::map<std::string, TTF_Font*> _fonts;
  };

}  // namespace CoffeeMaker

#endif
