#ifndef _coffeemaker_window_hpp
#define _coffeemaker_window_hpp

#include <SDL2/SDL.h>
#include <string>
#include <fmt/core.h>

namespace CoffeeMaker
{
  class ScreenDPI
  {
  public:
    float diagonal;
    float horizontal;
    float vertical;

    static const int BASE_DPI = 96;

    std::string toString();
  };

  /**
   * Base window class from which other windows may inherit from
   */
  class Window
  {
  public:
    Window(std::string title, int width, int height);
    ~Window();

    static SDL_Window * Instance();
    /**
     * Explicitly calls the destructor
     */
    void Destroy();

    int DisplayCount();

    CoffeeMaker::ScreenDPI DotsPerInch();

    float DPIScale();
    SDL_Surface *Surface();

  private:
    static SDL_Window *_window;
    CoffeeMaker::ScreenDPI _dpi;
    float _dpiScale;
  };
}

#endif
