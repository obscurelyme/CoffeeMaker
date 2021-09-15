#include "Primitives/Line.hpp"
#include "Color.hpp"
#include "Renderer.hpp"

// _USE_MATH_DEFINES is defined so we get access to PI constants
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#include <math.h>
#endif

using namespace CoffeeMaker::Shapes;

Line::Line() : color(Color()) {}

Line::Line(int length, int top, int left, float angle) : angleDegrees(angle), top(top), left(left), length(length), color(Color())
{
  angleRadians = angleDegrees * (float)(M_PI / 180);
  // Parametric Form, truncated to int
  endX = (int)(left + length * cos(angleRadians));
  endY = (int)(top + length * sin(angleRadians));
}

Line::~Line() {}

void Line::Render()
{
  SDL_SetRenderDrawColor(CoffeeMaker::Renderer::Instance(), color.r, color.g, color.b, color.a);
  SDL_RenderDrawLine(CoffeeMaker::Renderer::Instance(), left, top, endX, endY);
}

void Line::Rotate(float angle)
{
  angleDegrees += angle;
  angleRadians = angleDegrees * (float)(M_PI / 180);
  // Parametric Form, truncated to int
  endX = (int)(left + length * cos(angleRadians));
  endY = (int)(top + length * sin(angleRadians));
}
