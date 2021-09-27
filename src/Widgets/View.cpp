#include "Widgets/View.hpp"
#include "Renderer.hpp"

using namespace CoffeeMaker::Widgets;

View::View(int width, int height, ViewXProps xProps, ViewYProps yProps, int spacing):
  spacing(spacing), _xProps(xProps), _yProps(yProps) {
    clientRect.h = height;
    clientRect.w = width;
    clientRect.x = _DerivedXPosition();
    clientRect.y = _DerivedYPosition();
  }


int View::_DerivedXPosition() {
  if (_xProps == ViewXProps::CENTERED) {
    return (viewport.w - clientRect.w) / 2;
  } else if (_xProps == ViewXProps::RIGHT_ALIGNED) {
    return (viewport.w - clientRect.w);
  } else {
    return 0;
  }
}

int View::_DerivedYPosition() {
  if (_yProps == ViewYProps::CENTERED) {
    return (viewport.h - clientRect.h) / 2;
  } else if (_yProps == ViewYProps::BOTTOM_ALIGNED) {
    return (viewport.h - clientRect.h);
  } else {
    return 0;
  }
}

void View::Render() {
  SDL_Color c{ .r = 200, .g = 0, .b = 200, .a = 255 };
  SDL_SetRenderDrawColor(Renderer::Instance(), c.r, c.g, c.b, c.a);
  SDL_RenderDrawRect(Renderer::Instance(), &clientRect);
  Component::Render();
}
