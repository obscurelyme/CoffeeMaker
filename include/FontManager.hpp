#ifndef _coffeemaker_fontmanager_hpp
#define _coffeemaker_fontmanager_hpp

#include <string>
#include <map>
#include <filesystem>
#include <fmt/core.h>
#include <SDL2/SDL_ttf.h>
#include <spdlog/spdlog.h>
#include "Utilities.hpp"

namespace CoffeeMaker
{

  class FontManager
  {
  public:
    ~FontManager() = default;
    /**
     * Load a font within the /assets/font directory
     */
    static void LoadFont(const std::string& name);
    static void Init();
    static void Detroy();
    static TTF_Font* UseFont(const std::string& fontName);

  private:
    FontManager();

    static std::map<std::string, TTF_Font *> _fonts;
  };

}

#endif
