#include "Widgets/Component.hpp"
#include "Renderer.hpp"

using namespace CoffeeMaker;

Component::Component() : _parent(nullptr)
{
  SDL_RenderGetViewport(Renderer::Instance(), &viewport);
  clientRect.h = viewport.h;
  clientRect.w = viewport.w;
  clientRect.x = viewport.x;
  clientRect.y = viewport.y;
}

Component::Component(const SDL_Rect clientRect) : clientRect(clientRect)
{
  SDL_RenderGetViewport(Renderer::Instance(), &viewport);
}

void Component::AppendChild(Component *component)
{
  component->_parent = this;
  _children.push_back(component);
}
