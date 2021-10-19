#ifndef _headsupdisplay_hpp
#define _headsupdisplay_hpp

#include <string>

#include "Event.hpp"
#include "Utilities.hpp"
#include "Widgets/Text.hpp"
#include "Widgets/View.hpp"

class HeadsUpDisplay {
  public:
  HeadsUpDisplay();
  ~HeadsUpDisplay();

  void Render() const;
  void IncrementScore();
  void DecrementLife();

  private:
  unsigned int _score;
  unsigned int _life;
  CoffeeMaker::Delegate _incScoreDelegate{std::bind(&HeadsUpDisplay::IncrementScore, this)};
  CoffeeMaker::Delegate _decLifeDelegate{std::bind(&HeadsUpDisplay::DecrementLife, this)};

  Ref<CoffeeMaker::Widgets::Text> score;
  Ref<CoffeeMaker::Widgets::Text> playerHealth;
  Ref<CoffeeMaker::Widgets::Text> time;
  std::unique_ptr<CoffeeMaker::Widgets::View> hudView;
};

#endif
