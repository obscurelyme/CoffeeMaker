#ifndef _coffeemaker_texture_hpp
#define _coffeemaker_texture_hpp

#include <SDL2/SDL.h>
#include <string>
#include "Color.hpp"

namespace CoffeeMaker
{

  class Texture
  {
  public:
    Texture();
    explicit Texture(const std::string &filePath);
    explicit Texture(const SDL_Color &color);
    ~Texture();

    void LoadFromFile(const std::string &filePath);
    void SetColor(SDL_Color color = Color());
    void SetAlpha(Uint8 alpha);
    void SetBlendMode(SDL_BlendMode blend);
    void Render(int top, int left);
    /**
     * For use when the Texture's dimensions are controled by its parent
     */
    void Render(int top, int left, int height, int width);
    int Height() const;
    int Width() const;
    void SetHeight(int const height);
    void SetWidth(int const width);

    static void SetTextureDirectory();

  private:
    static std::string _textureDirectory;

    SDL_Texture *_texture;
    SDL_Color _color;
    int _height;
    int _width;
  };

}

#endif