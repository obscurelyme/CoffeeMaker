#include "Game/Animations/EnemyAnimations.hpp"

//------------------------------------------------------------------------------------------
//----- BaseSplineAnimation ----------------------------------------------------------------
//------------------------------------------------------------------------------------------

Animations::BaseSplineAnimation::BaseSplineAnimation(float animationDuration) :
    _spline(CreateScope<CoffeeMaker::Spline>(animationDuration)) {}

Animations::BaseSplineAnimation::~BaseSplineAnimation() {
  _startListeners.clear();
  _completeListeners.clear();
}

void Animations::BaseSplineAnimation::Update(float deltaTime) {
  _spline->Update(deltaTime);
  if (_spline->IsComplete()) {
    ProcessComplete();
  }
}

CoffeeMaker::Math::Vector2D Animations::BaseSplineAnimation::Position() const { return _spline->CurrentPosition(); };

void Animations::BaseSplineAnimation::Reset() { _spline->Reset(); }

void Animations::BaseSplineAnimation::DebugRender() const { _spline->DebugRender(); }

bool Animations::BaseSplineAnimation::Complete() const { return _spline->IsComplete(); }

void Animations::BaseSplineAnimation::OnStart(std::function<void(void*)> fn) { _startListeners.emplace_back(fn); }

void Animations::BaseSplineAnimation::OnComplete(std::function<void(void*)> fn) { _completeListeners.emplace_back(fn); }

void Animations::BaseSplineAnimation::ProcessStart() {
  for (auto fn : _startListeners) {
    std::invoke(fn, nullptr);
  }
}

void Animations::BaseSplineAnimation::ProcessComplete() {
  for (auto fn : _completeListeners) {
    std::invoke(fn, nullptr);
  }
}

//------------------------------------------------------------------------------------------
//----- EnemyEntrance ----------------------------------------------------------------------
//------------------------------------------------------------------------------------------

Animations::EnemyEntrance::EnemyEntrance() : Animations::BaseSplineAnimation(1.25f) {
  using Vec2 = CoffeeMaker::Math::Vector2D;

  _spline->AddCurve(Vec2{50, -50}, Vec2{50, 600}, Vec2{250, 600}, Vec2{250, 300});
  _spline->AddCurve(Vec2{250, 300}, Vec2{50, -150}, Vec2{50, 750}, Vec2{275, 150});

  _spline->Start();
}

Animations::EnemyBriefEntrance::EnemyBriefEntrance() : Animations::BaseSplineAnimation(1.0f) {
  using Vec2 = CoffeeMaker::Math::Vector2D;

  _spline->AddCurve(Vec2{-200.0f, 600.0f}, Vec2{0.0f, -50.0f}, Vec2{800.0f, 0.0f}, Vec2{400.0f, 150.0f});
  _spline->Start();
}

//------------------------------------------------------------------------------------------
//----- EnemyExit --------------------------------------------------------------------------
//------------------------------------------------------------------------------------------

Animations::EnemyExit::EnemyExit() : Animations::BaseSplineAnimation(1.25f) {
  using Vec2 = CoffeeMaker::Math::Vector2D;

  _spline->AddCurve(Vec2{400, 150}, Vec2{750, 900}, Vec2{750, -800}, Vec2{500, 900});
  _spline->Start();
}
