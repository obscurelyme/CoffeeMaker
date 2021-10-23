#include "Game/Scenes/TitleScene.hpp"

#include <SDL2/SDL.h>

#include <functional>
#include <memory>

#include "Color.hpp"
#include "Event.hpp"
#include "FontManager.hpp"
#include "Renderer.hpp"
#include "Widgets/Button.hpp"
#include "Widgets/Properties.hpp"
#include "Widgets/Text.hpp"

using namespace CoffeeMaker;
using namespace CoffeeMaker::UIProperties;
using namespace CoffeeMaker::Widgets;

void TitleScene::Render() {
  SDL_SetRenderDrawColor(Renderer::Instance(), _backgroundColor.r, _backgroundColor.g, _backgroundColor.b,
                         _backgroundColor.a);
  SDL_RenderClear(Renderer::Instance());
  for (auto& entity : _entities) {
    entity->Render();
  }
}

void TitleScene::Update(float) {}

void TitleScene::Pause() {}

void TitleScene::Unpause() {}

void TitleScene::Init() {
  _backgroundColor = Color(0, 0, 0, 255);  // Black
  std::shared_ptr<View> _view(new View(400, 200, HorizontalAlignment::Centered, VerticalAlignment::Centered));
  std::shared_ptr<Text> _title(new Text());
  _title->SetFont(FontManager::UseFont("Roboto/Roboto-Regular"));
  _title->SetText("Cheap Asteriods");
  _title->SetColor(Color(255, 255, 255, 255));
  _title->SetHorizontalAlignment(HorizontalAlignment::Centered);
  _title->SetVerticalAlignment(VerticalAlignment::Top);
  _view->AppendChild(_title);

  std::shared_ptr<Button> _playButton(new Button("test-button-background.png", "test-button-background-hovered.png"));
  _playButton->SetVerticalAlignment(VerticalAlignment::Bottom);
  std::shared_ptr<Text> _playButtonText(new Text());
  _playButtonText->SetHorizontalAlignment(HorizontalAlignment::Centered);
  _playButtonText->SetVerticalAlignment(VerticalAlignment::Centered);
  _playButtonText->SetFont(FontManager::UseFont("Roboto/Roboto-Regular"));
  _playButtonText->SetColor(Color(255, 255, 255, 255));
  _playButtonText->SetText("Play");
  _playButton->AppendChild(_playButtonText);
  _playButton->On(Button::ButtonEventType::OnClick, Delegate{std::bind(&TitleScene::Play, this)});

  std::shared_ptr<Button> _quitButton(new Button("test-button-background.png", "test-button-background-hovered.png"));
  _quitButton->SetHorizontalAlignment(HorizontalAlignment::Right);
  _quitButton->SetVerticalAlignment(VerticalAlignment::Bottom);
  std::shared_ptr<Text> _quitButtonText(new Text());
  _quitButtonText->SetHorizontalAlignment(HorizontalAlignment::Centered);
  _quitButtonText->SetVerticalAlignment(VerticalAlignment::Centered);
  _quitButtonText->SetFont(FontManager::UseFont("Roboto/Roboto-Regular"));
  _quitButtonText->SetColor(Color(255, 255, 255, 255));
  _quitButtonText->SetText("Quit");
  _quitButton->AppendChild(_quitButtonText);
  _quitButton->On(Button::ButtonEventType::OnClick, Delegate{std::bind(&TitleScene::Quit, this)});

  _view->AppendChild(_playButton);
  _view->AppendChild(_quitButton);

  _entities.push_back(_view);
}

void TitleScene::Destroy() {
  // Clear out entities
  _entities.clear();
}

void TitleScene::Play() { SceneManager::LoadScene(); }

void TitleScene::Quit() {
  Destroy();
  SDL_Event quit;
  quit.type = SDL_QUIT;
  SDL_PushEvent(&quit);
}
