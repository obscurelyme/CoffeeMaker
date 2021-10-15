#include "Texture.hpp"

#include <SDL2/SDL_image.h>

#include "Logger.hpp"
#include "MessageBox.hpp"
#include "Renderer.hpp"
#include "Utilities.hpp"

using namespace CoffeeMaker;

SDL_Texture *CoffeeMaker::createRectTextureFromSurface(int height, int width, const SDL_Color &color) {
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
  int rmask = 0xff000000;
  int gmask = 0x00ff0000;
  int bmask = 0x0000ff00;
  int amask = 0x000000ff;
#else
  int rmask = 0x000000ff;
  int gmask = 0x0000ff00;
  int bmask = 0x00ff0000;
  int amask = 0xff000000;
#endif
  SDL_Surface *surface = SDL_CreateRGBSurface(0, width, height, 32, rmask, gmask, bmask, amask);
  if (surface == NULL) {
    CoffeeMaker::MessageBox::ShowMessageBoxAndQuit("SDL_CreateRGBSurface Error", "Could not create surface");
  }

  SDL_Texture *texture = SDL_CreateTextureFromSurface(Renderer::Instance(), surface);
  if (texture == NULL) {
    CoffeeMaker::MessageBox::ShowMessageBoxAndQuit("SDL_CreateTextureFromSurface Error", "Could not create textgure");
  }

  // TODO Need to manually fill in the pixels
  // for (int i = 0; i < surface->w; i++) {
  //   for (int j = 0; j < surface->h; j++) {
  //     surface->pixels[i + j] = 255;
  //   }
  // }

  SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
  SDL_FreeSurface(surface);
  return texture;
}

std::string Texture::_textureDirectory = "";

void Texture::SetTextureDirectory() {
  Texture::_textureDirectory = fmt::format(fmt::runtime("{}/{}"), CoffeeMaker::Utilities::AssetsDirectory(), "images");
}

Texture::Texture() : _texture(nullptr), _color(Color()), _height(0), _width(0), _useColorKey(false) {}

Texture::Texture(const std::string &filePath) :
    _texture(nullptr), _color(Color()), _height(0), _width(0), _useColorKey(false) {
  LoadFromFile(filePath);
}

Texture::Texture(const SDL_Color &color) :
    _texture(nullptr), _color(color), _height(0), _width(0), _useColorKey(false) {}

Texture::Texture(const std::string &filePath, bool useColorKey) :
    _texture(nullptr), _height(0), _width(0), _useColorKey(useColorKey) {
  LoadFromFile(filePath);
}

Texture::~Texture() {
  if (_texture != nullptr) {
    if (Renderer::Exists()) {
      SDL_DestroyTexture(_texture);
    }
    _texture = nullptr;
  }
}

void Texture::LoadFromFile(const std::string &filePath) {
  _surface = nullptr;
  std::string path = fmt::format(fmt::runtime("{}/{}"), Texture::_textureDirectory, filePath);
  _surface = IMG_Load(path.c_str());
  if (_surface == nullptr) {
    // TODO: something went wrong loading the texture
    Logger::Error(fmt::format(fmt::runtime("Could not load surface at filepath {}"), filePath));
    return;
  }

  if (_useColorKey) {
    SDL_SetColorKey(_surface, SDL_TRUE, SDL_MapRGB(_surface->format, COLOR_KEY.r, COLOR_KEY.g, COLOR_KEY.b));
  }
  _texture = SDL_CreateTextureFromSurface(CoffeeMaker::Renderer::Instance(), _surface);
  _height = _surface->h;
  _width = _surface->w;
  SDL_FreeSurface(_surface);
}

void Texture::CreateFromSurface(int height, int width, const SDL_Color &c) {
  _texture = createRectTextureFromSurface(height, width, c);
  _width = 10;
  _height = 25;
}

void Texture::Render(int top, int left) {
  SDL_Rect renderQuad = {.x = left, .y = top, .w = _width, .h = _height};

  if (_texture == nullptr) {
    SDL_SetRenderDrawColor(CoffeeMaker::Renderer::Instance(), _color.r, _color.g, _color.b, _color.a);
    SDL_RenderFillRect(CoffeeMaker::Renderer::Instance(), &renderQuad);
    return;
  }

  SDL_RenderCopy(CoffeeMaker::Renderer::Instance(), _texture, NULL, &renderQuad);
}

