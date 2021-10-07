#include "Widgets/Button.hpp"

#include <algorithm>
#include <functional>
#include <iostream>

#include "Logger.hpp"

using namespace CoffeeMaker;

std::map<std::string, Button *> Button::buttons = {};
std::queue<Event *> Button::eventQueue;
int Button::_buttonUid = 0;

Delegate *createButtonDelegate(std::function<void(const Event &event)> fn) { return new Delegate(fn); }

Button::Button() : top(0), left(0), width(150), height(50), padding(0), _texture(), _hovered(false) {
  clientRect.h = height;
  clientRect.w = width;
  clientRect.x = left;
  clientRect.y = top;
  _EmplaceButton();
  _AttachDefaultEvents();
}

Button::Button(const ButtonProperties &props) : top(0), left(0) {
  if (props.type == ButtonPropsType::TextureBased) {
    _defaultTexture = props.textureProps.defaultTexture;
    _hoveredTexture = props.textureProps.hoveredTexture;
  } else {
    _defaultColor = props.colorProps.defaultColor;
    _hoveredColor = props.colorProps.hoveredColor;
  }
  clientRect.h = props.height;
  clientRect.w = props.width;
  _EmplaceButton();
  _AttachDefaultEvents();
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

void Button::SetTexture(const Texture &texture) {
  _texture = texture;
  _textureColorMod = _texture.GetColorMod();
}

void Button::SetTexture(const std::string &filePath) {
  _texture.LoadFromFile(filePath);
  _textureColorMod = _texture.GetColorMod();
}

void Button::SetWidth(Uint32 width) {
  clientRect.w = width;
  CalcPosition();
}

void Button::SetHeight(Uint32 height) {
  clientRect.h = height;
  CalcPosition();
}

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

void Button::OnMouseover() {
  _hovered = true;
  _texture.SetColor(Color(0, 50, 0, 255));
}

void Button::OnMouseleave() {
  _hovered = false;
  _texture.SetColor(_textureColorMod);
}

void Button::Render() {
  clientRect.x = UIComponent::DeriveXPosition();
  clientRect.y = UIComponent::DeriveYPosition();
  _texture.Render(clientRect.y, clientRect.x, clientRect.h, clientRect.w);
  UIComponent::Render();
}

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

void Button::_EmplaceButton() {
  _componentId = "CoffeeMaker::Widget::Button-" + std::to_string(++_buttonUid);
  buttons.emplace(_componentId, this);
}

void Button::_AttachDefaultEvents() {
  _events.emplace(ButtonEventType::MouseMotion, new Event());
  _events.emplace(ButtonEventType::MouseDown, new Event());
  _events.emplace(ButtonEventType::MouseUp, new Event());

  On(ButtonEventType::MouseMotion, Delegate{std::bind(&Button::OnMouseMotion, this, std::placeholders::_1)});
  On(ButtonEventType::MouseDown, Delegate{std::bind(&Button::OnMouseDown, this, std::placeholders::_1)});
  On(ButtonEventType::MouseUp, Delegate{std::bind(&Button::OnMouseUp, this, std::placeholders::_1)});
}
