#include "Widgets/View.hpp"

#include "Renderer.hpp"

using namespace CoffeeMaker::Widgets;
using namespace CoffeeMaker::UIProperties;

View::View(int width, int height, HorizontalAlignment xAlign, VerticalAlignment yAlign, int spacing) :
    spacing(spacing) {
  UIComponent::_xAlign = xAlign;
  UIComponent::_yAlign = yAlign;
  clientRect.h = height;
  clientRect.w = width;
  clientRect.x = UIComponent::DeriveXPosition();
  clientRect.y = UIComponent::DeriveYPosition();
}

void View::Render() {
  // SDL_Color c{.r = 200, .g = 0, .b = 200, .a = 255};
  // SDL_SetRenderDrawColor(Renderer::Instance(), c.r, c.g, c.b, c.a);
  // SDL_RenderDrawRect(Renderer::Instance(), &clientRect);
  UIComponent::Render();
}
