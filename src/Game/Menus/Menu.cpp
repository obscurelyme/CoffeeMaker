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
}

Menu::~Menu() {}

void Menu::Init() {
  // std::shared_ptr<Button> quit(new Button());
  std::shared_ptr<Button> returnToMain(new Button());
  returnToMain->SetTexture("test-button-background.png");
  std::shared_ptr<Text> returnToMainText(new Text());
  returnToMainText->SetFont(FontManager::UseFont("Roboto/Roboto-Regular"));
  returnToMainText->SetText("Return to Main Menu");
  returnToMainText->SetColor(Color(255, 255, 255, 255));
  // std::shared_ptr<Button> play(new Button());

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
    _view->Render();
  }
}
