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
    FontManager() : _fonts({})
    {
      if (TTF_Init() == -1)
      {
        spdlog::critical("Could not initialize SDL-TTF!");
        exit(1);
      }
    }
    ~FontManager()
    {
      for (const auto &[key, value] : _fonts)
      {
        TTF_CloseFont(value);
      }
    }

    /**
     * Load a font within the /assets/font directory
     */
    void loadFont(std::string name)
    {
      std::string fontFilePath = fmt::format("{}{}", CoffeeMaker::Utilities::AssetsDirectory(), fmt::format("/fonts/{}.ttf", name));
      // TODO recognize DPI Scaling
      TTF_Font *font = TTF_OpenFont(fontFilePath.c_str(), 1 * 16);
      if (font == nullptr)
      {
        spdlog::critical("Could not load font from given filePath: {}", fontFilePath);
      }

      _fonts.emplace(name, font);
    }

    TTF_Font *useFont(std::string name)
    {
      auto search = _fonts.find(name);
      if (search != _fonts.end())
      {
        return search->second;
      }
      return nullptr;
    }

  private:
    std::map<std::string, TTF_Font *> _fonts;
  };

}

#endif
