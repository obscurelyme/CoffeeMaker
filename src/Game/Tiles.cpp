#include "Game/Tiles.hpp"

#include "Renderer.hpp"

Tiles::Tiles() : _scrollSpeed(300.0f), _movement(0) {}

Tiles::Tiles(const std::string& filePath, int viewportWidth, int viewportHeight) :
    _viewportWidth(viewportWidth),
    _viewportHeight(viewportHeight),
    _scrollSpeed(300.0f * CoffeeMaker::Renderer::DynamicResolutionDownScale()),
    _movement(0) {
  _texture.LoadFromFile(filePath);
  _texture.SetWidth(_texture.Width());
  _texture.SetHeight(_texture.Height());
}

Tiles::Tiles(const std::string& filePath, int viewportWidth, int viewportHeight, float speed) :
    _viewportWidth(viewportWidth),
    _viewportHeight(viewportHeight),
    _scrollSpeed(speed * CoffeeMaker::Renderer::DynamicResolutionDownScale()),
    _movement(0) {
  _texture.LoadFromFile(filePath);
  _texture.SetWidth(_texture.Width());
  _texture.SetHeight(_texture.Height());
}

void Tiles::Update(float deltaTime) { _movement += deltaTime * _scrollSpeed; }

void Tiles::Render() {
  const int widthCount = _viewportWidth / _texture.Width();
  const int heightCount = (_viewportHeight / _texture.Height()) + 1;

  for (int i = 0; i <= widthCount; i++) {
    for (int j = 0; j <= heightCount; j++) {
      float yPos = (j * _texture.Height()) - _texture.Height() + _movement;
      float xPos = (float)i * _texture.Width();

      if (j == 0 && yPos >= 0) {
        _movement = 0;  // NOTE: reset the position for infinite loop effect
      }

      _texture.Render(yPos, xPos);
    }
  }
}
