#include "Widgets/Button.hpp"

#include <algorithm>
#include <functional>
#include <iostream>

#include "Logger.hpp"

using namespace CoffeeMaker;

std::map<std::string, Button *> Button::buttons = {};
std::queue<std::function<void()>> Button::onClickCallbacks;
std::queue<Event *> Button::eventQueue;
int Button::_buttonUid = 0;

Button::Button() : top(0), left(0), width(150), height(50), padding(0), _texture(), _hovered(false) {
  clientRect.h = height;
  clientRect.w = width;
  clientRect.x = left;
  clientRect.y = top;
  _componentId = "CoffeeMaker::Widget::Button-" + std::to_string(++_buttonUid);
  buttons.emplace(_componentId, this);

  // Add default events
  _events.emplace(ButtonEventType::MouseMotion, new Event());
  _events.emplace(ButtonEventType::MouseDown, new Event());
  _events.emplace(ButtonEventType::MouseUp, new Event());

  On(ButtonEventType::MouseMotion, Delegate{std::bind(&Button::OnMouseMotion, this, std::placeholders::_1)});
  On(ButtonEventType::MouseDown, Delegate{std::bind(&Button::OnMouseDown, this, std::placeholders::_1)});
  On(ButtonEventType::MouseUp, Delegate{std::bind(&Button::OnMouseUp, this, std::placeholders::_1)});
}

Button::~Button() {
  CM_LOGGER_INFO("{} is being deleted", _componentId);
  for (auto it = buttons.begin(); it != buttons.end();) {
    if (it->first == _componentId) {
      it = buttons.erase(it);
    } else {
      ++it;
    }
  }
  for (auto e : _events) {
    e.second->RemoveAllListeners();
    delete e.second;
    e.second = nullptr;
  }
}

void Button::SetBackgroundColor(const SDL_Color &color) { _texture.SetColor(color); }

void Button::SetTexture(const Texture &texture) { _texture = texture; }

void Button::SetTexture(const std::string &filePath) { _texture.LoadFromFile(filePath); }

bool Button::_HitDetection(const int &mouseX, const int &mouseY) {
  return clientRect.x + clientRect.w >= mouseX && clientRect.x <= mouseX && clientRect.y + clientRect.h >= mouseY &&
         clientRect.y <= mouseY;
}

void Button::OnMouseUp(const Event &) {
  // noop
}

void Button::OnMouseDown(const Event &) {
  if (_hovered) {
    auto clickEvent = _events.find(ButtonEventType::OnClick);
    if (clickEvent != _events.end()) {
      eventQueue.push(clickEvent->second);
    }
  }
}

void Button::OnMouseMotion(const Event &) {
  int x, y;
  SDL_GetMouseState(&x, &y);
  if (_HitDetection(x, y)) {
    if (!_hovered) {
      OnMouseover();
    }
    return;
  }
  if (_hovered) {
    OnMouseleave();
  }
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

void Button::PollEvents(const SDL_Event *const event) {
  for (auto &button : CoffeeMaker::Button::buttons) {
    auto &btnEvents = button.second->_events;
    auto search = button.second->_events.find((ButtonEventType)event->type);
    if (search != btnEvents.end()) {
      eventQueue.push(search->second);
    }
  }
}

/**
 * Process the Button Event[s] at a separate stage within the run loop
 */
void Button::ProcessEvents() {
  while (!eventQueue.empty()) {
    auto e = eventQueue.front();
    eventQueue.pop();
    e->Emit();
  }
}
