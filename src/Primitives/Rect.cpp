#include "Primitives/Rect.hpp"
#include "Renderer.hpp"

using namespace CoffeeMaker::Shapes;

Rect::Rect() : Rect(0, 0, 0, 0) {}

Rect::Rect(int height, int width) : Rect(height, width, 0, 0) {}

Rect::Rect(int height, int width, int top, int left) : color(Color())
{
  clientRect.h = height;
  clientRect.w = width;
  clientRect.x = top;
  clientRect.y = left;
}

int Rect::Height()
{
  return clientRect.h;
}

int Rect::Width()
{
  return clientRect.w;
}

int Rect::Top()
{
  return clientRect.y;
}

int Rect::Left()
{
  return clientRect.x;
}

void Rect::Render()
{
  SDL_SetRenderDrawColor(CoffeeMaker::Renderer::Instance(), color.r, color.g, color.b, color.a);
  SDL_RenderFillRect(CoffeeMaker::Renderer::Instance(), &clientRect);
}