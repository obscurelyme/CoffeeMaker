#include "Game/Tiles.hpp"
#include "Renderer.hpp"

Tiles::Tiles(const std::string& filePath, int viewportWidth, int viewportHeight): _viewportWidth(viewportWidth), _viewportHeight(viewportHeight) {
  _texture.LoadFromFile(filePath);
}


void Tiles::Render() {
  for (int i = 0; i <= _viewportWidth; i+=_texture.Width()) {
    for (int j = 0; j <= _viewportHeight; j+=_texture.Height()) {
      _texture.Render(j, i);
    }
  }
}
