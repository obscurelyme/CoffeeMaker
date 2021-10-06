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
    _texture(nullptr),
    _wrapLength(0) {
  _id = "Text-" + std::to_string(++_textId);
}

Text::Text(std::string textContent) :
    color(CoffeeMaker::Color()),
    _textContent(textContent),
    _font(nullptr),
    renderer(CoffeeMaker::Renderer::Instance()),
    _texture(nullptr),
    _wrapLength(0) {
  _id = "Text-" + std::to_string(++_textId);
}

Text::~Text() {
  if (_texture != nullptr) {
    if (CoffeeMaker::Renderer::Exists()) {
      // NOTE: destroy the current texture if the Renderer still exists
      // we do this because SDL_DestroyRenderer will auto destroy all
      // textures it created.
      SDL_DestroyTexture(_texture);
    }
    _texture = nullptr;
  }
  _font = nullptr;
}

void Text::OnAppend() {
  SetTextContentTexture();
  UIComponent::OnAppend();
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

  UIComponent::DebugRender();
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_RenderCopy(renderer, _texture, NULL, &clientRect);
}

void Text::SetFont(TTF_Font *f) {
  _font = f;
  SetTextContentTexture();
}

void Text::SetText(const std::string &textContent) {
  _textContent = textContent;
  SetTextContentTexture();
}

void Text::SetTextContentTexture() {
  if (_font != nullptr && _textContent != "") {
    if (_texture != nullptr) {
      SDL_DestroyTexture(_texture);
      _texture = nullptr;
    }
    SDL_Surface *surface;
    surface = TTF_RenderText_Blended_Wrapped(_font, _textContent.c_str(), color, GetWrapLength());
    if (surface == nullptr) {
      MessageBox::ShowMessageBoxAndQuit(
          "Text Surface Error", "Could not create a text surface for the given string: \"" + _textContent + "\"");
    }
    _texture = SDL_CreateTextureFromSurface(renderer, surface);
    clientRect.w = surface->w;
    clientRect.h = surface->h;
    SDL_FreeSurface(surface);
    CalcPosition();
  }
}

void Text::SetColor(const SDL_Color &newColor) {
  color.r = newColor.r;
  color.g = newColor.g;
  color.b = newColor.b;
  color.a = newColor.a;
  SetTextContentTexture();
}

void Text::SetWrapLength(Uint32 wrapLength) {
  _wrapLength = wrapLength;
  SetTextContentTexture();
}

Uint32 Text::GetWrapLength() const {
  if (_wrapLength > 0) {
    return _wrapLength;
  }

  return _parent != nullptr ? _parent->clientRect.w : viewport.w;
}
