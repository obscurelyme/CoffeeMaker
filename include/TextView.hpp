#ifndef _coffeemaker_textview_hpp
#define _coffeemaker_textview_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string>

#include "Color.hpp"
#include "Renderer.hpp"
#include "Widgets/Component.hpp"

namespace CoffeeMaker {
enum class TextAlignmentX {
  Centered,
  LeftAligned,
  RightAligned,
};

enum class TextAlignmentY {
  Centered,
  TopAligned,
  BottomAligned,
};

struct TextProperties {
  std::string &textContent;
  TextAlignmentX textAlignementX;
  TextAlignmentY textAlignmentY;
};

class TextView : public Component {
 public:
  TextView();
  TextView(std::string textContent);
  ~TextView();

  void Render();
  void SetFont(TTF_Font *f);
  void SetText(const std::string &textContent);
  void SetColor(const SDL_Color &color);
  void SetTextContentTexture();

  void SetXAlignment(TextAlignmentX xAlignment);
  void SetYAlignment(TextAlignmentY yAlignment);

  SDL_Color color;

 private:
  std::string _textContent;
  TTF_Font *_font;
  SDL_Renderer *renderer;
  SDL_Rect _textBoard;
  SDL_Texture *_texture;
  TextAlignmentX _xProps;
  TextAlignmentY _yProps;

  int DeriveXAxisPosition();
  int DeriveYAxisPosition();
};

}  // namespace CoffeeMaker

#endif
