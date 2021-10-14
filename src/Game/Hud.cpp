#include "Game/Hud.hpp"

#include "Color.hpp"
#include "Event.hpp"
#include "Game/PlayerEvents.hpp"
#include "Widgets/Properties.hpp"

using namespace CoffeeMaker::Widgets;
using namespace CoffeeMaker::UIProperties;

HeadsUpDisplay::HeadsUpDisplay() : _score(0) {
  score = std::make_shared<Text>("Score: 0");
  time = std::make_shared<Text>("Time: 0");
  playerHealth = std::make_shared<Text>("Lives: 3");
  score->SetFont("Roboto/Roboto-Regular");
  time->SetFont("Roboto/Roboto-Regular");
  playerHealth->SetFont("Roboto/Roboto-Regular");
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

  incScore->AddListener(_incScoreDelegate);
}

HeadsUpDisplay::~HeadsUpDisplay() { incScore->RemoveListener(_incScoreDelegate); }

void HeadsUpDisplay::Render() const { hudView->Render(); }

void HeadsUpDisplay::IncrementScore() {
  _score += 10;
  score->SetText("Score: " + std::to_string(_score));
}
