#ifndef _coffeemaker_textview_hpp
#define _coffeemaker_textview_hpp

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

namespace CoffeeMaker
{

  SDL_Color Color(unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, unsigned char a = 255)
  {
    SDL_Color c{.r = r,
                .g = g,
                .b = b,
                .a = a};
    return c;
  }

  class TextView
  {
  public:
    TextView() : textContent(""), color(CoffeeMaker::Color()), renderer(nullptr), font(nullptr) {}
    TextView(std::string textContent) : textContent(textContent), color(CoffeeMaker::Color()), renderer(nullptr), font(nullptr) {}
    ~TextView() {}

    void AssignToRenderer(SDL_Renderer *sdlRenderer)
    {
      renderer = sdlRenderer;
    }

    void Render()
    {
      SDL_Surface *surface;
      SDL_Texture *texture;

      surface = TTF_RenderText_Blended(font, textContent.c_str(), color);
      texture = SDL_CreateTextureFromSurface(renderer, surface);

      textBoard.w = surface->w;
      textBoard.h = surface->h;
      textBoard.x = 0; // x - textBoard.w;
      textBoard.y = 0; // y - textBoard.h;

      SDL_FreeSurface(surface);
      SDL_RenderCopy(renderer, texture, NULL, &textBoard);
      SDL_DestroyTexture(texture);
    }

    void SetFont(TTF_Font *f)
    {
      font = f;
    }

    std::string textContent;
    SDL_Color color;
    TTF_Font *font;
    SDL_Renderer *renderer;
    SDL_Rect textBoard;
  };

} // namespace CoffeeMaker

#endif