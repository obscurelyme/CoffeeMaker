#ifndef _coffeemaker_scalableuisprite_hpp
#define _coffeemaker_scalableuisprite_hpp

#include <SDL2/SDL.h>

#include <cmath>
#include <string>

#include "Renderer.hpp"
#include "Texture.hpp"
#include "UIComponent.hpp"
#include "Utilities.hpp"

namespace CoffeeMaker {
  namespace Widgets {

    class ScalableUISprite : public UIComponent {
      public:
      ScalableUISprite(const std::string& filePath, float width, float height, int cornerClipX, int cornerClipY) :
          _width(width),
          _height(height),
          _cornerClipX(cornerClipX),
          _cornerClipY(cornerClipY),
          _texture(CreateScope<CoffeeMaker::Texture>(filePath)) {
        clientRect.w = static_cast<int>(_width);
        clientRect.h = static_cast<int>(_height);
        clientRect.x = 0;
        clientRect.y = 0;

        SetCornerClipRects();
        SetCornerDestinationRects();
        SetEdgeClipRects();
        SetEdgeDestinationRects();
        SetCenterClipRect();
      }
      ~ScalableUISprite() = default;

      void Render() override {
        _texture->Render(_cornerClipTopLeft, _cornerDestTopLeft);
        _texture->Render(_cornerClipTopRight, _cornerDestTopRight);
        _texture->Render(_cornerClipBottomLeft, _cornerDestBottomLeft);
        _texture->Render(_cornerClipBottomRight, _cornerDestBottomRight);

        _edgeDestTop.y = 0;
        _edgeDestTop.x = _cornerDestTopLeft.w + _cornerDestTopLeft.x;
        _edgeDestTop.h = _edgeClipTop.h;
        _edgeDestTop.w = _edgeClipTop.w;

        _edgeDestBottom.y = _cornerDestBottomLeft.y;
        _edgeDestBottom.x = _cornerDestTopLeft.w + _cornerDestTopLeft.x;
        _edgeDestBottom.h = _edgeClipTop.h;
        _edgeDestBottom.w = _edgeClipTop.w;

        _edgeDestLeft.x = _cornerDestTopLeft.x;
        _edgeDestLeft.y = _cornerDestTopLeft.y + _cornerDestTopLeft.h;
        _edgeDestLeft.h = _edgeClipLeft.h;
        _edgeDestLeft.w = _edgeClipLeft.w;

        _edgeDestRight.x = _cornerDestTopRight.x;
        _edgeDestRight.y = _cornerDestTopRight.y + _cornerDestTopRight.h;
        _edgeDestRight.h = _edgeClipRight.h;
        _edgeDestRight.w = _edgeClipRight.w;

        _centerDest.x = _centerClip.x;
        _centerDest.y = _centerClip.y;
        _centerDest.h = _centerClip.h;
        _centerDest.w = _centerClip.w;

        int currentXOffset;
        int currentYOffset;
        for (int i = 0; i < _numTopTiles; i++) {
          currentXOffset = i * _edgeDestTop.w;
          _edgeDestTop.x = _cornerDestTopLeft.w + _cornerDestTopLeft.x + currentXOffset;
          _edgeDestBottom.x = _edgeDestTop.x;

          if (i == _numTopTiles - 1) {
            // last in the sequence, we need the remaining width space and make a new destination rect based on that.
            _edgeDestTop.w = _cornerDestTopRight.x - _edgeDestTop.x;
            _edgeDestBottom.w = _edgeDestTop.w;
          }
          _texture->Render(_edgeClipTop, _edgeDestTop);
          _texture->Render(_edgeClipBottom, _edgeDestBottom);
        }

        for (int i = 0; i < _numLeftTiles; i++) {
          currentYOffset = i * _edgeDestLeft.h;
          _edgeDestLeft.y = _cornerDestTopLeft.h + _cornerDestTopLeft.y + currentYOffset;
          _edgeDestRight.y = _edgeDestLeft.y;

          if (i == _numLeftTiles - 1) {
            _edgeDestLeft.h = _cornerDestBottomLeft.y - _edgeDestLeft.y;
            _edgeDestRight.h = _edgeDestLeft.h;
          }

          _texture->Render(_edgeClipLeft, _edgeDestLeft);
          _texture->Render(_edgeClipRight, _edgeDestRight);
        }

        for (int i = 0, xOffset = 0; i < _numTopTiles; i++) {
          xOffset = i * _centerDest.w;
          _centerDest.x = xOffset + _cornerDestTopLeft.w + _cornerDestTopLeft.x;
          if (i == _numTopTiles - 1) {
            _centerDest.w = _cornerDestTopRight.x - _centerDest.x;
          }

          for (int j = 0, yOffset = 0; j < _numLeftTiles; j++) {
            yOffset = j * _centerDest.h;
            _centerDest.y = _cornerDestTopLeft.h + _cornerDestTopLeft.y + yOffset;
            if (j == _numLeftTiles - 1) {
              _centerDest.h = _cornerDestBottomLeft.y - _cornerDestTopLeft.h;
            }
            _texture->Render(_centerClip, _centerDest);
          }
        }

        UIComponent::Render();
      }

