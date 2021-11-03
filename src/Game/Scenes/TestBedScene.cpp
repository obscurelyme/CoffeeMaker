#include "Game/Scenes/TestBedScene.hpp"

#include <string>

#include "Color.hpp"
#include "Event.hpp"
#include "InputManager.hpp"
#include "Logger.hpp"
#include "Renderer.hpp"
#include "Widgets/Properties.hpp"

TestEnemy::TestEnemy() :
    _sprite(CreateScope<CoffeeMaker::Sprite>("EnemyV1.png")),
    _rotation(0),
    _entranceSpline(CreateScope<Animations::EnemyEntrance>()),
    _exitSpline(CreateScope<Animations::EnemyExit>()),
    _exitTimeout(CreateScope<CoffeeMaker::Timeout>(12000,
                                                   [this]() {
                                                     if (_state == TestEnemy::State::StrafeLeft) {
                                                       _state = TestEnemy::State::WillExit_StrafeLeft;
                                                     }
                                                     if (_state == TestEnemy::State::StrafeRight) {
                                                       _state = TestEnemy::State::WillExit_StrafeRight;
                                                     }
                                                   })),
    _state(TestEnemy::State::Entering) {
  _position.x = 400;
  _position.y = 150;

  _sprite->clientRect.x = _position.x;
  _sprite->clientRect.y = _position.y;
  _sprite->clientRect.w = 48;
  _sprite->clientRect.h = 48;
  _entranceSpline->OnComplete([this](void*) {
    _state = TestEnemy::State::StrafeLeft;
    _exitTimeout->Start();
  });
}

TestEnemy::~TestEnemy() {}

void TestEnemy::Init() {}

void TestEnemy::Update(float deltaTime) {
  using Vec2 = CoffeeMaker::Math::Vector2D;

  if (CoffeeMaker::InputManager::IsKeyPressed(SDL_SCANCODE_R)) {
    _state = TestEnemy::State::Entering;
    _entranceSpline->Reset();
    _exitSpline->Reset();
  }

  switch (_state) {
    case TestEnemy::State::WillExit_StrafeLeft: {
      MoveLeft(deltaTime);
      if (_position.x <= 400) {
        _state = TestEnemy::State::Exiting;
      }
    } break;
    case TestEnemy::State::WillExit_StrafeRight: {
      MoveRight(deltaTime);
      if (_position.x >= 400) {
        _state = TestEnemy::State::Exiting;
      }
    } break;
    case TestEnemy::State::StrafeLeft: {
      MoveLeft(deltaTime);
    } break;
    case TestEnemy::State::StrafeRight: {
      MoveRight(deltaTime);
    } break;
    case TestEnemy::State::Entering: {
      _entranceSpline->Update(deltaTime);

      Vec2 currentPos = _entranceSpline->Position();

      _rotation = CoffeeMaker::Math::rad2deg(_position.LookAt(currentPos)) + 90;
      _position = currentPos;
    } break;
    case TestEnemy::State::Exiting: {
      _exitSpline->Update(deltaTime);
      Vec2 currentPos = _exitSpline->Position();

      _rotation = CoffeeMaker::Math::rad2deg(_position.LookAt(currentPos)) + 90;
      _position = currentPos;
    } break;
  }

  _sprite->rotation = _rotation;
  _sprite->SetPosition(_position);
}

void TestEnemy::Render() {
  // Render enemy sprite
  _sprite->Render();
  SDL_SetRenderDrawColor(CoffeeMaker::Renderer::Instance(), CoffeeMaker::Colors::Yellow.r,
                         CoffeeMaker::Colors::Yellow.g, CoffeeMaker::Colors::Yellow.b, CoffeeMaker::Colors::Yellow.a);
  SDL_RenderDrawLineF(CoffeeMaker::Renderer::Instance(), _position.x, _position.y, TestPlayer::Position().x,
                      TestPlayer::Position().y);
  // Debug Bezier Curve
  _entranceSpline->DebugRender();
  _exitSpline->DebugRender();
}
void TestEnemy::Pause() {}
void TestEnemy::Unpause() {}

