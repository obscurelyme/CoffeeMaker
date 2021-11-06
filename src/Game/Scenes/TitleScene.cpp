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
  _music = CoffeeMaker::Audio::LoadMusic("music/CoolTrace.ogg");
  CoffeeMaker::Audio::PlayMusic(_music);
  SDL_ShowCursor(SDL_ENABLE);
  _backgroundColor = Color(0, 0, 0, 255);
  Ref<View> _view(new View(400, 200, HorizontalAlignment::Centered, VerticalAlignment::Centered));
  Ref<Text> _title(new Text());
  _title->SetFont(FontManager::UseFont("Sarpanch/Sarpanch-Bold"));
  _title->SetText("Ultra Cosmo Invaders");
  _title->SetColor(Color(255, 255, 255, 255));
  _title->SetHorizontalAlignment(HorizontalAlignment::Centered);
  _title->SetVerticalAlignment(VerticalAlignment::Top);
  _view->AppendChild(_title);

  Ref<Button> _playButton(new Button("button.png", "button.png"));
  _playButton->SetVerticalAlignment(VerticalAlignment::Bottom);
  Ref<Text> _playButtonText(new Text());
  _playButtonText->SetHorizontalAlignment(HorizontalAlignment::Centered);
  _playButtonText->SetVerticalAlignment(VerticalAlignment::Centered);
  _playButtonText->SetFont(FontManager::UseFont("Sarpanch/Sarpanch-Regular"));
  _playButtonText->SetColor(Color(255, 255, 255, 255));
  _playButtonText->SetText("Play");
  _playButton->AppendChild(_playButtonText);
  _playButton->On(Button::ButtonEventType::OnClick, Delegate{std::bind(&TitleScene::Play, this)});

  Ref<Button> _quitButton(new Button("button.png", "button.png"));
  _quitButton->SetHorizontalAlignment(HorizontalAlignment::Right);
  _quitButton->SetVerticalAlignment(VerticalAlignment::Bottom);
  Ref<Text> _quitButtonText(new Text());
  _quitButtonText->SetHorizontalAlignment(HorizontalAlignment::Centered);
  _quitButtonText->SetVerticalAlignment(VerticalAlignment::Centered);
  _quitButtonText->SetFont(FontManager::UseFont("Sarpanch/Sarpanch-Regular"));
  _quitButtonText->SetColor(Color(255, 255, 255, 255));
  _quitButtonText->SetText("Quit");
  _quitButton->AppendChild(_quitButtonText);
  _quitButton->On(Button::ButtonEventType::OnClick, Delegate{std::bind(&TitleScene::Quit, this)});

  _view->AppendChild(_playButton);
  _view->AppendChild(_quitButton);

  _entities.push_back(_view);
  _loaded = true;
}

void TitleScene::Destroy() {
  // Clear out entities
  CoffeeMaker::Audio::StopMusic();
  CoffeeMaker::Audio::FreeMusic(_music);
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

void TitleScene::OnEvent(Sint32, void*, void*) {}
