#include "Widgets/Button.hpp"
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

Texture::Texture() : _texture(nullptr), _height(0), _width(0) {}

Texture::Texture(const std::string &filePath) : _texture(nullptr), _height(0), _width(0)
{
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

  _texture = SDL_CreateTextureFromSurface(CoffeeMaker::Renderer::Instance(), surface);
  _height = surface->h;
  _width = surface->w;
  SDL_FreeSurface(surface);
}

void Texture::Render(int top, int left)
{
  if (_texture == nullptr)
  {
    CoffeeMaker::Logger::Error("Could not render NULL texture");
    return;
  }
  SDL_Rect renderQuad = {.x = left, .y = top, .w = _width, .h = _height};
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
    Logger::Error("Could not set color on NULL texture");
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
