#include "Widgets/Button.hpp"

#include <algorithm>
#include <functional>
#include <iostream>

#include "Logger.hpp"
#include "Renderer.hpp"

using namespace CoffeeMaker;

std::map<std::string, Button *> Button::buttons = {};
std::queue<Event *> Button::eventQueue;
int Button::_buttonUid = 0;
std::map<std::string, Ref<Texture>> Button::_cachedTextures = {};

Delegate *createButtonDelegate(std::function<void(const Event &event)> fn) { return new Delegate(fn); }

Button::Button() : _currentTexture(nullptr), _defaultTexture(nullptr), _hoveredTexture(nullptr), _hovered(false) {
  _type = ButtonType::Standard;
  clientRect.h = 50;
  clientRect.w = 100;
  clientRect.x = 0;
  clientRect.y = 0;
  _EmplaceButton();
  _AttachDefaultEvents();
}

Button::Button(const SDL_Color &defaultColor, const SDL_Color &hoveredColor, Uint32 width, Uint32 height) :
    _defaultTexture(nullptr),
    _hoveredTexture(nullptr),
    _defaultColor(defaultColor),
    _hoveredColor(hoveredColor),
    _hovered(false) {
  _type = ButtonType::Standard;
  clientRect.h = height;
  clientRect.w = width;
  _EmplaceButton();
  _AttachDefaultEvents();
}

Button::Button(const std::string &defaultTexture, const std::string &hoveredTexture) : _hovered(false) {
  _type = ButtonType::Textured;

  auto it = _cachedTextures.find(defaultTexture);
  if (it == _cachedTextures.end()) {
    _defaultTexture = std::make_shared<Texture>(defaultTexture);
    _cachedTextures.emplace(defaultTexture, _defaultTexture);
  } else {
    _defaultTexture = it->second;
  }

  auto it2 = _cachedTextures.find(hoveredTexture);
  if (it2 == _cachedTextures.end()) {
    _hoveredTexture = std::make_shared<Texture>(hoveredTexture);
    _cachedTextures.emplace(hoveredTexture, _hoveredTexture);
  } else {
    _hoveredTexture = it2->second;
  }

  _currentTexture = _defaultTexture;
  clientRect.h = _currentTexture->Height();
  clientRect.w = _currentTexture->Width();
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
  _currentColor = _hoveredColor;
  _currentTexture = _hoveredTexture;
}

void Button::OnMouseleave() {
  _hovered = false;
  _currentColor = _defaultColor;
  _currentTexture = _defaultTexture;
}

void Button::Render() {
  if (_type == ButtonType::Textured) {
    _currentTexture->Render(clientRect.y, clientRect.x, clientRect.h, clientRect.w);
  } else {
    SDL_SetRenderDrawColor(CoffeeMaker::Renderer::Instance(), _currentColor.r, _currentColor.g, _currentColor.b,
                           _currentColor.a);
    SDL_RenderFillRect(CoffeeMaker::Renderer::Instance(), &clientRect);
    CoffeeMaker::Renderer::IncDrawCalls();
  }
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

std::string Button::ID() const { return _componentId; }
