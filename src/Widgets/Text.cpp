#include "Widgets/Text.hpp"

#include "MessageBox.hpp"

using namespace CoffeeMaker::Widgets;
using namespace CoffeeMaker::UIProperties;

int Text::_textId = 0;

Text::Text() :
    color(CoffeeMaker::Color()),
    _textContent(""),
    _font(nullptr),
    renderer(CoffeeMaker::Renderer::Instance()),
    _texture(nullptr) {
  _id = "Text-" + std::to_string(++_textId);
}

Text::Text(std::string textContent) :
    color(CoffeeMaker::Color()),
    _textContent(textContent),
    _font(nullptr),
    renderer(CoffeeMaker::Renderer::Instance()),
    _texture(nullptr) {
  _id = "Text-" + std::to_string(++_textId);
}

Text::~Text() {
  if (_texture != nullptr) {
    // SDL renderer destroys textures automatically when calling
    // SDL_DestroyRenderer
    _texture = nullptr;
  }
}

void Text::Render() {
  if (_font == nullptr) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Text View : Render",
                             "Cannot render Text because it has no assigned font!", nullptr);
    exit(1);
  }
  if (_texture == nullptr) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Text View : Render",
                             "Cannot render Text because it has no assigned texture!", nullptr);
    exit(1);
  }

  clientRect.x = UIComponent::DeriveXPosition();
  clientRect.y = UIComponent::DeriveYPosition();
  UIComponent::DebugRender();
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_RenderCopy(renderer, _texture, NULL, &clientRect);
}

void Text::SetFont(TTF_Font *f) { _font = f; }

void Text::SetText(const std::string &textContent) {
  _textContent = textContent;
  SetTextContentTexture();
}

void Text::SetTextContentTexture() {
  if (_font != nullptr) {
    if (_texture != nullptr) {
      SDL_DestroyTexture(_texture);
      _texture = nullptr;
    }
    SDL_Surface *surface;
    surface = TTF_RenderText_Blended(_font, _textContent.c_str(), color);
    _texture = SDL_CreateTextureFromSurface(renderer, surface);
    clientRect.w = surface->w;
    clientRect.h = surface->h;
    SDL_FreeSurface(surface);
  } else {
    CoffeeMaker::MessageBox::ShowMessageBoxAndQuit("Cannot set text with NULL font",
                                                   "Cannot generate a texture for text element when it's font is NULL");
  }
}

void Text::SetColor(const SDL_Color &newColor) {
  color.r = newColor.r;
  color.g = newColor.g;
  color.b = newColor.b;
  color.a = newColor.a;
  if (_textContent != "") {
    SetTextContentTexture();
  }
}
