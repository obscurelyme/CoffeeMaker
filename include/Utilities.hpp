#ifndef _coffeemaker_utilities_hpp
#define _coffeemaker_utilities_hpp

#include <fmt/core.h>

#include <filesystem>
#include <memory>
#include <string>

/**
 * Alias type for std::shared_ptr
 */
template <typename T>
using Ref = std::shared_ptr<T>;

namespace CoffeeMaker {

  namespace Utilities {
    extern const char *_baseDir;

    void Init(const char *);
    const std::string BaseDirectory();
    const std::string AssetsDirectory();
  }  // namespace Utilities

}  // namespace CoffeeMaker

#endif
