#ifndef _coffeemaker_component_hpp
#define _coffeemaker_component_hpp

#include <SDL2/SDL.h>
#include <vector>

namespace CoffeeMaker
{
  class Component
  {
  public:
    Component();
    Component(const SDL_Rect clientRect);
    ~Component() = default;

    void AppendChild(Component *component);
    virtual void Render() = 0;

    SDL_Rect viewport;
    SDL_Rect clientRect;

  protected:
    std::vector<Component *> _children;
    Component *_parent;
  };
}

#endif
