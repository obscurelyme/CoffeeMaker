#include "Sprite.hpp"

CoffeeMaker::Sprite::Sprite(const std::string& filePath) :
    rotation(0), _texture(CreateScope<CoffeeMaker::Texture>(filePath, true)) {
  clientRect.x = 0;
  clientRect.y = 0;
  clientRect.w = static_cast<float>(_texture->Width());
  clientRect.h = static_cast<float>(_texture->Height());
  clipRect.x = 0;
  clipRect.y = 0;
  clipRect.w = _texture->Width();
  clipRect.h = _texture->Height();
}

CoffeeMaker::Sprite::Sprite(const std::string& filePath, float width, float height) :
    rotation(0), _texture(CreateScope<CoffeeMaker::Texture>(filePath, true)) {
  clientRect.x = 0;
  clientRect.y = 0;
  clientRect.w = width;
  clientRect.h = height;
  clipRect.x = 0;
  clipRect.y = 0;
  clipRect.w = _texture->Width();
  clipRect.h = _texture->Height();
}

CoffeeMaker::Sprite::~Sprite() {}

void CoffeeMaker::Sprite::Render() { _texture->Render(clipRect, clientRect, rotation); }

void CoffeeMaker::Sprite::Render(SDL_Rect clip) { _texture->Render(clip, clientRect, rotation); }

void CoffeeMaker::Sprite::SetPosition(const CoffeeMaker::Math::Vector2D& pos) {
  clientRect.x = pos.x;
  clientRect.y = pos.y;
}

void CoffeeMaker::Sprite::SetAlpha(Uint8 alpha) { _texture->SetAlpha(alpha); }
