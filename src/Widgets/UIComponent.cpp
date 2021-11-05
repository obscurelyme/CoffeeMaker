#include "Widgets/UIComponent.hpp"

#include "Color.hpp"
#include "Renderer.hpp"

using namespace CoffeeMaker;
using namespace CoffeeMaker::UIProperties;

bool UIComponent::_debugRendering = false;
int UIComponent::_uid = 0;

UIComponent::~UIComponent() {
  _parent = nullptr;
  for (std::shared_ptr<UIComponent> child : _children) {
    child->_parent = nullptr;
  }
  _children.clear();
}

UIComponent::UIComponent() : _parent(nullptr) {
  SDL_RenderGetViewport(Renderer::Instance(), &viewport);
  clientRect.h = viewport.h;
  clientRect.w = viewport.w;
  clientRect.x = viewport.x;
  clientRect.y = viewport.y;
  _xAlign = HorizontalAlignment::Left;
  _yAlign = VerticalAlignment::Top;
  _id = "UIComponent-" + std::to_string(++_uid);
}

UIComponent::UIComponent(const SDL_Rect clientRect) : clientRect(clientRect), _parent(nullptr) {
  SDL_RenderGetViewport(Renderer::Instance(), &viewport);
  _xAlign = HorizontalAlignment::Left;
  _yAlign = VerticalAlignment::Top;
}

void UIComponent::AppendChild(const std::shared_ptr<UIComponent>& component) {
  component->_parent = this;
  component->OnAppend();
  _children.push_back(component);
}

void UIComponent::OnAppend() {
  CalcPosition();
  RepositionChildren();
}

std::string UIComponent::ID() const { return _id; }

void UIComponent::RepositionChildren() {
  for (auto& child : _children) {
    child->OnAppend();
  }
}

void UIComponent::CalcPosition() {
  clientRect.x = UIComponent::DeriveXPosition();
  clientRect.y = UIComponent::DeriveYPosition();
  RepositionChildren();
}

/**
 * Render all children of the component, with the parent as the viewport
 */
void UIComponent::Render() {
  if (_debugRendering) {
    DebugRender();
  }
  // for nested views, this doesn't work. need to fetch the absolute position and
  // then set that position as the viewport.
  // SDL_RenderSetViewport(Renderer::Instance(), &clientRect);
  for (auto i = std::begin(_children); i != std::end(_children); ++i) {
    (*i)->Render();
  }
  // if (_parent == nullptr) {
  //   SDL_RenderSetViewport(Renderer::Instance(), &viewport);
  // }
}

void UIComponent::DebugRender() {
  SDL_Color prevColor;
  SDL_Color borderColor = Color(200, 0, 200, 255);

  SDL_GetRenderDrawColor(Renderer::Instance(), &prevColor.r, &prevColor.g, &prevColor.b, &prevColor.a);
  SDL_SetRenderDrawColor(Renderer::Instance(), borderColor.r, borderColor.g, borderColor.b, borderColor.a);
  SDL_RenderDrawRect(Renderer::Instance(), &clientRect);
  SDL_SetRenderDrawColor(Renderer::Instance(), prevColor.r, prevColor.g, prevColor.b, prevColor.a);
}

void UIComponent::SetHorizontalAlignment(CoffeeMaker::UIProperties::HorizontalAlignment xAlign) {
  _xAlign = xAlign;
  CalcPosition();
}

void UIComponent::SetVerticalAlignment(CoffeeMaker::UIProperties::VerticalAlignment yAlign) {
  _yAlign = yAlign;
  CalcPosition();
}

int UIComponent::DeriveXPosition() {
  SDL_Rect relativeParent = _parent != nullptr ? _parent->clientRect : viewport;

  if (_xAlign == HorizontalAlignment::Centered) {
    return ((relativeParent.w - clientRect.w) / 2) + relativeParent.x;
  } else if (_xAlign == HorizontalAlignment::Right) {
    return (relativeParent.w - clientRect.w) + relativeParent.x;
  } else {
    return 0 + relativeParent.x;
  }
}

int UIComponent::DeriveYPosition() {
  SDL_Rect relativeParent = _parent != nullptr ? _parent->clientRect : viewport;

  if (_yAlign == VerticalAlignment::Centered) {
    return ((relativeParent.h - clientRect.h) / 2) + relativeParent.y;
  } else if (_yAlign == VerticalAlignment::Bottom) {
    return (relativeParent.h - clientRect.h) + relativeParent.y;
  } else {
    return 0 + relativeParent.y;
  }
}

void UIComponent::SetDebugRender(bool toggle) { _debugRendering = toggle; }
