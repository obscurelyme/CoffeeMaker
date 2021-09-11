#ifndef _coffeemaker_renderer_hpp
#define _coffeemaker_renderer_hpp

#include <SDL2/SDL.h>
#include "Window.hpp"

namespace CoffeeMaker
{

  class Renderer
  {
  public:
    Renderer(CoffeeMaker::Window *window) : _window(window)
    {
      _renderer = SDL_CreateRenderer(window->instance(), -1, 0);
    }

    SDL_Renderer *Instance()
    {
      return _renderer;
    }

    void Render()
    {
      SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
      SDL_RenderClear(_renderer);

      // TODO More rendering...

      SDL_RenderPresent(_renderer);
    }

    void BeginRender()
    {
      SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
      SDL_RenderClear(_renderer);
    }

    void EndRender()
    {
      SDL_RenderPresent(_renderer);
    }

    void Destroy()
    {
      SDL_DestroyRenderer(_renderer);
    }

  private:
    CoffeeMaker::Window *_window;
    SDL_Renderer *_renderer;
  };

} // namespace CoffeeMaker

#endif