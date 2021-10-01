#include "Widgets/Button.hpp"

#include <algorithm>
#include <iostream>

using namespace CoffeeMaker;

std::map<std::string, Button *> Button::buttons = {};
std::queue<std::function<void()>> Button::onClickCallbacks;

Button::Button() : top(0), left(0), width(150), height(50), padding(0), _texture(), _hovered(false) {
  clientRect.h = height;
  clientRect.w = width;
  clientRect.x = left;
  clientRect.y = top;
  _id = "Button-" + _id;
  buttons.emplace(_id, this);
}

Button::~Button() {
  for (auto it = buttons.begin(); it != buttons.end();) {
    if (it->first == _id) {
      it = buttons.erase(it);
    } else {
      ++it;
    }
  }
}

bool Button::_HitDetection(const int &mouseX, const int &mouseY) {
  return clientRect.x + clientRect.w >= mouseX && clientRect.x <= mouseX && clientRect.y + clientRect.h >= mouseY &&
         clientRect.y <= mouseY;
}

void Button::OnEvent(const SDL_Event *event) {
  switch (event->type) {
    case SDL_MOUSEMOTION:
      int x, y;
      SDL_GetMouseState(&x, &y);
      if (_HitDetection(x, y)) {
        if (!_hovered) {
          OnMouseover();
        }
        break;
      }
      if (_hovered) {
        OnMouseleave();
      }
      break;
    case SDL_MOUSEBUTTONDOWN:
      if (_hovered) {
        OnClick();
      }
      break;
    case SDL_MOUSEBUTTONUP:
      break;
    case SDL_KEYDOWN:
      switch (event->key.keysym.sym) {
        case SDLK_UP:
          clientRect.y -= 5;
          break;
        case SDLK_DOWN:
          clientRect.y += 5;
          break;
        case SDLK_LEFT:
          clientRect.x -= 5;
          break;
        case SDLK_RIGHT:
          clientRect.x += 5;
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}

void Button::OnMouseover() {
  _hovered = true;
  _texture.SetColor(Color(0, 255, 0, 255));
}

void Button::OnMouseleave() {
  _hovered = false;
  _texture.SetColor(Color(0, 0, 0, 255));
}

void Button::Render() {
  clientRect.x = UIComponent::DeriveXPosition();
  clientRect.y = UIComponent::DeriveYPosition();
  _texture.Render(clientRect.y, clientRect.x, clientRect.h, clientRect.w);
  UIComponent::Render();
}

void Button::OnClick() { onClickCallbacks.push(onClickCallback); }

/**
 * Process the onClick callbacks at a separate stage within the run loop
 */
void Button::ProcessEvents() {
  while (!onClickCallbacks.empty()) {
    auto callback = onClickCallbacks.front();
    onClickCallbacks.pop();
    callback();
  }
}
