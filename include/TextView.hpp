#ifndef _coffeemaker_textview_hpp
#define _coffeemaker_textview_hpp

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Color.hpp"
#include "Renderer.hpp"

namespace CoffeeMaker
{
  class TextView
  {
  public:
    TextView() : textContent(""), color(CoffeeMaker::Color()), font(nullptr), renderer(CoffeeMaker::Renderer::Instance()) {}
    TextView(std::string textContent) : textContent(textContent), color(CoffeeMaker::Color()), font(nullptr), renderer(CoffeeMaker::Renderer::Instance()) {}
    ~TextView() {}

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
