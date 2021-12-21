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
  ScoreManager::SetNewHighScore(static_cast<unsigned int>(ScoreManager::CurrentScorePlacement()),
                                ScoreManager::GetScore());
  HighScores highScores = ScoreManager::GetHighScores();

  _backgroundSpaceTiles =
      CreateScope<Tiles>("StarBackground-DarkBlue.png", CoffeeMaker::Renderer::GetOutputWidth(),
                         CoffeeMaker::Renderer::GetOutputHeight(), 15.0f, Tiles::ScrollDirection::Horizontal);
  _backgroundSmokeTiles =
      CreateScope<Tiles>("SpaceSmoke.png", CoffeeMaker::Renderer::GetOutputWidth(),
                         CoffeeMaker::Renderer::GetOutputHeight(), 25.0f, Tiles::ScrollDirection::Horizontal);
  _backgroundNebulaTiles =
      CreateScope<Tiles>("SpaceNebula-Bottom.png", CoffeeMaker::Renderer::GetOutputWidth(),
                         CoffeeMaker::Renderer::GetOutputHeight(), 50.0f, Tiles::ScrollDirection::Horizontal);

  Ref<CoffeeMaker::Widgets::ScalableUISprite> panel =
      CreateRef<CoffeeMaker::Widgets::ScalableUISprite>("GlassPanel.png", 1.0f, 1.0f, 14, 14);

  _view = CreateScope<View>(WIDTH, HEIGHT, CoffeeMaker::UIProperties::HorizontalAlignment::Centered,
                            CoffeeMaker::UIProperties::VerticalAlignment::Centered);
  Ref<Text> _firstPlaceHighScoreLabel = CreateRef<Text>("1st Place");
  _firstPlaceHighScoreLabel->SetFont("Sarpanch/Sarpanch-Bold", CoffeeMaker::FontManager::FontSize::FontSizeMedium);
  _firstPlaceHighScoreLabel->SetColor(SDL_Color{.r = 255, .g = 215, .b = 0, .a = 255});
  _firstPlaceHighScoreLabel->SetMargins(CoffeeMaker::Margins{.top = 14, .bottom = 0, .left = 14, .right = 0});
  Ref<Text> _firstPlaceScore = CreateRef<Text>(std::to_string(highScores.firstPlace) + MarkNewHighScore(1));
  _firstPlaceScore->SetFont("Sarpanch/Sarpanch-Regular");
  _firstPlaceScore->SetMargins(CoffeeMaker::Margins{.top = 42, .bottom = 0, .left = 22, .right = 0});
  _firstPlaceScore->SetColor(CoffeeMaker::Colors::White);  // Gold

  Ref<Text> _secondPlaceHighScoreLabel = CreateRef<Text>("2nd Place");
  _secondPlaceHighScoreLabel->SetFont("Sarpanch/Sarpanch-Bold");
  _secondPlaceHighScoreLabel->SetMargins(CoffeeMaker::Margins{.top = 72, .bottom = 0, .left = 14, .right = 0});
  _secondPlaceHighScoreLabel->SetColor(SDL_Color{.r = 192, .g = 192, .b = 192, .a = 255});
  Ref<Text> _secondPlaceScore = CreateRef<Text>(std::to_string(highScores.secondPlace) + MarkNewHighScore(2));
  _secondPlaceScore->SetFont("Sarpanch/Sarpanch-Regular");
  _secondPlaceScore->SetMargins(CoffeeMaker::Margins{.top = 92, .bottom = 0, .left = 22, .right = 0});
  _secondPlaceScore->SetColor(CoffeeMaker::Colors::White);  // Silver

  Ref<Text> _thirdPlaceHighScoreLabel = CreateRef<Text>("3rd Place");
  _thirdPlaceHighScoreLabel->SetFont("Sarpanch/Sarpanch-Bold");
  _thirdPlaceHighScoreLabel->SetMargins(CoffeeMaker::Margins{.top = 122, .bottom = 0, .left = 14, .right = 0});
  _thirdPlaceHighScoreLabel->SetColor(SDL_Color{.r = 205, .g = 127, .b = 50, .a = 255});
  Ref<Text> _thirdPlaceScore = CreateRef<Text>(std::to_string(highScores.thirdPlace) + MarkNewHighScore(3));
  _thirdPlaceScore->SetFont("Sarpanch/Sarpanch-Regular");
  _thirdPlaceScore->SetMargins(CoffeeMaker::Margins{.top = 142, .bottom = 0, .left = 22, .right = 0});
  _thirdPlaceScore->SetColor(CoffeeMaker::Colors::White);  // Bronze

  Ref<Text> _currentSessionPlaceHighScoreLabel = CreateRef<Text>("Your score");
  _currentSessionPlaceHighScoreLabel->SetFont("Sarpanch/Sarpanch-Bold",
                                              CoffeeMaker::FontManager::FontSize::FontSizeLarge);
  _currentSessionPlaceHighScoreLabel->SetHorizontalAlignment(CoffeeMaker::UIProperties::HorizontalAlignment::Right);
  _currentSessionPlaceHighScoreLabel->SetMargins(CoffeeMaker::Margins{.top = 7, .bottom = 0, .left = 0, .right = 14});
  _currentSessionPlaceHighScoreLabel->SetColor(CoffeeMaker::Colors::Yellow);
  Ref<Text> _currentSessionPlaceScore = CreateRef<Text>(std::to_string(ScoreManager::GetScore()));
  _currentSessionPlaceScore->SetFont("Sarpanch/Sarpanch-Regular", CoffeeMaker::FontManager::FontSize::FontSizeMedium);
  _currentSessionPlaceScore->SetHorizontalAlignment(CoffeeMaker::UIProperties::HorizontalAlignment::Right);
  _currentSessionPlaceScore->SetMargins(CoffeeMaker::Margins{.top = 40, .bottom = 0, .left = 0, .right = 22});
  _currentSessionPlaceScore->SetColor(CoffeeMaker::Colors::White);

  _view->AppendChild(panel);
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
  playAgainButton->SetMargins(CoffeeMaker::Margins{.top = 0, .bottom = 70, .left = 0, .right = 24});
  returnToMainMenuButton->SetMargins(CoffeeMaker::Margins{.top = 0, .bottom = 14, .left = 0, .right = 24});

  playAgainButton->On(Button::ButtonEventType::OnClick,
                      CoffeeMaker::Delegate{std::bind(&HighScoreScene::HandlePlayAgain, this)});
  returnToMainMenuButton->On(Button::ButtonEventType::OnClick,
                             CoffeeMaker::Delegate{std::bind(&HighScoreScene::HandleMainMenu, this)});

  _view->AppendChild(returnToMainMenuButton);
  _view->AppendChild(playAgainButton);
  _loaded = true;

  ScoreManager::SaveHighScores();
}

void HighScoreScene::Update(float deltaTime) {
  _backgroundSpaceTiles->Update(deltaTime);
  _backgroundNebulaTiles->Update(deltaTime);
  _backgroundSmokeTiles->Update(deltaTime);
}

void HighScoreScene::Render() {
  _backgroundSpaceTiles->Render();
  _backgroundSmokeTiles->Render();
  _backgroundNebulaTiles->Render();
  _view->Render();
}

void HighScoreScene::Destroy() {
  _backgroundNebulaTiles.reset();
  _backgroundSmokeTiles.reset();
  _backgroundSpaceTiles.reset();
  _view.reset();
  _loaded = false;
}

void HighScoreScene::Pause() {}

void HighScoreScene::Unpause() {}

void HighScoreScene::HandlePlayAgain() { SceneManager::LoadScene(1); }

void HighScoreScene::HandleMainMenu() { SceneManager::LoadScene(0); }

std::string HighScoreScene::MarkNewHighScore(int place) {
  return (ScoreManager::CurrentScorePlacement() == place ? "*" : "");
}
