#include "TextView.hpp"

using namespace CoffeeMaker;

TextView::TextView() : color(CoffeeMaker::Color()), _textContent(""), _font(nullptr), renderer(CoffeeMaker::Renderer::Instance()), _texture(nullptr) {}

TextView::TextView(std::string textContent) : color(CoffeeMaker::Color()), _textContent(textContent), _font(nullptr), renderer(CoffeeMaker::Renderer::Instance()), _texture(nullptr) {}

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
  if (_font == nullptr) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Text View : Render", "Cannot render TextView because it has no assigned font!", nullptr);
    exit(1);
  }
  if (_texture == nullptr) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Text View : Render", "Cannot render TextView because it has no assigned texture!", nullptr);
    exit(1);
  }

  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_RenderCopy(renderer, _texture, NULL, &_textBoard);
}

void TextView::SetFont(TTF_Font *f)
{
  _font = f;
}

void TextView::SetText(const std::string &textContent)
{
  _textContent = textContent;
  SetTextContentTexture();
}

void TextView::SetTextContentTexture()
{
  if (_font != nullptr)
  {
    if (_texture != nullptr) {
      SDL_DestroyTexture(_texture);
      _texture = nullptr;
    }
    SDL_Surface *surface;
    surface = TTF_RenderText_Blended(_font, _textContent.c_str(), color);
    _texture = SDL_CreateTextureFromSurface(renderer, surface);
    _textBoard.w = surface->w;
    _textBoard.h = surface->h;
    _textBoard.x = 0; //(viewPort.w - surface->w) / 2;
    _textBoard.y = 0; //(viewPort.h - surface->h) / 2;
    SDL_FreeSurface(surface);
  }
}

void TextView::SetColor(const SDL_Color& newColor) {
  color.r = newColor.r;
  color.g = newColor.g;
  color.b = newColor.b;
  color.a = newColor.a;
  SetTextContentTexture();
}
