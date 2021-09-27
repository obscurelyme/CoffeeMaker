#include "Widgets/UIComponent.hpp"

#include "Color.hpp"
#include "Renderer.hpp"

using namespace CoffeeMaker;
using namespace CoffeeMaker::UIProperties;

bool UIComponent::_debugRendering = true;

UIComponent::UIComponent() : _parent(nullptr) {
  SDL_RenderGetViewport(Renderer::Instance(), &viewport);
  clientRect.h = viewport.h;
  clientRect.w = viewport.w;
  clientRect.x = viewport.x;
  clientRect.y = viewport.y;
  _xAlign = HorizontalAlignment::Left;
  _yAlign = VerticalAlignment::Top;
}

UIComponent::UIComponent(const SDL_Rect clientRect) : clientRect(clientRect), _parent(nullptr) {
  SDL_RenderGetViewport(Renderer::Instance(), &viewport);
  _xAlign = HorizontalAlignment::Left;
  _yAlign = VerticalAlignment::Top;
}

void UIComponent::AppendChild(UIComponent* const component) {
  component->_parent = this;
  _children.push_back(component);
}

/**
 * Render all children of the component, with the parent as the viewport
 */
void UIComponent::Render() {
  if (_debugRendering) {
    DebugRender();
  }
  SDL_RenderSetViewport(Renderer::Instance(), &clientRect);
  for (auto i = std::begin(_children); i != std::end(_children); ++i) {
    (*i)->Render();
  }
  if (_parent == nullptr) {
    SDL_RenderSetViewport(Renderer::Instance(), &viewport);
  }
}

void UIComponent::DebugRender() {
  SDL_Color prevColor;
  SDL_Color borderColor = Color(200, 0, 200, 255);

  SDL_GetRenderDrawColor(Renderer::Instance(), &prevColor.r, &prevColor.g, &prevColor.b, &prevColor.a);
  SDL_SetRenderDrawColor(Renderer::Instance(), borderColor.r, borderColor.g, borderColor.b, borderColor.a);
  SDL_RenderDrawRect(Renderer::Instance(), &clientRect);
  SDL_SetRenderDrawColor(Renderer::Instance(), prevColor.r, prevColor.g, prevColor.b, prevColor.a);
}

void UIComponent::SetHorizontalAlignment(CoffeeMaker::UIProperties::HorizontalAlignment xAlign) { _xAlign = xAlign; }

void UIComponent::SetVerticalAlignment(CoffeeMaker::UIProperties::VerticalAlignment yAlign) { _yAlign = yAlign; }

int UIComponent::DeriveXPosition() {
  SDL_Rect currentViewport;
  SDL_RenderGetViewport(Renderer::Instance(), &currentViewport);

  if (_xAlign == HorizontalAlignment::Centered) {
    return (currentViewport.w - clientRect.w) / 2;
  } else if (_xAlign == HorizontalAlignment::Right) {
    return (currentViewport.w - clientRect.w);
  } else {
    return 0;
  }
}

int UIComponent::DeriveYPosition() {
  SDL_Rect currentViewport;
  SDL_RenderGetViewport(Renderer::Instance(), &currentViewport);

  if (_yAlign == VerticalAlignment::Centered) {
    return (currentViewport.h - clientRect.h) / 2;
  } else if (_yAlign == VerticalAlignment::Bottom) {
    return (currentViewport.h - clientRect.h);
  } else {
    return 0;
  }
}

void UIComponent::SetDebugRender(bool toggle) { _debugRendering = toggle; }
