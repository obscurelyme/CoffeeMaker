#include "Game/Scenes/TestBedScene.hpp"

#include <string>

#include "Color.hpp"
#include "Event.hpp"
#include "InputManager.hpp"
#include "Logger.hpp"
#include "Renderer.hpp"
#include "Widgets/Properties.hpp"

Sprite::Sprite(const std::string& filePath) : rotation(0), _texture(CreateScope<CoffeeMaker::Texture>(filePath)) {
  clientRect.w = _texture->Height();
  clientRect.h = _texture->Width();
  // clipRect = SDL_Rect{.x = 0, .y = 0, .w = 32, .h = 32};
}

Sprite::Sprite(const std::string& filePath, float width, float height) :
    rotation(0), _texture(CreateScope<CoffeeMaker::Texture>(filePath)) {
  clientRect.w = width;
  clientRect.h = height;
}

void Sprite::Render() { _texture->Render(clipRect, clientRect, rotation); }

TestPlayer::TestPlayer() : _rotation(0), _rotation2(0), _flip(SDL_FLIP_NONE) {
  _position.x = 400;
  _position.y = 300;
  _clientRect.x = _position.x;
  _clientRect.y = _position.y;
}

TestPlayer::~TestPlayer() {}

void TestPlayer::Render() {
  _texture.Render(_clipRect, _clientRect, _rotation, _flip);

  SDL_SetRenderDrawColor(CoffeeMaker::Renderer::Instance(), CoffeeMaker::Colors::Yellow.r,
                         CoffeeMaker::Colors::Yellow.g, CoffeeMaker::Colors::Yellow.b, CoffeeMaker::Colors::Yellow.a);
  SDL_RenderDrawLineF(CoffeeMaker::Renderer::Instance(), _position.x, _position.y, _randLookAt.x, _randLookAt.y);
  SDL_SetRenderDrawColor(CoffeeMaker::Renderer::Instance(), CoffeeMaker::Colors::Blue.r, CoffeeMaker::Colors::Blue.g,
                         CoffeeMaker::Colors::Blue.b, CoffeeMaker::Colors::Blue.a);

  // SDL_RenderDrawLineF(CoffeeMaker::Renderer::Instance(), _randLookAt.x, _position.y, _randLookAt.x, _randLookAt.y);
  // SDL_RenderDrawLineF(CoffeeMaker::Renderer::Instance(), _position.x, _position.y, _randLookAt.x, _position.y);

  SDL_RenderDrawLineF(CoffeeMaker::Renderer::Instance(), 800, 300, _randLookAt.x, _randLookAt.y);
  SDL_RenderDrawLineF(CoffeeMaker::Renderer::Instance(), _position.x, _position.y, 800, 300);
  SDL_SetRenderDrawColor(CoffeeMaker::Renderer::Instance(), CoffeeMaker::Colors::Red.r, CoffeeMaker::Colors::Red.g,
                         CoffeeMaker::Colors::Red.b, CoffeeMaker::Colors::Red.a);
  SDL_RenderDrawLineF(CoffeeMaker::Renderer::Instance(), 400, 0, 400, 600);
  SDL_RenderDrawLineF(CoffeeMaker::Renderer::Instance(), 0, 300, 800, 300);
}

void TestPlayer::Update(float deltaTime) {
  _rotation = 0;
  _movement.x = 0;
  _movement.y = 0;
  _timeout.Start();
  // _timeout.Act();
  if (CoffeeMaker::InputManager::IsKeyPressed(SDL_SCANCODE_LSHIFT)) {
  }

  if (CoffeeMaker::InputManager::IsKeyDown(SDL_SCANCODE_LEFT)) {
    _rotation += -8;
    _movement += CoffeeMaker::Math::Vector2D::Left();
  }

  if (CoffeeMaker::InputManager::IsKeyDown(SDL_SCANCODE_RIGHT)) {
    _rotation += 8;
    _movement += CoffeeMaker::Math::Vector2D::Right();
  }

  if (CoffeeMaker::InputManager::IsKeyDown(SDL_SCANCODE_UP)) {
    _movement += CoffeeMaker::Math::Vector2D::Down();
  }

  if (CoffeeMaker::InputManager::IsKeyDown(SDL_SCANCODE_DOWN)) {
    _movement += CoffeeMaker::Math::Vector2D::Up();
  }
  _position += CoffeeMaker::Math::Normalize(_movement) * deltaTime * 200;

  _clientRect.x = _position.x;
  _clientRect.y = _position.y;
}
void TestPlayer::Init() {}
void TestPlayer::Pause() {}
void TestPlayer::Unpause() {}

