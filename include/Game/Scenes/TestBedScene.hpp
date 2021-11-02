#ifndef _testbedscene_hpp
#define _testbedscene_hpp

#include <SDL2/SDL.h>

#include <vector>

#include "Game/Entity.hpp"
#include "Game/Scene.hpp"
#include "Game/Tiles.hpp"
#include "Math.hpp"
#include "Sprite.hpp"
#include "Texture.hpp"
#include "Timer.hpp"
#include "Utilities.hpp"
#include "Widgets/Text.hpp"
#include "Widgets/View.hpp"

class Spline {
  using Vec2 = CoffeeMaker::Math::Vector2D;

  public:
  Spline();
  ~Spline() = default;

  /**
   * @brief Adds a curve to the spline.
   */
  void AddCurve(const Vec2&, const Vec2&, const Vec2&, const Vec2&);
  float Weight();
  Vec2 CurrentPosition();

  void Update(float deltaTime);
  void Start();

  private:
  std::vector<CoffeeMaker::Math::Vector2D> _spline;
  std::vector<CoffeeMaker::Math::Vector2D> _currentSlice;
  float _time;
  int _offset;
  float _currentTime;
  int _finalOffset;
  bool _complete;
  float _weight;
};

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

  static TestPlayer* _instance;
};

class TestEnemy : public Entity {
  public:
  TestEnemy();
  ~TestEnemy();
  virtual void Init();
  virtual void Update(float deltaTime = 0.0f);
  virtual void Render();
  virtual void Pause();
  virtual void Unpause();

  private:
  Scope<CoffeeMaker::Sprite> _sprite;
  double _rotation;
  CoffeeMaker::Math::Vector2D _movement;
  CoffeeMaker::Math::Vector2D _position;
  std::vector<CoffeeMaker::Math::Point2D> _trail;
  // float _currentTime;
  // float _totaltime;
  Scope<Spline> _spline;
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
  Scope<TestEnemy> _enemy;
  Scope<CoffeeMaker::Widgets::View> _view;
  Ref<CoffeeMaker::Widgets::Text> _text;
  Ref<CoffeeMaker::Widgets::Text> _text2;
  Ref<CoffeeMaker::Widgets::Text> _randomPointText;
  Ref<CoffeeMaker::Widgets::Text> _diffPointText;
};

#endif
