#ifndef _coffeemaker_window_hpp
#define _coffeemaker_window_hpp

#include <SDL2/SDL.h>
#include <fmt/core.h>

#include <string>

namespace CoffeeMaker {
  class ScreenDPI {
    public:
    float diagonal;
    float horizontal;
    float vertical;

    static const int BASE_DPI = 96;

    std::string toString();
  };

  /**
   * Window Interface
   */
  class IWindow {
    public:
    virtual ~IWindow() = default;
    virtual int DisplayCount() const = 0;
    virtual float DPIScale() const = 0;
    virtual ScreenDPI GetScreenDPI() const = 0;
    virtual SDL_DisplayMode DisplayMode() const = 0;
    virtual std::string DisplayName() const = 0;
    virtual Uint32 PixelFormat() const = 0;
    virtual std::string PixelFormatName() const = 0;
    virtual SDL_Rect DisplayBounds() const = 0;
    virtual SDL_Rect DisplayUsableBounds() const = 0;
    virtual SDL_Window *Handle() const = 0;

    private:
    virtual ScreenDPI SetScreenDPI() = 0;
  };

  class BasicWindow : public IWindow {
    public:
    BasicWindow(std::string title, int width, int height);
    ~BasicWindow();

    int DisplayCount() const override;
    float DPIScale() const override;
    ScreenDPI GetScreenDPI() const override;
    SDL_DisplayMode DisplayMode() const override;
    std::string DisplayName() const override;
    Uint32 PixelFormat() const override;
    std::string PixelFormatName() const override;
    SDL_Rect DisplayBounds() const override;
    SDL_Rect DisplayUsableBounds() const override;
    SDL_Window *Handle() const override;
    void ShowWindow() const;

    private:
    ScreenDPI SetScreenDPI() override;
    static SDL_Window *_window;
    CoffeeMaker::ScreenDPI _screenDpi;
    float _dpiScale;
  };

  /**
   * Static class to work with instances of a window object.
   */
  class GlobalWindow {
    public:
    static IWindow *Instance();
    static void Set(IWindow *win);
    static void Unset();

    private:
    GlobalWindow();
    explicit GlobalWindow(IWindow *win);
    static IWindow *_instance;
  };
}  // namespace CoffeeMaker

#endif