void TestPlayer::SetRotationText(Ref<CoffeeMaker::Widgets::Text> txt) { _text = txt; }

void TestPlayer::SetRotationText2(Ref<CoffeeMaker::Widgets::Text> txt) { _text2 = txt; }

void TestPlayer::SetRandomPointText(Ref<CoffeeMaker::Widgets::Text> txt) { _randText = txt; }

void TestPlayer::SetRandomPointText2(Ref<CoffeeMaker::Widgets::Text> txt) { _diffPointText = txt; }

void TestPlayer::LookAtRandomPoint() {
  // Note
  float x = CoffeeMaker::Math::Random(0.0f, 800.0f);
  float y = CoffeeMaker::Math::Random(0.0f, 600.0f);
  _randLookAt.x = x;
  _randLookAt.y = y;

  _rotation = CoffeeMaker::Math::rad2deg(_position.LookAt(_randLookAt)) + 90;

  _randText->SetText("(" + std::to_string(_randLookAt.x) + "," + std::to_string(_randLookAt.y) + ")");
  _text2->SetText(std::to_string(_rotation2));
  _text->SetText(std::to_string(_rotation));

  // _diffPointText->SetText("(" + std::to_string(diffX) + "," + std::to_string(diffY) + ")");
}

TestBedScene::TestBedScene() {
  _backgroundTiles = CreateScope<Tiles>("space.png", 800, 600);
  _view = CreateScope<CoffeeMaker::Widgets::View>(400, 150, CoffeeMaker::UIProperties::HorizontalAlignment::Centered,
                                                  CoffeeMaker::UIProperties::VerticalAlignment::Top);
  _text = CreateRef<CoffeeMaker::Widgets::Text>("0");
  _text->SetFont("Roboto/Roboto-Regular");
  _text->SetColor(CoffeeMaker::Colors::Yellow);
  _player = CreateScope<TestPlayer>();
  _player->SetRotationText(_text);
  _randomPointText = CreateRef<CoffeeMaker::Widgets::Text>("(0,0)");
  _randomPointText->SetFont("Roboto/Roboto-Regular");
  _randomPointText->SetColor(CoffeeMaker::Colors::Yellow);
  _randomPointText->SetHorizontalAlignment(CoffeeMaker::UIProperties::HorizontalAlignment::Right);
  _view->AppendChild(_randomPointText);
  _player->SetRandomPointText(_randomPointText);
  _text2 = CreateRef<CoffeeMaker::Widgets::Text>("0");
  _text2->SetFont("Roboto/Roboto-Regular");
  _text2->SetColor(CoffeeMaker::Colors::Yellow);
  _player->SetRotationText2(_text2);
  _text2->SetVerticalAlignment(CoffeeMaker::UIProperties::VerticalAlignment::Bottom);
  _view->AppendChild(_text2);

  _diffPointText = CreateRef<CoffeeMaker::Widgets::Text>("(0,0)");
  _text2->SetFont("Roboto/Roboto-Regular");
  _text2->SetColor(CoffeeMaker::Colors::Yellow);
  _player->SetRandomPointText2(_diffPointText);
  _diffPointText->SetVerticalAlignment(CoffeeMaker::UIProperties::VerticalAlignment::Bottom);
  _diffPointText->SetHorizontalAlignment(CoffeeMaker::UIProperties::HorizontalAlignment::Right);
  _diffPointText->SetFont("Roboto/Roboto-Regular");
  _diffPointText->SetColor(CoffeeMaker::Colors::Yellow);
  _view->AppendChild(_diffPointText);
}

void TestBedScene::Init() {
  _view->AppendChild(_text);
  _loaded = true;
}

void TestBedScene::Destroy() {
  _player.reset();
  _view.reset();
  _loaded = false;
}

void TestBedScene::Update(float deltaTime) {
  _backgroundTiles->Update(deltaTime);
  _player->Update(deltaTime);

  if (CoffeeMaker::InputManager::IsKeyPressed(SDL_SCANCODE_Q)) {
    Quit();
  }
}

void TestBedScene::Render() {
  _backgroundTiles->Render();
  _player->Render();
  _view->Render();
}

void TestBedScene::Pause() {}

void TestBedScene::Unpause() {}

void TestBedScene::Quit() { CoffeeMaker::PushCoffeeMakerEvent(CoffeeMaker::ApplicationEvents::COFFEEMAKER_GAME_QUIT); }
