#include "Texture.hpp"
#include "Utilities.hpp"
#include "Renderer.hpp"
#include "Logger.hpp"

#include <SDL2/SDL_image.h>

using namespace CoffeeMaker;

std::string Texture::_textureDirectory = "";

void Texture::SetTextureDirectory()
{
  Texture::_textureDirectory = fmt::format("{}/{}", CoffeeMaker::Utilities::AssetsDirectory(), "images");
}

Texture::Texture() : _texture(nullptr), _color(Color()), _height(0), _width(0), _useColorKey(false) {}

Texture::Texture(const std::string &filePath) : _texture(nullptr), _color(Color()), _height(0), _width(0), _useColorKey(false)
{
  LoadFromFile(filePath);
}

Texture::Texture(const SDL_Color &color) : _texture(nullptr), _color(color), _height(0), _width(0), _useColorKey(false) {}

Texture::Texture(const std::string &filePath, bool useColorKey) :
  _texture(nullptr), _height(0), _width(0), _useColorKey(useColorKey) {
  LoadFromFile(filePath);
}

Texture::~Texture()
{
  if (_texture != nullptr)
  {
    // SDL renderer destroys textures automatically
    _texture = nullptr;
  }
}

void Texture::LoadFromFile(const std::string &filePath)
{
  SDL_Surface *surface = nullptr;
  std::string path = fmt::format("{}/{}", Texture::_textureDirectory, filePath);
  surface = IMG_Load(path.c_str());
  if (surface == nullptr)
  {
    // TODO: something went wrong loading the texture
    Logger::Error(fmt::format("Could not load surface at filepath {}", filePath));
    return;
  }

  if (_useColorKey)
  {
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, COLOR_KEY.r, COLOR_KEY.g, COLOR_KEY.b));
  }
  _texture = SDL_CreateTextureFromSurface(CoffeeMaker::Renderer::Instance(), surface);
  _height = surface->h;
  _width = surface->w;
  SDL_FreeSurface(surface);
}

void Texture::Render(int top, int left)
{
  SDL_Rect renderQuad = {.x = left, .y = top, .w = _width, .h = _height};

  if (_texture == nullptr)
  {
    SDL_SetRenderDrawColor(CoffeeMaker::Renderer::Instance(), _color.r, _color.g, _color.b, _color.a);
    SDL_RenderFillRect(CoffeeMaker::Renderer::Instance(), &renderQuad);
    return;
  }

  SDL_RenderCopy(CoffeeMaker::Renderer::Instance(), _texture, NULL, &renderQuad);
}

void Texture::Render(int top, int left, int height, int width)
{
  SDL_Rect renderQuad = {.x = left, .y = top, .w = width, .h = height};

  if (_texture == nullptr)
  {
    SDL_SetRenderDrawColor(CoffeeMaker::Renderer::Instance(), _color.r, _color.g, _color.b, _color.a);
    SDL_RenderFillRect(CoffeeMaker::Renderer::Instance(), &renderQuad);
    return;
  }

  SDL_RenderCopy(CoffeeMaker::Renderer::Instance(), _texture, NULL, &renderQuad);
}

void Texture::SetAlpha(Uint8 alpha)
{
  if (_texture == nullptr)
  {
    Logger::Error("Could not set alpha on NULL texture");
    return;
  }
  SDL_SetTextureAlphaMod(_texture, alpha);
}

void Texture::SetColor(SDL_Color color)
{
  if (_texture == nullptr)
  {
    _color = color;
    return;
  }
  SDL_SetTextureColorMod(_texture, color.r, color.g, color.b);
}

void Texture::SetBlendMode(SDL_BlendMode blend)
{
  if (_texture == nullptr)
  {
    Logger::Error("Could not set blend mode on NULL texture");
    return;
  }
  SDL_SetTextureBlendMode(_texture, blend);
}

int Texture::Height() const
{
  return _height;
}

int Texture::Width() const
{
  return _width;
}

void Texture::SetHeight(int const height)
{
  _height = height;
}

void Texture::SetWidth(int const width)
{
  _width = width;
}
