#include "Utilities.hpp"

#include <SDL2/SDL.h>

namespace CoffeeMaker::Utilities {
  const char *_baseDir = "";
}

void CoffeeMaker::Utilities::Init(const char *base) { CoffeeMaker::Utilities::_baseDir = base; }

const std::string CoffeeMaker::Utilities::BaseDirectory() { return CoffeeMaker::Utilities::_baseDir; }

const std::string CoffeeMaker::Utilities::AssetsDirectory() {
  return fmt::format("{}{}", CoffeeMaker::Utilities::_baseDir, "assets");
}