void Texture::Render(float top, float left) {
  SDL_FRect renderQuad = {.x = left, .y = top, .w = (float)_width, .h = (float)_height};

  if (_texture == nullptr) {
    SDL_SetRenderDrawColor(CoffeeMaker::Renderer::Instance(), _color.r, _color.g, _color.b, _color.a);
    SDL_RenderDrawRectF(CoffeeMaker::Renderer::Instance(), &renderQuad);
    return;
  }

  SDL_RenderCopyF(CoffeeMaker::Renderer::Instance(), _texture, NULL, &renderQuad);
}

void Texture::Render(int top, int left, int height, int width) {
  SDL_Rect renderQuad = {.x = left, .y = top, .w = width, .h = height};

  if (_texture == nullptr) {
    SDL_SetRenderDrawColor(CoffeeMaker::Renderer::Instance(), _color.r, _color.g, _color.b, _color.a);
    SDL_RenderFillRect(CoffeeMaker::Renderer::Instance(), &renderQuad);
    return;
  }

  SDL_RenderCopy(CoffeeMaker::Renderer::Instance(), _texture, NULL, &renderQuad);
}

void Texture::Render(const SDL_Rect &clip, const SDL_Rect &renderRect) {
  if (_texture == nullptr) {
    SDL_SetRenderDrawColor(CoffeeMaker::Renderer::Instance(), _color.r, _color.g, _color.b, _color.a);
    SDL_RenderFillRect(CoffeeMaker::Renderer::Instance(), &renderRect);
    return;
  }

  SDL_RenderCopy(CoffeeMaker::Renderer::Instance(), _texture, &clip, &renderRect);
}

void Texture::Render(const SDL_Rect &clip, const SDL_Rect &renderRect, double rotation) {
  if (_texture == nullptr) {
    CoffeeMaker::MessageBox::ShowMessageBoxAndQuit("Error rendering texture", "Cannot render texture with nullptr");
    return;
  }
  SDL_RendererFlip flip = SDL_FLIP_NONE;
  SDL_RenderCopyEx(CoffeeMaker::Renderer::Instance(), _texture, &clip, &renderRect, rotation, NULL, flip);
}

void Texture::Render(const SDL_Rect &renderRect, double rotation) {
  if (_texture == nullptr) {
    CoffeeMaker::MessageBox::ShowMessageBoxAndQuit("Error rendering texture", "Cannot render texture with nullptr");
    return;
  }
  SDL_RendererFlip flip = SDL_FLIP_NONE;
  SDL_RenderCopyEx(CoffeeMaker::Renderer::Instance(), _texture, NULL, &renderRect, rotation, NULL, flip);
}

void Texture::SetAlpha(Uint8 alpha) {
  if (_texture == nullptr) {
    Logger::Error("Could not set alpha on NULL texture");
    return;
  }
  SDL_SetTextureAlphaMod(_texture, alpha);
}

void Texture::SetColor(SDL_Color color) {
  if (_texture == nullptr) {
    _color = color;
    return;
  }
  SDL_SetTextureColorMod(_texture, color.r, color.g, color.b);
}

SDL_Color Texture::GetColorMod() {
  SDL_Color colorMod = {.a = 255};
  if (_texture != nullptr) {
    SDL_GetTextureColorMod(_texture, &colorMod.r, &colorMod.g, &colorMod.b);
  }
  return colorMod;
}

void Texture::SetBlendMode(SDL_BlendMode blend) {
  if (_texture == nullptr) {
    Logger::Error("Could not set blend mode on NULL texture");
    return;
  }
  SDL_SetTextureBlendMode(_texture, blend);
}

int Texture::Height() const { return _height; }

int Texture::Width() const { return _width; }

void Texture::SetHeight(int const height) { _height = height; }

void Texture::SetWidth(int const width) { _width = width; }

SDL_Texture *Texture::Handle() const { return _texture; }
