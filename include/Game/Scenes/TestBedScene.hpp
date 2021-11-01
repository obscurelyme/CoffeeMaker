#ifndef _testbedscene_hpp
#define _testbedscene_hpp

#include "Game/Entity.hpp"
#include "Game/Scene.hpp"
#include "Game/Tiles.hpp"
#include "Math.hpp"
#include "Timer.hpp"
#include "Utilities.hpp"
#include "Widgets/Text.hpp"
#include "Widgets/View.hpp"

class TestPlayer : public Entity {
  public:
  TestPlayer();
  ~TestPlayer();

  virtual void Init();
  virtual void Update(float deltaTime = 0.0f);
  virtual void Render();
  virtual void Pause();
  virtual void Unpause();

  void SetRotationText(Ref<CoffeeMaker::Widgets::Text> txt);
  void SetRotationText2(Ref<CoffeeMaker::Widgets::Text> txt);
  void SetRandomPointText(Ref<CoffeeMaker::Widgets::Text> txt);
  void SetRandomPointText2(Ref<CoffeeMaker::Widgets::Text> txt);
  void LookAtRandomPoint();

  private:
  CoffeeMaker::Texture _texture{"PlayerV1.png", true};
  SDL_Rect _clipRect{.x = 0, .y = 0, .w = 32, .h = 32};
  SDL_FRect _clientRect{.x = 0, .y = 0, .w = 48, .h = 48};
  CoffeeMaker::Math::Vector2D _position;
  CoffeeMaker::Math::Vector2D _randLookAt;
  Ref<CoffeeMaker::Widgets::Text> _text;
  Ref<CoffeeMaker::Widgets::Text> _text2;
  Ref<CoffeeMaker::Widgets::Text> _diffPointText;
  Ref<CoffeeMaker::Widgets::Text> _randText;
  CoffeeMaker::Timeout _timeout{5000, std::bind(&TestPlayer::LookAtRandomPoint, this)};
  double _rotation;
  double _rotation2;
  SDL_RendererFlip _flip;
};

class TestBedScene : public Scene {
  public:
  TestBedScene();
  ~TestBedScene() = default;

  virtual void Render() override;
  virtual void Update(float deltaTime) override;
  virtual void Init() override;
  virtual void Destroy() override;
  virtual void Pause() override;
  virtual void Unpause() override;

  private:
  void Quit();

  Scope<Tiles> _backgroundTiles;
  Scope<TestPlayer> _player;
  Scope<CoffeeMaker::Widgets::View> _view;
  Ref<CoffeeMaker::Widgets::Text> _text;
  Ref<CoffeeMaker::Widgets::Text> _text2;
  Ref<CoffeeMaker::Widgets::Text> _randomPointText;
  Ref<CoffeeMaker::Widgets::Text> _diffPointText;
};

#endif
