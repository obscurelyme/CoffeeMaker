#include "TextView.hpp"

using namespace CoffeeMaker;

TextView::TextView()
    : color(CoffeeMaker::Color()),
      _textContent(""),
      _font(nullptr),
      renderer(CoffeeMaker::Renderer::Instance()),
      _texture(nullptr),
      _xProps(TextAlignmentX::LeftAligned),
      _yProps(TextAlignmentY::TopAligned) {}

TextView::TextView(std::string textContent)
    : color(CoffeeMaker::Color()),
      _textContent(textContent),
      _font(nullptr),
      renderer(CoffeeMaker::Renderer::Instance()),
      _texture(nullptr),
      _xProps(TextAlignmentX::LeftAligned),
      _yProps(TextAlignmentY::TopAligned) {}

TextView::~TextView() {
  if (_texture != nullptr) {
    // SDL renderer destroys textures automatically when calling
    // SDL_DestroyRenderer
    _texture = nullptr;
  }
}

void TextView::Render() {
  if (_font == nullptr) {
    SDL_ShowSimpleMessageBox(
        SDL_MESSAGEBOX_ERROR, "Text View : Render",
        "Cannot render TextView because it has no assigned font!", nullptr);
    exit(1);
  }
  if (_texture == nullptr) {
    SDL_ShowSimpleMessageBox(
        SDL_MESSAGEBOX_ERROR, "Text View : Render",
        "Cannot render TextView because it has no assigned texture!", nullptr);
    exit(1);
  }

  _textBoard.x = DeriveXAxisPosition();
  _textBoard.y = DeriveYAxisPosition();
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_RenderCopy(renderer, _texture, NULL, &_textBoard);
}

void TextView::SetFont(TTF_Font *f) { _font = f; }

void TextView::SetText(const std::string &textContent) {
  _textContent = textContent;
  SetTextContentTexture();
}

void TextView::SetTextContentTexture() {
  if (_font != nullptr) {
    if (_texture != nullptr) {
      SDL_DestroyTexture(_texture);
      _texture = nullptr;
    }
    SDL_Surface *surface;
    surface = TTF_RenderText_Blended(_font, _textContent.c_str(), color);
    _texture = SDL_CreateTextureFromSurface(renderer, surface);
    _textBoard.w = surface->w;
    _textBoard.h = surface->h;
    SDL_FreeSurface(surface);
  }
}

void TextView::SetColor(const SDL_Color &newColor) {
  color.r = newColor.r;
  color.g = newColor.g;
  color.b = newColor.b;
  color.a = newColor.a;
  SetTextContentTexture();
}

void TextView::SetXAlignment(TextAlignmentX xAlignment) {
  _xProps = xAlignment;
}

void TextView::SetYAlignment(TextAlignmentY yAlignment) {
  _yProps = yAlignment;
}

int TextView::DeriveXAxisPosition() {
  SDL_Rect currentViewport;
  SDL_RenderGetViewport(Renderer::Instance(), &currentViewport);

  if (_xProps == TextAlignmentX::Centered) {
    return (currentViewport.w - _textBoard.w) / 2;
  } else if (_xProps == TextAlignmentX::RightAligned) {
    return (currentViewport.w - _textBoard.w);
  } else {
    return 0;
  }
}

int TextView::DeriveYAxisPosition() {
  SDL_Rect currentViewport;
  SDL_RenderGetViewport(Renderer::Instance(), &currentViewport);

  if (_yProps == TextAlignmentY::Centered) {
    return (currentViewport.h - _textBoard.h) / 2;
  } else if (_yProps == TextAlignmentY::BottomAligned) {
    return (currentViewport.h - _textBoard.h);
  } else {
    return 0;
  }
}
