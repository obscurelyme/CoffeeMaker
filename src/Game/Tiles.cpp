#include "Game/Tiles.hpp"

#include <cmath>

#include "Logger.hpp"
#include "Renderer.hpp"

Tiles::Tiles() :
    _widthCount(0), _heightCount(0), _scrollSpeed(300.0f), _movement(0.0f), _xOffset(0.0f), _yOffset(0.0f) {}

Tiles::Tiles(const std::string& filePath, int viewportWidth, int viewportHeight) :
    _viewportWidth(viewportWidth),
    _viewportHeight(viewportHeight),
    _widthCount(0),
    _heightCount(0),
    _scrollSpeed(300.0f * CoffeeMaker::Renderer::DynamicResolutionDownScale()),
    _movement(0.0f),
    _direction(Tiles::ScrollDirection::Vertical),
    _xOffset(0.0f),
    _yOffset(0.0f) {
  _texture.LoadFromFile(filePath);

  if (_direction == Tiles::ScrollDirection::Vertical) {
    _widthCount = _viewportWidth / _texture.Width();
    _heightCount = _viewportHeight / _texture.Height() + 1;
  } else {
    _widthCount = _viewportWidth / _texture.Width() + 1;
    _heightCount = _viewportHeight / _texture.Height();
  }
  CM_LOGGER_DEBUG("Tiles: {} - ({},{}) Offsets ({},{})", filePath, _widthCount, _heightCount, _xOffset, _yOffset);
}

Tiles::Tiles(const std::string& filePath, int viewportWidth, int viewportHeight, float speed) :
    _viewportWidth(viewportWidth),
    _viewportHeight(viewportHeight),
    _widthCount(0),
    _heightCount(0),
    _scrollSpeed(speed * CoffeeMaker::Renderer::DynamicResolutionDownScale()),
    _movement(0.0f),
    _direction(Tiles::ScrollDirection::Vertical),
    _xOffset(0.0f),
    _yOffset(0.0f) {
  _texture.LoadFromFile(filePath);
  if (_direction == Tiles::ScrollDirection::Vertical) {
    _widthCount = _viewportWidth / _texture.Width();
    _heightCount = _viewportHeight / _texture.Height() + 1;
  } else {
    _widthCount = _viewportWidth / _texture.Width() + 1;
    _heightCount = _viewportHeight / _texture.Height();
  }
  CM_LOGGER_DEBUG("Tiles: {} - ({},{}) Offsets ({},{})", filePath, _widthCount, _heightCount, _xOffset, _yOffset);
}

Tiles::Tiles(const std::string& filePath, int viewportWidth, int viewportHeight, float speed,
             Tiles::ScrollDirection direction) :
    _viewportWidth(viewportWidth),
    _viewportHeight(viewportHeight),
    _widthCount(0),
    _heightCount(0),
    _scrollSpeed(speed * CoffeeMaker::Renderer::DynamicResolutionDownScale()),
    _movement(0),
    _direction(direction),
    _xOffset(0.0f),
    _yOffset(0.0f) {
  _texture.LoadFromFile(filePath);
  if (_direction == Tiles::ScrollDirection::Vertical) {
    _widthCount = _viewportWidth / _texture.Width();
    _heightCount = _viewportHeight / _texture.Height() + 1;
  } else {
    _widthCount = _viewportWidth / _texture.Width() + 1;
    _heightCount = _viewportHeight / _texture.Height();
  }
  CM_LOGGER_DEBUG("Tiles: {} - ({},{}) Offsets ({},{})", filePath, _widthCount, _heightCount, _xOffset, _yOffset);
}

void Tiles::Update(float deltaTime) { _movement += deltaTime * _scrollSpeed; }

void Tiles::Render() {
  if (_direction == ScrollDirection::Vertical) {
    for (int i = 0; i <= _widthCount; i++) {
      for (int j = 0; j <= _heightCount; j++) {
        float yPos = (j * _texture.Height()) - _texture.Height() + _movement;
        float xPos = (float)i * _texture.Width();

        if (j == 0 && yPos >= 0) {
          _movement = 0;  // NOTE: reset the position for infinite loop effect
          yPos = _heightCount * _texture.Height() - yPos;
          CM_LOGGER_DEBUG("Reset Vertical Position: ({},{})", xPos, yPos);
        }

        _texture.Render(yPos, xPos);
      }
    }
    return;
  }

  for (int i = 0; i <= _widthCount; i++) {
    for (int j = 0; j <= _heightCount; j++) {
      float yPos = (float)j * _texture.Height() + _yOffset;
      float xPos = (i * _texture.Width()) - _texture.Width() + _movement;

      if (i == 0 && xPos >= 0) {
        _movement = 0;  // NOTE: reset the position for infinite loop effect
        xPos = _widthCount * _texture.Width() - xPos;
        CM_LOGGER_DEBUG("Reset Horizontal Position: ({},{})", xPos, yPos);
      }

      _texture.Render(yPos, xPos);
    }
  }
}

void Tiles::SetXOffset(float x) { _xOffset = x; }

void Tiles::SetYOffset(float y) { _yOffset = y; }

void Tiles::PinToBottom() {}
