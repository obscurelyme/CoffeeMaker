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
    /**
     * @brief Returns the entire available render height. Scales accordingly to High DPI modes
     *
     * @return int
     */
    static int GetOutputHeight();
    /**
     * @brief Returns the entire available render width. Scales accordingly to High DPI modes
     *
     * @return int
     */
    static int GetOutputWidth();

    /**
     * @brief Return a scaler based on Renderer Output Width size starting with 1.0f as 800px width
     *
     * @return float
     */
    static float DynamicResolutionUpScale() { return GetOutputWidth() / 1792.0f; };

    static float DynamicResolutionDownScale() { return GetOutputWidth() / 1792.0f; };

    private:
    static SDL_Renderer *_renderer;
    static Uint32 _numDrawCalls;
    static int _width;
    static int _height;
  };

  class GlobalRenderer {
    public:
    IRenderer *Instance();

    private:
    GlobalRenderer();
  };

}  // namespace CoffeeMaker

#endif
