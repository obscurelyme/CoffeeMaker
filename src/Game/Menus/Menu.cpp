#include "Game/Menus/Menu.hpp"

#include "Color.hpp"
#include "Event.hpp"
#include "FontManager.hpp"
#include "Game/Scene.hpp"

Menu::Menu() : _active(false), _view(std::make_unique<View>()) {
  _view->clientRect.h = 500;
  _view->clientRect.w = 200;
  _view->SetHorizontalAlignment(HorizontalAlignment::Centered);
  _view->SetVerticalAlignment(VerticalAlignment::Centered);
  _renderer = CoffeeMaker::Renderer::Instance();
  _backgroundRect = SDL_FRect{.x = 0.0f,
                              .y = 0.0f,
                              .w = CoffeeMaker::Renderer::GetOutputWidthF(),
                              .h = CoffeeMaker::Renderer::GetOutputHeightF()};
  _backgroundColor = CoffeeMaker::Colors::Black;
  _backgroundColor.a = 100;
}

Menu::~Menu() {
  _active = false;
  int s = SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_NONE);
  if (s != 0) {
    CM_LOGGER_CRITICAL("Error setting SDL Draw Blend Mode to NONE in Menu Destructor: {}", SDL_GetError());
  }
}

void Menu::Init() {
  std::shared_ptr<Button> returnToMain(new Button("button.png", "button.png"));
  returnToMain->SetHorizontalAlignment(HorizontalAlignment::Centered);
  returnToMain->SetVerticalAlignment(VerticalAlignment::Centered);
  std::shared_ptr<Text> returnToMainText(new Text("Main Menu"));
  returnToMainText->SetFont(FontManager::UseFont("Sarpanch/Sarpanch-Regular"));
  returnToMainText->SetColor(Color(255, 255, 255, 255));
  returnToMainText->SetHorizontalAlignment(HorizontalAlignment::Centered);
  returnToMainText->SetVerticalAlignment(VerticalAlignment::Centered);

  returnToMain->On(Button::ButtonEventType::OnClick, Delegate{std::bind(&Menu::ReturnToTitleScene, this)});

  _view->AppendChild(returnToMain);
  returnToMain->AppendChild(returnToMainText);
}

void Menu::ReturnToTitleScene() {
  Hide();
  SceneManager::LoadScene(0);
}

void Menu::Hide() { _active = false; }

void Menu::Show() { _active = true; }

bool Menu::IsShown() { return _active; }

void Menu::Render() {
  if (_active) {
    RenderTransparentBackground();
    _view->Render();
  }
}

void Menu::RenderTransparentBackground() {
  int s = SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);
  if (s != 0) {
    CM_LOGGER_CRITICAL("Error setting SDL Draw Blend Mode to BLEND: {}", SDL_GetError());
  }

  SDL_SetRenderDrawColor(_renderer, _backgroundColor.r, _backgroundColor.g, _backgroundColor.b, _backgroundColor.a);
  SDL_RenderFillRectF(_renderer, &_backgroundRect);

  s = SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_NONE);
  if (s != 0) {
    CM_LOGGER_CRITICAL("Error setting SDL Draw Blend Mode to NONE: {}", SDL_GetError());
  }
}
