#ifndef _coffeemaker_view_hpp
#define _coffeemaker_view_hpp

#include <SDL2/SDL.h>

#include "Properties.hpp"
#include "Widgets/UIComponent.hpp"

using namespace CoffeeMaker::UIProperties;

namespace CoffeeMaker {

  namespace Widgets {

    class View : public UIComponent {
      public:
      View();
      View(int width, int height, HorizontalAlignment xAlign = HorizontalAlignment::Left,
           VerticalAlignment yAlign = VerticalAlignment::Top, int spacing = 0);
      View(float widthPercent, float heightPercent, HorizontalAlignment xAlign = HorizontalAlignment::Left,
           VerticalAlignment yAlign = VerticalAlignment::Top, int spacing = 0);
      View(float widthPercent, int heightPercent, HorizontalAlignment xAlign = HorizontalAlignment::Left,
           VerticalAlignment yAlign = VerticalAlignment::Top, int spacing = 0);
      View(int widthPercent, float heightPercent, HorizontalAlignment xAlign = HorizontalAlignment::Left,
           VerticalAlignment yAlign = VerticalAlignment::Top, int spacing = 0);
      ~View() = default;

      void Render();

      int spacing;
    };

  }  // namespace Widgets

}  // namespace CoffeeMaker

#endif
