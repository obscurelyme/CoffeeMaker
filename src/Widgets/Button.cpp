#include "Widgets/Button.hpp"

using namespace CoffeeMaker;

Button::Button() : top(0), left(0), width(150), height(50), padding(0), _clientRect(), _texture() {}

void Button::OnMouseover()
{
  _texture.SetColor(Color(0, 255, 0, 255));
}

void Button::OnMouseleave()
{
  _texture.SetColor(Color(0, 0, 0, 255));
}

void Button::Render()
{
  _texture.Render(top, left, height, width);
}
