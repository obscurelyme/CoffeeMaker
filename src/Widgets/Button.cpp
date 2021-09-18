#include "Widgets/Button.hpp"
#include <iostream>

using namespace CoffeeMaker;

Button::Button() : top(0), left(0), width(150), height(50), padding(0), _clientRect(), _texture(), _hovered(false) {}

bool Button::_HitDetection(const int &mouseX, const int &mouseY)
{
  return left + width >= mouseX && left <= mouseX && top + height >= mouseY && top <= mouseY;
}

void Button::OnEvent(const SDL_Event *event)
{
  switch (event->type)
  {
  case SDL_MOUSEMOTION:
    int x, y;
    SDL_GetMouseState(&x, &y);
    if (_HitDetection(x, y))
    {
      if (!_hovered)
      {
        OnMouseover();
      }
      break;
    }
    if (_hovered)
    {
      OnMouseleave();
    }
    break;
  case SDL_MOUSEBUTTONDOWN:
    if (_hovered)
    {
      OnClick([]()
              { std::cout << "Button was clicked" << std::endl; });
    }
    break;
  case SDL_MOUSEBUTTONUP:
    break;
  default:
    break;
  }
}

void Button::OnMouseover()
{
  _hovered = true;
  _texture.SetColor(Color(0, 255, 0, 255));
}

void Button::OnMouseleave()
{
  _hovered = false;
  _texture.SetColor(Color(0, 0, 0, 255));
}

void Button::Render()
{
  _texture.Render(top, left, height, width);
}

void Button::OnClick(void (*callback)(void))
{
  callback();
}
