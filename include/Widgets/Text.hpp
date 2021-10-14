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

      void Render() override;
      std::string ID() const override;

      void SetFont(const std::string &fontName);
      void SetFont(TTF_Font *f);
      void SetText(const std::string &textContent);
      void SetColor(const SDL_Color &color);
      void SetWrapLength(Uint32 wrapLength);
      void OnAppend() override;
      Uint32 GetWrapLength() const;

      SDL_Color color;

      private:
      void SetTextContentTexture();

      std::string _componentId;
      std::string _textContent;
      TTF_Font *_font;
      SDL_Renderer *renderer;
      SDL_Texture *_texture;
      Uint32 _wrapLength;

      static int _textId;
    };
  }  // namespace Widgets

}  // namespace CoffeeMaker

#endif
