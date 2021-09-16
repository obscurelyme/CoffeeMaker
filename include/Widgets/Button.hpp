#ifndef _coffeemaker_button_hpp
#define _coffeemaker_button_hpp

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
    ~Texture();

    void LoadFromFile(const std::string &filePath);
    void SetColor(SDL_Color color = Color());
    void SetAlpha(Uint8 alpha);
    void SetBlendMode(SDL_BlendMode blend);
    void Render(int top, int left);
    int Height() const;
    int Width() const;
    void SetHeight(int const height);
    void SetWidth(int const width);

    static void SetTextureDirectory();

  private:
    static std::string _textureDirectory;

    SDL_Texture *_texture;
    int _height;
    int _width;
  };

  class Button
  {
  public:
    void Draw();

    void OnEvent(SDL_Event *e);
    void OnMouseover();
    void OnClick();
    void OnMouseleave();

    int top;
    int left;
    int width;
    int height;
    int padding;
    void *children;
    SDL_Rect _clientRect;
    Texture _texture;
  };

} // CoffeeMaker

#endif
