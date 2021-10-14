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

  private:
  unsigned int _score;
  CoffeeMaker::Delegate _incScoreDelegate{std::bind(&HeadsUpDisplay::IncrementScore, this)};

  Ref<CoffeeMaker::Widgets::Text> score;
  Ref<CoffeeMaker::Widgets::Text> playerHealth;
  Ref<CoffeeMaker::Widgets::Text> time;
  std::unique_ptr<CoffeeMaker::Widgets::View> hudView;
};

#endif
