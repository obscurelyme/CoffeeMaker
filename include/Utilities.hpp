#ifndef _coffeemaker_utilities_hpp
#define _coffeemaker_utilities_hpp

#include <string>
#include <fmt/core.h>
#include <filesystem>

namespace CoffeeMaker
{

  namespace Utilities
  {

    std::string EXECUTABLE_PATH = "";

    /**
     * Returns the working directory the executable is located in.
     * Use this to reference relative filepath locations
     */
    const std::string ExecutableWorkingDirectory()
    {
      return std::filesystem::weakly_canonical(std::filesystem::path(EXECUTABLE_PATH)).parent_path().string();
    }

    /**
     * Returns the full location of the assets directory
     */
    const std::string AssetsDirectory()
    {
      return fmt::format("{}/assets", ExecutableWorkingDirectory());
    }

    /**
     * Returns the full location of the assets directory
     */
    const std::string ImagesDirectory()
    {
      return fmt::format("{}/images", AssetsDirectory());
    }

    /**
     * Returns the full location of the assets directory
     */
    const std::string WithinImagesDirectory(std::string filePath)
    {
      return fmt::format("{}/images/{}", AssetsDirectory(), filePath);
    }

    /**
     * Returns the full location of the assets directory
     */
    const std::string FontsDirectory()
    {
      return fmt::format("{}/fonts", AssetsDirectory());
    }

  }

}

#endif