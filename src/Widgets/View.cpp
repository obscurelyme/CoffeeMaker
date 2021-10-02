#include "Widgets/View.hpp"

#include "Renderer.hpp"

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

void View::Render() { UIComponent::Render(); }
