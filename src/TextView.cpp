#include "TextView.hpp"

using namespace CoffeeMaker;

TextView::TextView() : color(CoffeeMaker::Color()), _textContent(""), font(nullptr), renderer(CoffeeMaker::Renderer::Instance()), _texture(nullptr) {}

TextView::TextView(std::string textContent) : color(CoffeeMaker::Color()), _textContent(textContent), font(nullptr), renderer(CoffeeMaker::Renderer::Instance()), _texture(nullptr) {}

TextView::~TextView()
{
  if (_texture != nullptr)
  {
    // SDL renderer destroys textures automatically when calling SDL_DestroyRenderer
    _texture = nullptr;
  }
}

void TextView::Render()
{
  if (_texture != nullptr)
  {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    // if (_parent != nullptr)
    // {
    //   // Render should be relative to the parent position
    //   _textBoard.x = ((_parent->clientRect.w - _textBoard.w) / 2) + _parent->clientRect.x;
    //   _textBoard.y = ((_parent->clientRect.h - _textBoard.h) / 2) + _parent->clientRect.y;
    // }
    SDL_RenderCopy(renderer, _texture, NULL, &_textBoard);
  }
}

void TextView::SetFont(TTF_Font *f)
{
  font = f;
}

void TextView::SetText(const std::string &textContent)
{
  _textContent = textContent;
  SetTextContentTexture();
}

void TextView::SetTextContentTexture()
{
  if (font != nullptr)
  {
    SDL_Surface *surface;
    surface = TTF_RenderText_Blended(font, _textContent.c_str(), color);
    _texture = SDL_CreateTextureFromSurface(renderer, surface);
    _textBoard.w = surface->w;
    _textBoard.h = surface->h;
    _textBoard.x = 0; //(viewPort.w - surface->w) / 2;
    _textBoard.y = 0; //(viewPort.h - surface->h) / 2;
    SDL_FreeSurface(surface);
  }
}
