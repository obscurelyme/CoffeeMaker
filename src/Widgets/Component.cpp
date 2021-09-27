#include "Widgets/Component.hpp"

#include "Renderer.hpp"

using namespace CoffeeMaker;

Component::Component() : _parent(nullptr) {
  SDL_RenderGetViewport(Renderer::Instance(), &viewport);
  clientRect.h = viewport.h;
  clientRect.w = viewport.w;
  clientRect.x = viewport.x;
  clientRect.y = viewport.y;
}

Component::Component(const SDL_Rect clientRect) : clientRect(clientRect) {
  SDL_RenderGetViewport(Renderer::Instance(), &viewport);
}

void Component::AppendChild(Component* const component) {
  component->_parent = this;
  _children.push_back(component);
}

/**
 * Render all children of the component
 */
void Component::Render() {
  SDL_RenderSetViewport(Renderer::Instance(), &clientRect);
  for (auto i = std::begin(_children); i != std::end(_children); ++i) {
    (*i)->Render();
  }
  if (_parent == nullptr) {
    SDL_RenderSetViewport(Renderer::Instance(), &viewport);
  }
}
