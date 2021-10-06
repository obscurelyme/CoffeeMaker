#ifndef _coffeemaker_utilities_hpp
#define _coffeemaker_utilities_hpp

#include <fmt/core.h>

#include <filesystem>
#include <string>

namespace CoffeeMaker {

namespace Utilities {
extern const char *_baseDir;

void Init(const char *);
const std::string BaseDirectory();
const std::string AssetsDirectory();
}  // namespace Utilities

}  // namespace CoffeeMaker

#endif
