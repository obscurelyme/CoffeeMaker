#ifndef _coffeemaker_textview_hpp
#define _coffeemaker_textview_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string>

#include "Color.hpp"
#include "Renderer.hpp"
#include "Widgets/UIComponent.hpp"

namespace CoffeeMaker {
  namespace Widgets {
    class Text : public UIComponent {
      public:
      Text();
      explicit Text(std::string textContent);
      ~Text();

      void Render();
      void SetFont(TTF_Font *f);
      void SetText(const std::string &textContent);
      void SetColor(const SDL_Color &color);
      void SetTextContentTexture();

      SDL_Color color;

      private:
      std::string _id;
      std::string _textContent;
      TTF_Font *_font;
      SDL_Renderer *renderer;
      SDL_Texture *_texture;

      static int _textId;
    };
  }  // namespace Widgets

}  // namespace CoffeeMaker

#endif
