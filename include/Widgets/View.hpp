#ifndef _coffeemaker_view_hpp
#define _coffeemaker_view_hpp

#include "Component.hpp"

#include <SDL2/SDL.h>

namespace CoffeeMaker {

  namespace Widgets {

    enum class ViewXProps {
      CENTERED,
      LEFT_ALIGNED,
      RIGHT_ALIGNED
    };

    enum class ViewYProps {
      CENTERED,
      TOP_ALIGNED,
      BOTTOM_ALIGNED
    };

    class View : public Component {
      public:
        View(int width, int height, ViewXProps xProperties = ViewXProps::LEFT_ALIGNED, ViewYProps yProperties = ViewYProps::TOP_ALIGNED, int spacing = 0);
        ~View() = default;

        void Render();

        int spacing;

      private:
        int _DerivedXPosition();
        int _DerivedYPosition();

        ViewXProps _xProps;
        ViewYProps _yProps;
    };

  }

}

#endif
