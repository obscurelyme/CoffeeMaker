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
    ~FontManager() = default;
    /**
     * Load a font within the /assets/font directory
     */
<<<<<<< HEAD
    static void LoadFont(const std::string& name);
    static void Init();
    static void Destroy();
    static TTF_Font* UseFont(const std::string& fontName);
=======
    void loadFont(std::string name)
    {
      std::string fontFilePath = fmt::format(fmt::runtime("{0}{1}"), CoffeeMaker::Utilities::AssetsDirectory(), fmt::format(fmt::runtime("/fonts/{0}.ttf"), name));
      // TODO recognize DPI Scaling
      TTF_Font *font = TTF_OpenFont(fontFilePath.c_str(), 1 * 16);
      if (font == nullptr)
      {
        spdlog::critical("Could not load font from given filePath: {}", fontFilePath);
      }

      _fonts.emplace(name, font);
    }
>>>>>>> d2c4845 (some c make options)

    private:
    FontManager();

    static std::map<std::string, TTF_Font*> _fonts;
  };

}  // namespace CoffeeMaker

#endif
