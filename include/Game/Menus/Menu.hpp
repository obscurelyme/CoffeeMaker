#ifndef _menu_hpp
#define _menu_hpp

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
  bool _active;
  std::unique_ptr<View> _view;
};

#endif
