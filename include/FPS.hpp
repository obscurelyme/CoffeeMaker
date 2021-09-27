#ifndef _coffeemaker_fps_hpp
#define _coffeemaker_fps_hpp

#include "Widgets/Text.hpp"
#include "Widgets/View.hpp"

using namespace CoffeeMaker::Widgets;

namespace CoffeeMaker {

  class FPS {
    public:
    FPS();
    ~FPS();

    void Update();
    void Render();

    private:
    View _view{50, 50};
    Text _text;
    unsigned int _countedFrames;
    const unsigned int _msInASecond = 1000;
    unsigned int _priorTime;
    unsigned int _currentTime;
  };

}  // namespace CoffeeMaker

#endif