      void OnAppend() override {
        UIComponent::OnAppend();

        SetCornerDestinationRects();
        SetEdgeDestinationRects();
      }

      private:
      void SetCornerClipRects() {
        _cornerClipTopLeft.x = 0;
        _cornerClipTopLeft.y = 0;
        _cornerClipTopLeft.w = _cornerClipX;
        _cornerClipTopLeft.h = _cornerClipY;

        _cornerClipTopRight.x = _texture->Width() - _cornerClipX;
        _cornerClipTopRight.y = 0;
        _cornerClipTopRight.w = _cornerClipX;
        _cornerClipTopRight.h = _cornerClipY;

        _cornerClipBottomLeft.x = 0;
        _cornerClipBottomLeft.y = _texture->Height() - _cornerClipY;
        _cornerClipBottomLeft.w = _cornerClipX;
        _cornerClipBottomLeft.h = _cornerClipY;

        _cornerClipBottomRight.x = _texture->Width() - _cornerClipX;
        _cornerClipBottomRight.y = _texture->Height() - _cornerClipY;
        _cornerClipBottomRight.w = _cornerClipX;
        _cornerClipBottomRight.h = _cornerClipY;
      }

      void SetCornerDestinationRects() {
        _cornerDestTopLeft.x = clientRect.x;
        _cornerDestTopLeft.y = clientRect.y;
        _cornerDestTopLeft.w = _cornerClipX;
        _cornerDestTopLeft.h = _cornerClipY;

        _cornerDestTopRight.x = clientRect.x + clientRect.w - _cornerClipX;
        _cornerDestTopRight.y = clientRect.y;
        _cornerDestTopRight.w = _cornerClipX;
        _cornerDestTopRight.h = _cornerClipY;

        _cornerDestBottomLeft.x = clientRect.x;
        _cornerDestBottomLeft.y = clientRect.y + clientRect.h - _cornerClipY;
        _cornerDestBottomLeft.w = _cornerClipX;
        _cornerDestBottomLeft.h = _cornerClipY;

        _cornerDestBottomRight.x = clientRect.x + clientRect.w - _cornerClipX;
        _cornerDestBottomRight.y = clientRect.y + clientRect.h - _cornerClipY;
        _cornerDestBottomRight.w = _cornerClipX;
        _cornerDestBottomRight.h = _cornerClipY;
      }

