#include "Game/Scenes/HighScoreScene.hpp"

#include <SDL2/SDL.h>

#include <string>

#include "Event.hpp"
#include "Game/Scene.hpp"
#include "Game/ScoreManager.hpp"
#include "Logger.hpp"
#include "Renderer.hpp"
#include "Widgets/Button.hpp"
#include "Widgets/Properties.hpp"
#include "Widgets/Text.hpp"

int HighScoreScene::WIDTH = 400;
int HighScoreScene::HEIGHT = 300;

HighScoreScene::HighScoreScene() : _view(nullptr) {}

void HighScoreScene::Init() {
  SDL_ShowCursor(SDL_ENABLE);
  using Text = CoffeeMaker::Widgets::Text;
  using Button = CoffeeMaker::Button;
  using View = CoffeeMaker::Widgets::View;
  HighScores highScores = ScoreManager::GetHighScores();

  _view = CreateScope<View>(WIDTH, HEIGHT, CoffeeMaker::UIProperties::HorizontalAlignment::Centered,
                            CoffeeMaker::UIProperties::VerticalAlignment::Centered);
  Ref<Text> _firstPlaceHighScoreLabel = CreateRef<Text>("1st Place");
  _firstPlaceHighScoreLabel->SetFont("Sarpanch/Sarpanch-Bold");
  _firstPlaceHighScoreLabel->SetColor(SDL_Color{.r = 255, .g = 215, .b = 0, .a = 255});
  _firstPlaceHighScoreLabel->SetMargins(CoffeeMaker::Margins{.top = 0, .bottom = 0, .left = 0, .right = 0});
  Ref<Text> _firstPlaceScore = CreateRef<Text>(std::to_string(highScores.firstPlace));
  _firstPlaceScore->SetFont("Sarpanch/Sarpanch-Regular");
  _firstPlaceScore->SetMargins(CoffeeMaker::Margins{.top = 20, .bottom = 0, .left = 8, .right = 0});
  _firstPlaceScore->SetColor(CoffeeMaker::Colors::White);  // Gold

  Ref<Text> _secondPlaceHighScoreLabel = CreateRef<Text>("2nd Place");
  _secondPlaceHighScoreLabel->SetFont("Sarpanch/Sarpanch-Bold");
  _secondPlaceHighScoreLabel->SetMargins(CoffeeMaker::Margins{.top = 50, .bottom = 0, .left = 0, .right = 0});
  _secondPlaceHighScoreLabel->SetColor(SDL_Color{.r = 192, .g = 192, .b = 192, .a = 255});
  Ref<Text> _secondPlaceScore = CreateRef<Text>(std::to_string(highScores.secondPlace));
  _secondPlaceScore->SetFont("Sarpanch/Sarpanch-Regular");
  _secondPlaceScore->SetMargins(CoffeeMaker::Margins{.top = 70, .bottom = 0, .left = 8, .right = 0});
  _secondPlaceScore->SetColor(CoffeeMaker::Colors::White);  // Silver

  Ref<Text> _thirdPlaceHighScoreLabel = CreateRef<Text>("3rd Place");
  _thirdPlaceHighScoreLabel->SetFont("Sarpanch/Sarpanch-Bold");
  _thirdPlaceHighScoreLabel->SetMargins(CoffeeMaker::Margins{.top = 100, .bottom = 0, .left = 0, .right = 0});
  _thirdPlaceHighScoreLabel->SetColor(SDL_Color{.r = 205, .g = 127, .b = 50, .a = 255});
  Ref<Text> _thirdPlaceScore = CreateRef<Text>(std::to_string(highScores.thirdPlace));
  _thirdPlaceScore->SetFont("Sarpanch/Sarpanch-Regular");
  _thirdPlaceScore->SetMargins(CoffeeMaker::Margins{.top = 120, .bottom = 0, .left = 8, .right = 0});
  _thirdPlaceScore->SetColor(CoffeeMaker::Colors::White);  // Bronze

  Ref<Text> _currentSessionPlaceHighScoreLabel = CreateRef<Text>("Your score");
  _currentSessionPlaceHighScoreLabel->SetFont("Sarpanch/Sarpanch-Bold");
  _currentSessionPlaceHighScoreLabel->SetHorizontalAlignment(CoffeeMaker::UIProperties::HorizontalAlignment::Right);
  _currentSessionPlaceHighScoreLabel->SetMargins(CoffeeMaker::Margins{.top = 0, .bottom = 0, .left = -50, .right = 0});
  _currentSessionPlaceHighScoreLabel->SetColor(CoffeeMaker::Colors::Yellow);
  Ref<Text> _currentSessionPlaceScore = CreateRef<Text>(std::to_string(ScoreManager::GetScore()));
  _currentSessionPlaceScore->SetFont("Sarpanch/Sarpanch-Regular");
  _currentSessionPlaceScore->SetHorizontalAlignment(CoffeeMaker::UIProperties::HorizontalAlignment::Right);
  _currentSessionPlaceScore->SetMargins(CoffeeMaker::Margins{.top = 20, .bottom = 0, .left = -50, .right = 0});
  _currentSessionPlaceScore->SetColor(CoffeeMaker::Colors::White);

  _view->AppendChild(_firstPlaceHighScoreLabel);
  _view->AppendChild(_secondPlaceHighScoreLabel);
  _view->AppendChild(_thirdPlaceHighScoreLabel);
  _view->AppendChild(_firstPlaceScore);
  _view->AppendChild(_secondPlaceScore);
  _view->AppendChild(_thirdPlaceScore);
  _view->AppendChild(_currentSessionPlaceHighScoreLabel);
  _view->AppendChild(_currentSessionPlaceScore);

  Ref<Button> returnToMainMenuButton = CreateRef<Button>("button.png", "button.png");
  Ref<Text> returnToMainMenuButtonLabel = CreateRef<Text>("Main Menu");
  returnToMainMenuButtonLabel->SetFont("Sarpanch/Sarpanch-Regular");
  returnToMainMenuButtonLabel->SetHorizontalAlignment(CoffeeMaker::UIProperties::HorizontalAlignment::Centered);
  returnToMainMenuButtonLabel->SetVerticalAlignment(CoffeeMaker::UIProperties::VerticalAlignment::Centered);
  returnToMainMenuButtonLabel->SetColor(CoffeeMaker::Colors::White);
  returnToMainMenuButton->AppendChild(returnToMainMenuButtonLabel);
  Ref<Button> playAgainButton = CreateRef<Button>("button.png", "button.png");
  Ref<Text> playAgainButtonLabel = CreateRef<Text>("Play Again");
  playAgainButtonLabel->SetFont("Sarpanch/Sarpanch-Regular");
  playAgainButtonLabel->SetHorizontalAlignment(CoffeeMaker::UIProperties::HorizontalAlignment::Centered);
  playAgainButtonLabel->SetVerticalAlignment(CoffeeMaker::UIProperties::VerticalAlignment::Centered);
  playAgainButtonLabel->SetColor(CoffeeMaker::Colors::White);
  playAgainButton->AppendChild(playAgainButtonLabel);

  returnToMainMenuButton->SetHorizontalAlignment(CoffeeMaker::UIProperties::HorizontalAlignment::Right);
  playAgainButton->SetHorizontalAlignment(CoffeeMaker::UIProperties::HorizontalAlignment::Right);
  returnToMainMenuButton->SetVerticalAlignment(CoffeeMaker::UIProperties::VerticalAlignment::Bottom);
  playAgainButton->SetVerticalAlignment(CoffeeMaker::UIProperties::VerticalAlignment::Bottom);
  playAgainButton->SetMargins(CoffeeMaker::Margins{.top = -55, .bottom = 0, .left = -10, .right = 0});
  returnToMainMenuButton->SetMargins(CoffeeMaker::Margins{.top = 0, .bottom = 0, .left = -10, .right = 0});

  playAgainButton->On(Button::ButtonEventType::OnClick,
                      CoffeeMaker::Delegate{std::bind(&HighScoreScene::HandlePlayAgain, this)});
  returnToMainMenuButton->On(Button::ButtonEventType::OnClick,
                             CoffeeMaker::Delegate{std::bind(&HighScoreScene::HandleMainMenu, this)});

  _view->AppendChild(returnToMainMenuButton);
  _view->AppendChild(playAgainButton);
  _loaded = true;
}

void HighScoreScene::Update(float) {}

void HighScoreScene::Render() {
  SDL_SetRenderDrawColor(CoffeeMaker::Renderer::Instance(), 0, 0, 0, 0);
  SDL_RenderClear(CoffeeMaker::Renderer::Instance());
  _view->Render();
}

void HighScoreScene::Destroy() {
  _view.reset();
  _loaded = false;
}

void HighScoreScene::Pause() {}

void HighScoreScene::Unpause() {}

void HighScoreScene::HandlePlayAgain() { SceneManager::LoadScene(1); }

void HighScoreScene::HandleMainMenu() { SceneManager::LoadScene(0); }
