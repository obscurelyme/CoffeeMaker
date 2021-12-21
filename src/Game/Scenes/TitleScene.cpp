#include "Game/Scenes/TitleScene.hpp"

#include <SDL2/SDL.h>

#include <functional>
#include <memory>

#include "Color.hpp"
#include "Event.hpp"
#include "FontManager.hpp"
#include "Logger.hpp"
#include "Renderer.hpp"

void TitleScene::Render() {
  _backgroundSpaceTiles->Render();
  _backgroundSmokeTiles->Render();
  _backgroundNebulaTiles->Render();

  for (auto& entity : _entities) {
    entity->Render();
  }
}

void TitleScene::Update(float deltaTime) {
  _backgroundSpaceTiles->Update(deltaTime);
  _backgroundNebulaTiles->Update(deltaTime);
  _backgroundSmokeTiles->Update(deltaTime);
}

void TitleScene::Pause() {}

void TitleScene::Unpause() {}

void TitleScene::Init() {
  _music = CoffeeMaker::Audio::LoadMusic("music/CoolTrace.ogg");
  // CoffeeMaker::Audio::PlayMusic(_music);
  SDL_ShowCursor(SDL_ENABLE);

  _backgroundSpaceTiles =
      CreateScope<Tiles>("StarBackground-DarkBlue.png", CoffeeMaker::Renderer::GetOutputWidth(),
                         CoffeeMaker::Renderer::GetOutputHeight(), 15.0f, Tiles::ScrollDirection::Horizontal);
  _backgroundSmokeTiles =
      CreateScope<Tiles>("SpaceSmoke.png", CoffeeMaker::Renderer::GetOutputWidth(),
                         CoffeeMaker::Renderer::GetOutputHeight(), 25.0f, Tiles::ScrollDirection::Horizontal);
  _backgroundNebulaTiles =
      CreateScope<Tiles>("SpaceNebula-Bottom.png", CoffeeMaker::Renderer::GetOutputWidth(),
                         CoffeeMaker::Renderer::GetOutputHeight(), 50.0f, Tiles::ScrollDirection::Horizontal);
  float output = CoffeeMaker::Renderer::GetOutputHeightF();
  if (output > _backgroundNebulaTiles->Height()) {
    _backgroundNebulaTiles->SetYOffset(output - _backgroundNebulaTiles->Height());
    CM_LOGGER_DEBUG("Y-Offset: {}", output - _backgroundNebulaTiles->Height());
  }

  Ref<CoffeeMaker::Widgets::View> _view =
      CreateRef<CoffeeMaker::Widgets::View>(400, 200, HorizontalAlignment::Centered, VerticalAlignment::Centered);
  Ref<CoffeeMaker::Widgets::Text> _title = CreateRef<CoffeeMaker::Widgets::Text>();
  _title->SetFont(
      CoffeeMaker::FontManager::UseFont("Sarpanch/Sarpanch-Bold", CoffeeMaker::FontManager::FontSize::FontSizeLarge));
  _title->SetText("Ultra Cosmo Invaders");
  _title->SetColor(CoffeeMaker::Color(255, 255, 255, 255));
  _title->SetHorizontalAlignment(HorizontalAlignment::Centered);
  _title->SetVerticalAlignment(VerticalAlignment::Top);
  _title->SetMargins(CoffeeMaker::Margins{.top = 18.0f, .bottom = 0.0f, .left = 0.0f, .right = 0.0f});
  _view->AppendChild(_title);

  Ref<CoffeeMaker::Button> _playButton(new CoffeeMaker::Button("button.png", "button.png"));
  _playButton->SetVerticalAlignment(VerticalAlignment::Bottom);
  Ref<CoffeeMaker::Widgets::Text> _playButtonText = CreateRef<CoffeeMaker::Widgets::Text>();
  _playButtonText->SetHorizontalAlignment(HorizontalAlignment::Centered);
  _playButtonText->SetVerticalAlignment(VerticalAlignment::Centered);
  _playButtonText->SetFont(CoffeeMaker::FontManager::UseFont("Sarpanch/Sarpanch-Regular"));
  _playButtonText->SetColor(CoffeeMaker::Color(255, 255, 255, 255));
  _playButtonText->SetText("Play");
  _playButton->AppendChild(_playButtonText);
  _playButton->On(CoffeeMaker::Button::ButtonEventType::OnClick,
                  CoffeeMaker::Delegate{std::bind(&TitleScene::Play, this)});

  Ref<CoffeeMaker::Button> _quitButton(new CoffeeMaker::Button("button.png", "button.png"));
  _quitButton->SetHorizontalAlignment(HorizontalAlignment::Right);
  _quitButton->SetVerticalAlignment(VerticalAlignment::Bottom);
  Ref<CoffeeMaker::Widgets::Text> _quitButtonText = CreateRef<CoffeeMaker::Widgets::Text>();
  _quitButtonText->SetHorizontalAlignment(HorizontalAlignment::Centered);
  _quitButtonText->SetVerticalAlignment(VerticalAlignment::Centered);
  _quitButtonText->SetFont(CoffeeMaker::FontManager::UseFont("Sarpanch/Sarpanch-Regular"));
  _quitButtonText->SetColor(CoffeeMaker::Color(255, 255, 255, 255));
  _quitButtonText->SetText("Quit");
  _quitButton->AppendChild(_quitButtonText);
  _quitButton->On(CoffeeMaker::Button::ButtonEventType::OnClick,
                  CoffeeMaker::Delegate{std::bind(&TitleScene::Quit, this)});

  Ref<CoffeeMaker::Widgets::ScalableUISprite> panel =
      CreateRef<CoffeeMaker::Widgets::ScalableUISprite>("GlassPanel.png", 1.0f, 1.0f, 14, 14);

  _view->AppendChild(panel);
  _view->AppendChild(_playButton);
  _view->AppendChild(_quitButton);

  _playButton->SetMargins(CoffeeMaker::Margins{.top = 0.0f, .bottom = 18.0f, .left = 18.0f, .right = 0.0f});
  _quitButton->SetMargins(CoffeeMaker::Margins{.top = 0.0f, .bottom = 18.0f, .left = 0.0f, .right = 18.0f});

  _entities.push_back(_view);
  _loaded = true;
}

void TitleScene::Destroy() {
  // Clear out entities
  CoffeeMaker::Audio::StopMusic();
  CoffeeMaker::Audio::FreeMusic(_music);
  _backgroundNebulaTiles.reset();
  _backgroundSmokeTiles.reset();
  _backgroundSpaceTiles.reset();
  _music = nullptr;
  _entities.clear();
  _loaded = false;
}

void TitleScene::Play() { SceneManager::LoadScene(); }

void TitleScene::Quit() {
  Destroy();
  SDL_Event quit;
  quit.type = SDL_QUIT;
  SDL_PushEvent(&quit);
}
