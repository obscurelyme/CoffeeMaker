#ifndef _coffeemaker_renderer_hpp
#define _coffeemaker_renderer_hpp

#include <SDL2/SDL.h>

#include "Window.hpp"

namespace CoffeeMaker {
  class IRenderer {
    public:
    virtual ~IRenderer() = default;
    virtual SDL_Renderer *Instance() = 0;
  };

  class Renderer {
    public:
    Renderer();
    ~Renderer();

    static SDL_Renderer *Instance();
    void Render();
    void BeginRender();
    void EndRender();
    void Destroy();
    static bool Exists();
    /**
     * @brief The number of draw calls that happened so far
     * in the current frame.
     *
     * @return int
     */
    static Uint32 DrawCalls();
    static void IncDrawCalls();

    private:
    static SDL_Renderer *_renderer;
    static Uint32 _numDrawCalls;
  };

  class GlobalRenderer {
    public:
    IRenderer *Instance();

    private:
    GlobalRenderer();
  };

}  // namespace CoffeeMaker

#endif