void TestEnemy::MoveLeft(float deltaTime) {
  _rotation = 180;
  if (_position.x > 100 - _sprite->clientRect.w) {
    _position += CoffeeMaker::Math::Vector2D::Left() * 200 * deltaTime;
  } else {
    _state = TestEnemy::State::StrafeRight;
  }
}

void TestEnemy::MoveRight(float deltaTime) {
  _rotation = 180;
  if (_position.x < 700) {
    _position += CoffeeMaker::Math::Vector2D::Right() * 200 * deltaTime;
  } else {
    _state = TestEnemy::State::StrafeLeft;
  }
}

TestPlayer* TestPlayer::_instance = nullptr;
CoffeeMaker::Math::Vector2D& TestPlayer::Position() { return _instance->_position; }

TestPlayer::TestPlayer() : _sprite(CreateScope<CoffeeMaker::Sprite>("PlayerV1.png")), _rotation(0), _rotation2(0) {
  _position.x = 400;
  _position.y = 500;

  _sprite->clientRect.x = _position.x;
  _sprite->clientRect.y = _position.y;
  _sprite->clientRect.w = 48;
  _sprite->clientRect.h = 48;
  _instance = this;
  _timeout.Start();
}

TestPlayer::~TestPlayer() { _instance = nullptr; }

void TestPlayer::Render() {
  _sprite->Render();

  // SDL_SetRenderDrawColor(CoffeeMaker::Renderer::Instance(), CoffeeMaker::Colors::Yellow.r,
  //                        CoffeeMaker::Colors::Yellow.g, CoffeeMaker::Colors::Yellow.b,
  //                        CoffeeMaker::Colors::Yellow.a);
  // SDL_RenderDrawLineF(CoffeeMaker::Renderer::Instance(), _position.x, _position.y, _randLookAt.x, _randLookAt.y);
  // SDL_SetRenderDrawColor(CoffeeMaker::Renderer::Instance(), CoffeeMaker::Colors::Blue.r, CoffeeMaker::Colors::Blue.g,
  //                        CoffeeMaker::Colors::Blue.b, CoffeeMaker::Colors::Blue.a);
  // SDL_RenderDrawLineF(CoffeeMaker::Renderer::Instance(), 800, 300, _randLookAt.x, _randLookAt.y);
  // SDL_RenderDrawLineF(CoffeeMaker::Renderer::Instance(), _position.x, _position.y, 800, 300);
  SDL_SetRenderDrawColor(CoffeeMaker::Renderer::Instance(), CoffeeMaker::Colors::Red.r, CoffeeMaker::Colors::Red.g,
                         CoffeeMaker::Colors::Red.b, CoffeeMaker::Colors::Red.a);
  SDL_RenderDrawLineF(CoffeeMaker::Renderer::Instance(), 400, 0, 400, 600);
  SDL_RenderDrawLineF(CoffeeMaker::Renderer::Instance(), 0, 300, 800, 300);
}

void TestPlayer::Update(float deltaTime) {
  _rotation = 0;
  _movement.x = 0;
  _movement.y = 0;
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

  _sprite->rotation = _rotation;
  _sprite->SetPosition(_position);
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
  _enemy = CreateScope<TestEnemy>();
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
  _enemy.reset();
  _loaded = false;
}

void TestBedScene::Update(float deltaTime) {
  _backgroundTiles->Update(deltaTime);
  _player->Update(deltaTime);
  _enemy->Update(deltaTime);

  if (CoffeeMaker::InputManager::IsKeyPressed(SDL_SCANCODE_Q)) {
    Quit();
  }
}

void TestBedScene::Render() {
  _backgroundTiles->Render();
  _player->Render();
  _enemy->Render();
  _view->Render();
}

void TestBedScene::Pause() {}

void TestBedScene::Unpause() {}

void TestBedScene::Quit() { CoffeeMaker::PushCoffeeMakerEvent(CoffeeMaker::ApplicationEvents::COFFEEMAKER_GAME_QUIT); }
