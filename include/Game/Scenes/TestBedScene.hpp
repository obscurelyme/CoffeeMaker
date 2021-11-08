#ifndef _testbedscene_hpp
#define _testbedscene_hpp

#include <SDL2/SDL.h>

#include <vector>

#include "Audio.hpp"
#include "Game/Animations/EnemyAnimations.hpp"
#include "Game/Entity.hpp"
#include "Game/Scene.hpp"
#include "Game/Tiles.hpp"
#include "Math.hpp"
#include "Spline.hpp"
#include "Sprite.hpp"
#include "Texture.hpp"
#include "Timer.hpp"
#include "Utilities.hpp"
#include "Widgets/Text.hpp"
#include "Widgets/View.hpp"

class TestPlayer : public Entity {
  public:
  TestPlayer();
  ~TestPlayer();

  static CoffeeMaker::Math::Vector2D& Position();

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
  Scope<CoffeeMaker::Sprite> _sprite;
  CoffeeMaker::Math::Vector2D _position;
  CoffeeMaker::Math::Vector2D _movement;
  CoffeeMaker::Math::Vector2D _randLookAt;
  Ref<CoffeeMaker::Widgets::Text> _text;
  Ref<CoffeeMaker::Widgets::Text> _text2;
  Ref<CoffeeMaker::Widgets::Text> _diffPointText;
  Ref<CoffeeMaker::Widgets::Text> _randText;
  CoffeeMaker::Timeout _timeout{5000, std::bind(&TestPlayer::LookAtRandomPoint, this)};
  double _rotation;
  double _rotation2;
  Scope<CoffeeMaker::AudioElement> _sound;

  static TestPlayer* _instance;
};

class TestEnemy : public Entity {
  public:
  enum class State {
    Entering,
    StrafeRight,
    StrafeLeft,
    WillExit_StrafeLeft,
    WillExit_StrafeRight,
    Exiting,
  };

  public:
  TestEnemy();
  ~TestEnemy();
  virtual void Init();
  virtual void Update(float deltaTime = 0.0f);
  virtual void Render();
  virtual void Pause();
  virtual void Unpause();

  private:
  void AnimateEntrance();
  void AnimateExit();

  void MoveLeft(float deltaTime = 0.0f);
  void MoveRight(float deltaTime = 0.0f);

  Scope<CoffeeMaker::Sprite> _sprite;
  double _rotation;
  CoffeeMaker::Math::Vector2D _movement;
  CoffeeMaker::Math::Vector2D _position;
  Scope<Animations::EnemyEntrance> _entranceSpline;
  Scope<Animations::EnemyExit> _exitSpline;
  Scope<CoffeeMaker::Timeout> _exitTimeout;
  State _state;
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
  virtual void OnEvent(Sint32 type, void* data1 = nullptr, void* data2 = nullptr) override;

  private:
  void Quit();

  Scope<Tiles> _backgroundTiles;
  Scope<TestPlayer> _player;
  Scope<TestEnemy> _enemy;
  Scope<CoffeeMaker::Widgets::View> _view;
  Ref<CoffeeMaker::Widgets::Text> _text;
  Ref<CoffeeMaker::Widgets::Text> _text2;
  Ref<CoffeeMaker::Widgets::Text> _randomPointText;
  Ref<CoffeeMaker::Widgets::Text> _diffPointText;
};

#endif
