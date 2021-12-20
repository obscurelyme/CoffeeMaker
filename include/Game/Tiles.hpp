#ifndef _tiles_hpp
#define _tiles_hpp

#include <string>

#include "Texture.hpp"

/**
 * Build out the tiling background for the game
 */
class Tiles {
  public:
  enum ScrollDirection { Vertical, Horizontal };
  Tiles();
  /**
   * Construct the tiling based on the viewport width and height
   * and the height/width of the loaded texture
   */
  Tiles(const std::string& filePath, int viewportWidth, int viewportHeight);
  Tiles(const std::string& filePath, int viewportWidth, int viewportHeight, float speed);
  Tiles(const std::string& filePath, int viewportWidth, int viewportHeight, float speed,
        Tiles::ScrollDirection direction);
  ~Tiles() = default;

  void Update(float deltaTime);
  void Render();

  void SetXOffset(float x);
  void SetYOffset(float y);
  void PinToBottom();
  int Height() const { return _texture.Height(); }
  int Width() const { return _texture.Width(); }

  private:
  CoffeeMaker::Texture _texture;
  int _viewportWidth;
  int _viewportHeight;
  int _widthCount;
  int _heightCount;
  float _scrollSpeed;
  float _movement;
  ScrollDirection _direction;
  float _xOffset;
  float _yOffset;
};

#endif
