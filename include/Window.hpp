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
    virtual Uint32 GetID() const = 0;

    private:
    virtual ScreenDPI SetScreenDPI() = 0;
  };

  class UtilityWindow {
    public:
    UtilityWindow();
    ~UtilityWindow();

    int DisplayHeight() const;
    int DisplayWidth() const;

    private:
    SDL_Window *_handle;
    SDL_Rect _usableDisplayBounds;
    SDL_Rect _displayBounds;

    static std::string title;
    static int width;
    static int height;
  };

  class BasicWindow : public IWindow {
    public:
    BasicWindow(std::string title, int width, int height, bool fullscreen, bool hdpi);
    ~BasicWindow();

    int DisplayCount() const;
    float DPIScale() const;
    ScreenDPI GetScreenDPI() const;
    SDL_DisplayMode DisplayMode() const;
    std::string DisplayName() const;
    Uint32 PixelFormat() const;
    std::string PixelFormatName() const;
    SDL_Rect DisplayBounds() const;
    SDL_Rect DisplayUsableBounds() const;
    SDL_Window *Handle() const;
    void ShowWindow() const;
    Uint32 GetID() const;
    bool HighDPIMode() const;

    private:
    ScreenDPI SetScreenDPI();
    static SDL_Window *_window;
    CoffeeMaker::ScreenDPI _screenDpi;
    float _dpiScale;
    SDL_Rect _screenBounds;
    SDL_Rect _usableDisplayBounds;
    bool _highDpiMode;
  };

  /**
   * Static class to work with instances of a window object.
   */
  class GlobalWindow {
    public:
    static IWindow *Instance();
    static void Set(IWindow *win);
    static void Unset();
    static Uint32 ID();

    private:
    GlobalWindow();
    GlobalWindow(IWindow *win);
    static IWindow *_instance;
  };
}  // namespace CoffeeMaker

#endif
