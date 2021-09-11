#ifndef _coffeemaker_window_hpp
#define _coffeemaker_window_hpp

#include <SDL2/SDL.h>
#include <string>

namespace CoffeeMaker
{
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

  private:
    SDL_Window *_window;
  };
}

#endif