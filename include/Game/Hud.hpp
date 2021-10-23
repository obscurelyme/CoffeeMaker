#ifndef _headsupdisplay_hpp
#define _headsupdisplay_hpp

#include <SDL2/SDL.h>

#include <string>

#include "Event.hpp"
#include "Timer.hpp"
#include "Utilities.hpp"
#include "Widgets/Text.hpp"
#include "Widgets/View.hpp"

class HeadsUpDisplay {
  public:
  HeadsUpDisplay();
  ~HeadsUpDisplay();

  void Update();
  void Render() const;
  void IncrementScore();
  void DecrementLife();
  void Pause();
  void Unpause();

  static void IncrementTimer(HeadsUpDisplay* instance);
  static Uint32 TimerInterval(Uint32 interval, void* params);

  private:
  unsigned int _score;
  unsigned int _life;
  CoffeeMaker::Delegate _incScoreDelegate{std::bind(&HeadsUpDisplay::IncrementScore, this)};
  CoffeeMaker::Delegate _decLifeDelegate{std::bind(&HeadsUpDisplay::DecrementLife, this)};

  Ref<CoffeeMaker::Widgets::Text> score;
  Ref<CoffeeMaker::Widgets::Text> playerHealth;
  Ref<CoffeeMaker::Widgets::Text> time;
  std::unique_ptr<CoffeeMaker::Widgets::View> hudView;
  CoffeeMaker::Timer _timer;
  SDL_TimerID _timerId;
};

#endif
