#include "Game/Hud.hpp"

#include <SDL2/SDL.h>

#include <functional>

#include "Color.hpp"
#include "Event.hpp"
#include "FontManager.hpp"
#include "Game/Events.hpp"
#include "Logger.hpp"
#include "Renderer.hpp"
#include "Widgets/Properties.hpp"

class IntervalFunction {
  public:
  explicit IntervalFunction(SDL_TimerCallback fn, Uint32 i) : interval(i), callback(fn) {}

  ~IntervalFunction();

  void Invoke() const { SDL_AddTimer(interval, callback, nullptr); }

  Uint32 interval;

  SDL_TimerCallback callback;
};

HeadsUpDisplay::HeadsUpDisplay() : _score(0), _life(3) {
  using Text = CoffeeMaker::Widgets::Text;
  using View = CoffeeMaker::Widgets::View;
  using namespace CoffeeMaker::UIProperties;
  using FontSize = CoffeeMaker::FontManager::FontSize;
  using Margins = CoffeeMaker::Margins;

  score = CreateRef<Text>("Score: 0");
  time = CreateRef<Text>("Time: 0:00");
  playerHealth = CreateRef<Text>("Lives: " + std::to_string(_life));

  if (CoffeeMaker::Renderer::GetOutputWidth() >= 1920) {
    score->SetFont("Sarpanch/Sarpanch-Regular", FontSize::FontSizeLarge);
    time->SetFont("Sarpanch/Sarpanch-Regular", FontSize::FontSizeLarge);
    playerHealth->SetFont("Sarpanch/Sarpanch-Regular", FontSize::FontSizeLarge);
  } else {
    score->SetFont("Sarpanch/Sarpanch-Regular");
    time->SetFont("Sarpanch/Sarpanch-Regular");
    playerHealth->SetFont("Sarpanch/Sarpanch-Regular");
  }

  hudView = CreateScope<View>(0.9f, 50, HorizontalAlignment::Centered);
  score->SetColor(CoffeeMaker::Colors::Yellow);
  time->SetColor(CoffeeMaker::Colors::Yellow);
  playerHealth->SetColor(CoffeeMaker::Colors::Yellow);

  score->SetHorizontalAlignment(HorizontalAlignment::Centered);
  time->SetMargins(Margins{.top = 0.0f, .left = 18.0f, .right = 0.0f, .bottom = 0.0f});
  time->SetHorizontalAlignment(HorizontalAlignment::Left);
  playerHealth->SetHorizontalAlignment(HorizontalAlignment::Right);
  score->SetVerticalAlignment(VerticalAlignment::Centered);
  time->SetVerticalAlignment(VerticalAlignment::Centered);
  playerHealth->SetVerticalAlignment(VerticalAlignment::Centered);
  playerHealth->SetMargins(Margins{.top = 0.0f, .left = 0.0f, .right = 18.0f, .bottom = 0.0f});

  panel = CreateRef<CoffeeMaker::Widgets::ScalableUISprite>("GlassPanel.png", 1.0f, 1.0f, 14, 14);

  hudView->AppendChild(panel);
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

void HeadsUpDisplay::Render() const {
  hudView->Render();
  // bottomPanel->Render();
}

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