      void SetEdgeClipRects() {
        _edgeClipLeft.x = 0;
        _edgeClipLeft.y = _cornerClipTopLeft.h;
        _edgeClipLeft.h = _cornerClipBottomLeft.y - _cornerClipTopLeft.h;
        _edgeClipLeft.w = _cornerClipTopLeft.w;

        _edgeClipRight.x = _cornerClipTopRight.x;
        _edgeClipRight.y = _edgeClipLeft.y;
        _edgeClipRight.h = _edgeClipLeft.h;
        _edgeClipRight.w = _edgeClipLeft.w;

        _edgeClipTop.x = _cornerClipTopLeft.w;
        _edgeClipTop.y = 0;
        _edgeClipTop.h = _cornerClipY;
        _edgeClipTop.w = _cornerClipTopRight.x - _cornerClipTopLeft.w;

        _edgeClipBottom.x = _cornerClipBottomLeft.w;
        _edgeClipBottom.y = _cornerClipBottomLeft.y;
        _edgeClipBottom.h = _edgeClipTop.h;
        _edgeClipBottom.w = _edgeClipTop.w;
      }

      void SetEdgeDestinationRects() {
        float edgeClipTop = static_cast<float>(_edgeClipTop.w);
        float cornerDestTopRight = static_cast<float>(_cornerDestTopRight.x);
        float cornerDestTopLeftWidth = static_cast<float>(_cornerDestTopLeft.w + _cornerDestTopLeft.x);
        _numTopTiles = static_cast<int>(std::ceil((cornerDestTopRight - cornerDestTopLeftWidth) / edgeClipTop));
        _numBottomTiles = _numTopTiles;

        float edgeClipLeft = static_cast<float>(_edgeClipLeft.h);
        float cornerDestBottomLeft = static_cast<float>(_cornerDestBottomLeft.y);
        float cornerDestTopLeftHeight = static_cast<float>(_cornerDestTopLeft.h + _cornerDestTopLeft.y);
        _numLeftTiles = static_cast<int>(std::ceil((cornerDestBottomLeft - cornerDestTopLeftHeight) / edgeClipLeft));
        _numRightTiles = _numLeftTiles;
      }

      void SetCenterClipRect() {
        _centerClip.x = _cornerClipTopLeft.w;
        _centerClip.y = _cornerClipTopLeft.h;
        _centerClip.h = _cornerClipBottomLeft.y - _cornerClipTopLeft.h;
        _centerClip.w = _cornerClipTopRight.x - _cornerClipTopLeft.w;
      }

      float _width;
      float _height;
      int _cornerClipX;
      int _cornerClipY;

      /*************************************************************************
       * Clip and Src SDL_Rects for the corners of the sprite
       ************************************************************************/
      SDL_Rect _cornerClipTopLeft;
      SDL_Rect _cornerDestTopLeft;
      SDL_Rect _cornerClipTopRight;
      SDL_Rect _cornerDestTopRight;
      SDL_Rect _cornerClipBottomLeft;
      SDL_Rect _cornerDestBottomLeft;
      SDL_Rect _cornerClipBottomRight;
      SDL_Rect _cornerDestBottomRight;
      /*************************************************************************
       * Clip and Src SDL_Rects for the edge tilables of the sprite
       ************************************************************************/
      SDL_Rect _edgeClipTop;
      SDL_Rect _edgeDestTop;
      SDL_Rect _edgeClipRight;
      SDL_Rect _edgeDestRight;
      SDL_Rect _edgeClipLeft;
      SDL_Rect _edgeDestLeft;
      SDL_Rect _edgeClipBottom;
      SDL_Rect _edgeDestBottom;
      int _numTopTiles;
      int _numRightTiles;
      int _numBottomTiles;
      int _numLeftTiles;
      /*************************************************************************
       * Clip and Src SDL_Rects for the center tilables of the sprite
       ************************************************************************/
      SDL_Rect _centerClip;
      SDL_Rect _centerDest;

      Scope<CoffeeMaker::Texture> _texture;
    };

  }  // namespace Widgets
}  // namespace CoffeeMaker

#endif
