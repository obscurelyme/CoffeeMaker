#ifndef _coffeemaker_textview_hpp
#define _coffeemaker_textview_hpp

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Color.hpp"
#include "Renderer.hpp"
#include "Widgets/Component.hpp"

namespace CoffeeMaker
{
  class TextView : public Component
  {
  public:
    TextView();
    TextView(std::string textContent);
    ~TextView();

    void Render();
    void SetFont(TTF_Font *f);
    void SetText(const std::string &textContent);
    void SetColor(const SDL_Color& color);
    void SetTextContentTexture();

    SDL_Color color;

  private:
    std::string _textContent;
    TTF_Font *_font;
    SDL_Renderer *renderer;
    SDL_Rect _textBoard;
    SDL_Texture *_texture;
  };

} // namespace CoffeeMaker

#endif
