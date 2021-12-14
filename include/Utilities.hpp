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

/**
 * @brief Creates a Ref (std::shared_ptr) object
 */
template <typename T, typename... Args>
constexpr Ref<T> CreateRef(Args &&...args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

template <typename T>
using Scope = std::unique_ptr<T>;

/**
 * @brief Creates a Scope (std::unique_ptr) object
 */
template <typename T, typename... Args>
constexpr Scope<T> CreateScope(Args &&...args) {
  return std::make_unique<T>(std::forward<Args>(args)...);
}

namespace CoffeeMaker {

  namespace Utilities {
    extern const char *_baseDir;
    extern std::string _assetDir;

    void Init(const char *);
    const std::string BaseDirectory();
    const std::string AssetsDirectory();
  }  // namespace Utilities

}  // namespace CoffeeMaker

#endif
