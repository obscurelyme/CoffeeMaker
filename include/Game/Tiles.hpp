#ifndef _tiles_hpp
#define _tiles_hpp

#include <string>

#include "Texture.hpp"

/**
 * Build out the tiling background for the game
 */
class Tiles {
  public:
  Tiles();
  /**
   * Construct the tiling based on the viewport width and height
   * and the height/width of the loaded texture
   */
  Tiles(const std::string& filePath, int viewportWidth, int viewportHeight);
  ~Tiles() = default;

  void Update(float deltaTime);
  void Render();

  private:
  CoffeeMaker::Texture _texture;
  int _viewportWidth;
  int _viewportHeight;
  int _scrollSpeed;
  float _movement;
};

#endif
