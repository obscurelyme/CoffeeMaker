#include "Widgets/View.hpp"

#include "Renderer.hpp"
#include "Window.hpp"

using namespace CoffeeMaker::Widgets;
using namespace CoffeeMaker::UIProperties;

View::View() {
  UIComponent::_xAlign = HorizontalAlignment::Left;
  UIComponent::_yAlign = VerticalAlignment::Top;
  clientRect.h = 0;
  clientRect.w = 0;
  clientRect.x = UIComponent::DeriveXPosition();
  clientRect.y = UIComponent::DeriveYPosition();
}

View::View(int width, int height, HorizontalAlignment xAlign, VerticalAlignment yAlign, int spacing) :
    spacing(spacing) {
  UIComponent::_xAlign = xAlign;
  UIComponent::_yAlign = yAlign;
  clientRect.h = height;
  clientRect.w = width;
  clientRect.x = UIComponent::DeriveXPosition();
  clientRect.y = UIComponent::DeriveYPosition();
}

View::View(float widthPercent, float heightPercent, HorizontalAlignment xAlign, VerticalAlignment yAlign, int spacing) :
    spacing(spacing) {
  // floats need to be between 0.0f and 1.0f
  if (widthPercent < 0.0f || widthPercent > 1.0f || heightPercent < 0.0f || heightPercent > 1.0f) {
    // problem
  }
  UIComponent::_xAlign = xAlign;
  UIComponent::_yAlign = yAlign;
  clientRect.w = (int)(widthPercent * Renderer::GetOutputWidth());
  clientRect.h = (int)(heightPercent * Renderer::GetOutputHeight());
  clientRect.x = UIComponent::DeriveXPosition();
  clientRect.y = UIComponent::DeriveYPosition();
}

View::View(float widthPercent, int height, HorizontalAlignment xAlign, VerticalAlignment yAlign, int spacing) :
    spacing(spacing) {
  if (widthPercent < 0.0f || widthPercent > 1.0f) {
    // problem
  }
  UIComponent::_xAlign = xAlign;
  UIComponent::_yAlign = yAlign;
  clientRect.w = (int)(widthPercent * Renderer::GetOutputWidth());
  clientRect.h = height;
  clientRect.x = UIComponent::DeriveXPosition();
  clientRect.y = UIComponent::DeriveYPosition();
}

View::View(int width, float heightPercent, HorizontalAlignment xAlign, VerticalAlignment yAlign, int spacing) :
    spacing(spacing) {
  if (heightPercent < 0.0f || heightPercent > 1.0f) {
    // problem
  }
  UIComponent::_xAlign = xAlign;
  UIComponent::_yAlign = yAlign;
  clientRect.w = width;
  clientRect.h = (int)(heightPercent * Renderer::GetOutputHeight());
  clientRect.x = UIComponent::DeriveXPosition();
  clientRect.y = UIComponent::DeriveYPosition();
}

void View::Render() { UIComponent::Render(); }
