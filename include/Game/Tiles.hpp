#ifndef _tiles_hpp
#define _tiles_hpp

#include <string>

#include "Logger.hpp"
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
  ~Tiles() { CM_LOGGER_DEBUG("Tile Destroyed: {}", _name); };

  void Update(float deltaTime);
  void Render();

  void SetXOffset(float x);
  void SetYOffset(float y);
  void PinToBottom();
  int Height() const { return _texture.Height(); }
  int Width() const { return _texture.Width(); }

  private:
  std::string _name;
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
