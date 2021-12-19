#include "Game/Tiles.hpp"

#include <cmath>

#include "Logger.hpp"
#include "Renderer.hpp"

Tiles::Tiles() : _scrollSpeed(300.0f), _movement(0), _xOffset(0), _yOffset(0) {}

Tiles::Tiles(const std::string& filePath, int viewportWidth, int viewportHeight) :
    _viewportWidth(viewportWidth),
    _viewportHeight(viewportHeight),
    _scrollSpeed(300.0f * CoffeeMaker::Renderer::DynamicResolutionDownScale()),
    _movement(0),
    _direction(Tiles::ScrollDirection::Vertical),
    _xOffset(0),
    _yOffset(0) {
  _texture.LoadFromFile(filePath);
  _texture.SetWidth(_texture.Width());
  _texture.SetHeight(_texture.Height());
}

Tiles::Tiles(const std::string& filePath, int viewportWidth, int viewportHeight, float speed) :
    _viewportWidth(viewportWidth),
    _viewportHeight(viewportHeight),
    _scrollSpeed(speed * CoffeeMaker::Renderer::DynamicResolutionDownScale()),
    _movement(0),
    _direction(Tiles::ScrollDirection::Vertical),
    _xOffset(0),
    _yOffset(0) {
  _texture.LoadFromFile(filePath);
  _texture.SetWidth(_texture.Width());
  _texture.SetHeight(_texture.Height());
}

Tiles::Tiles(const std::string& filePath, int viewportWidth, int viewportHeight, float speed,
             Tiles::ScrollDirection direction) :
    _viewportWidth(viewportWidth),
    _viewportHeight(viewportHeight),
    _scrollSpeed(speed * CoffeeMaker::Renderer::DynamicResolutionDownScale()),
    _movement(0),
    _direction(direction) {
  _texture.LoadFromFile(filePath);
  _texture.SetWidth(_texture.Width());
  _texture.SetHeight(_texture.Height());
}

void Tiles::Update(float deltaTime) { _movement += deltaTime * _scrollSpeed; }

void Tiles::Render() {
  if (_direction == ScrollDirection::Vertical) {
    const int widthCount = _viewportWidth / _texture.Width();
    const int heightCount = _viewportHeight / _texture.Height() + 1;

    for (int i = 0; i <= widthCount; i++) {
      for (int j = 0; j <= heightCount; j++) {
        float yPos = (j * _texture.Height()) - _texture.Height() + _movement;
        float xPos = (float)i * _texture.Width();

        if (j == 0 && yPos >= 0) {
          _movement = 0;  // NOTE: reset the position for infinite loop effect
          yPos = heightCount * _texture.Height() - yPos;
          CM_LOGGER_DEBUG("Reset Vertical Position: ({},{})", xPos, yPos);
        }

        _texture.Render(yPos, xPos);
      }
    }
    return;
  }

  const int widthCount = std::ceil((float)_viewportWidth / (float)_texture.Width()) + 1;
  const int heightCount = std::ceil((float)_viewportHeight / (float)_texture.Height()) + 1;

  for (int i = 0; i <= widthCount; i++) {
    for (int j = 0; j <= heightCount; j++) {
      float yPos = (float)j * _texture.Height();
      float xPos = (i * _texture.Width()) - _texture.Width() + _movement;

      if (i == 0 && xPos >= 0) {
        _movement = 0;  // NOTE: reset the position for infinite loop effect
        xPos = widthCount * _texture.Width() - xPos;
        CM_LOGGER_DEBUG("Reset Horizontal Position: ({},{})", xPos, yPos);
      }

      _texture.Render(yPos, xPos);
    }
  }
}

void Tiles::SetXOffset(float x) { _xOffset = x; }

void Tiles::SetYOffset(float y) { _yOffset = y; }

void Tiles::PinToBottom() {}
