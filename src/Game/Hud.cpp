#include "Game/Hud.hpp"

#include <SDL2/SDL.h>

#include <functional>

#include "Color.hpp"
#include "Event.hpp"
#include "Game/Events.hpp"
#include "Logger.hpp"
#include "Widgets/Properties.hpp"

using namespace CoffeeMaker::Widgets;
using namespace CoffeeMaker::UIProperties;

class IntervalFunction {
  public:
  explicit IntervalFunction(SDL_TimerCallback fn, Uint32 i) : interval(i), callback(fn) {}

  ~IntervalFunction();

  void Invoke() const { SDL_AddTimer(interval, callback, nullptr); }

  Uint32 interval;

  SDL_TimerCallback callback;
};

HeadsUpDisplay::HeadsUpDisplay() : _score(0), _life(3) {
  score = std::make_shared<Text>("Score: 0");
  time = std::make_shared<Text>("Time: 0:00");
  playerHealth = std::make_shared<Text>("Lives: " + std::to_string(_life));
  score->SetFont("Sarpanch/Sarpanch-Regular");
  time->SetFont("Sarpanch/Sarpanch-Regular");
  playerHealth->SetFont("Sarpanch/Sarpanch-Regular");
  hudView = std::make_unique<View>(800, 50);
  score->SetColor(CoffeeMaker::Colors::Yellow);
  time->SetColor(CoffeeMaker::Colors::Yellow);
  playerHealth->SetColor(CoffeeMaker::Colors::Yellow);

  score->SetHorizontalAlignment(HorizontalAlignment::Left);
  time->SetHorizontalAlignment(HorizontalAlignment::Centered);
  playerHealth->SetHorizontalAlignment(HorizontalAlignment::Right);
  score->SetVerticalAlignment(VerticalAlignment::Centered);
  time->SetVerticalAlignment(VerticalAlignment::Centered);
  playerHealth->SetVerticalAlignment(VerticalAlignment::Centered);

  hudView->AppendChild(score);
  hudView->AppendChild(time);
  hudView->AppendChild(playerHealth);

  _timer.Start();
  _timerId = SDL_AddTimer(1000, &HeadsUpDisplay::TimerInterval, this);
}

void HeadsUpDisplay::Pause() { _timer.Pause(); }

void HeadsUpDisplay::Unpause() { _timer.Unpause(); }

Uint32 HeadsUpDisplay::TimerInterval(Uint32 interval, void*) {
  CoffeeMaker::PushUserEvent(UCI::Events::HEADS_UP_DISPLAY_INCREMENT_TIMER);
  return interval;
}

HeadsUpDisplay::~HeadsUpDisplay() {
  SDL_RemoveTimer(_timerId);
  _timer.Stop();
}

void HeadsUpDisplay::Update() {
  // TODO: reassign the timer view every second
  // time->SetText(_timer.toString());
}

void HeadsUpDisplay::Render() const { hudView->Render(); }

void HeadsUpDisplay::IncrementScore() {
  _score += 10;
  score->SetText("Score: " + std::to_string(_score));
}

void HeadsUpDisplay::DecrementLife() {
  --_life;
  playerHealth->SetText("Life: " + std::to_string(_life));
}

void HeadsUpDisplay::IncrementTimer() { time->SetText("Time: " + _timer.toString()); }

void HeadsUpDisplay::OnSDLUserEvent(const SDL_UserEvent& event) {
  if (event.type == UCI::Events::HEADS_UP_DISPLAY_INCREMENT_TIMER) {
    IncrementTimer();
  }

  if (event.type == UCI::Events::PLAYER_INCREMENT_SCORE) {
    IncrementScore();
  }

  if (event.type == UCI::Events::PLAYER_LOST_LIFE) {
    DecrementLife();
  }
}
