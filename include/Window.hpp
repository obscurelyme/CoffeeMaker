#ifndef _coffeemaker_window_hpp
#define _coffeemaker_window_hpp

#include <SDL2/SDL.h>
#include <string>
#include <fmt/core.h>

namespace CoffeeMaker
{
  /**
   * Window Interface
   */
  class IWindow
  {
    public:
      virtual ~IWindow() = default;
      virtual int DisplayCount() = 0;
      virtual float DPIScale() = 0;
      virtual SDL_DisplayMode DisplayMode() = 0;
      virtual std::string DisplayName() = 0;
      virtual std::string PixelFormatName(Uint32 format) = 0;
      virtual int DisplayBounds() = 0;
      virtual int DisplayUsableBounds() = 0;
      virtual SDL_Window* Handle() = 0;
  };

  /**
   * Static class to work with instances of a window object.
   */
  class GlobalWindow
  {
    public:
      static IWindow * Instance();

      GlobalWindow(IWindow* win);

    private:
      static IWindow* _instance;
  };

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
  class Window : public IWindow
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
