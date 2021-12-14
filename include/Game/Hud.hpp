#ifndef _headsupdisplay_hpp
#define _headsupdisplay_hpp

#include <SDL2/SDL.h>

#include <string>

#include "Event.hpp"
#include "Timer.hpp"
#include "Utilities.hpp"
#include "Widgets/ScalableUISprite.hpp"
#include "Widgets/Text.hpp"
#include "Widgets/View.hpp"

class HeadsUpDisplayEvent {
  public:
  static void Emit();
  static void AddListener();
  static void RemoveListener();
};

class HeadsUpDisplay : public CoffeeMaker::IUserEventListener {
  public:
  HeadsUpDisplay();
  ~HeadsUpDisplay();

  void Update();
  void Render() const;
  void IncrementScore();
  void DecrementLife();
  void Pause();
  void Unpause();

  void OnSDLUserEvent(const SDL_UserEvent& event);

  void IncrementTimer();
  static Uint32 TimerInterval(Uint32 interval, void* params);

  private:
  unsigned int _score;
  unsigned int _life;

  Ref<CoffeeMaker::Widgets::Text> score;
  Ref<CoffeeMaker::Widgets::Text> playerHealth;
  Ref<CoffeeMaker::Widgets::Text> time;
  Scope<CoffeeMaker::Widgets::View> hudView;
  Ref<CoffeeMaker::Widgets::ScalableUISprite> panel;
  CoffeeMaker::Timer _timer;
  SDL_TimerID _timerId;
};

#endif
