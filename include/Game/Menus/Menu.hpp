#ifndef _menu_hpp
#define _menu_hpp

#include <SDL2/SDL.h>

#include <memory>

#include "Widgets/Button.hpp"
#include "Widgets/Text.hpp"
#include "Widgets/View.hpp"

using namespace CoffeeMaker;
using namespace CoffeeMaker::Widgets;

class Menu {
  public:
  Menu();
  ~Menu();

  void Show();
  void Hide();
  void Init();
  void Destroy();
  void Render();
  bool IsShown();

  void ReturnToTitleScene();

  private:
  void RenderTransparentBackground();

  bool _active;
  std::unique_ptr<View> _view;
  SDL_FRect _backgroundRect;
  SDL_Color _backgroundColor;
  SDL_Renderer* _renderer;
};

#endif
