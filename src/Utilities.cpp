#include "Utilities.hpp"

#include <SDL2/SDL.h>

namespace CoffeeMaker::Utilities {
  const char *_baseDir = "";
  std::string _assetDir = "";
}  // namespace CoffeeMaker::Utilities

void CoffeeMaker::Utilities::Init(const char *base) {
  CoffeeMaker::Utilities::_baseDir = base;
  CoffeeMaker::Utilities::_assetDir = fmt::format("{}{}", CoffeeMaker::Utilities::_baseDir, "assets");
}

const std::string CoffeeMaker::Utilities::BaseDirectory() { return CoffeeMaker::Utilities::_baseDir; }

const std::string CoffeeMaker::Utilities::AssetsDirectory() { return CoffeeMaker::Utilities::_assetDir; }
