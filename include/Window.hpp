#ifndef _coffeemaker_window_hpp
#define _coffeemaker_window_hpp

#include <SDL2/SDL.h>
#include <string>
#include <fmt/core.h>

namespace CoffeeMaker
{
  const float BASE_DPI = 96.0f;
  SDL_Surface *GLOBAL_SCREEN_SURFACE;
  float GLOBAL_DPI_SCALE = 1.0f;

  class DotsPerInch
  {
  public:
    float diagonal;
    float horizontal;
    float vertical;

    std::string toString()
    {
      return fmt::format("Diagonal {}, Horizontal {}, Vertical {}", diagonal, horizontal, vertical);
    }
  };

  /**
   * Base window class from which other windows may inherit from
   */
  class Window
  {
  public:
    Window(std::string title, int width, int height)
    {
      int windowFlags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
      _window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, windowFlags);
      _dpi = DotsPerInch();
      _dpiScale = _dpi.diagonal / CoffeeMaker::BASE_DPI;

      // TODO: need a better way to do this...use global variables contained to namespace for now
      GLOBAL_DPI_SCALE = _dpiScale;
      GLOBAL_SCREEN_SURFACE = SDL_GetWindowSurface(_window);
    }
    ~Window()
    {
      if (_window != nullptr)
      {
        SDL_DestroyWindow(_window);
        _window = nullptr;
      }
    }

    SDL_Window *const instance() const
    {
      return _window;
    }

    /**
     * Explicitly calls the destructor
     */
    void Destroy()
    {
      this->~Window();
    }

    int DisplayCount()
    {
      return SDL_GetNumVideoDisplays();
    }

    CoffeeMaker::DotsPerInch DotsPerInch()
    {
      CoffeeMaker::DotsPerInch dpi;
      SDL_GetDisplayDPI(SDL_GetWindowDisplayIndex(_window), &(dpi.diagonal), &(dpi.horizontal), &(dpi.vertical));
      return dpi;
    }

    float DPIScale()
    {
      return _dpiScale;
    }

  private:
    SDL_Window *_window;
    CoffeeMaker::DotsPerInch _dpi;
    float _dpiScale;
  };
}

#endif