#include "Game/Animations/EnemyAnimations.hpp"

#include "Logger.hpp"

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

CoffeeMaker::Math::Vector2D Animations::BaseSplineAnimation::Position() const { return _spline->CurrentPosition(); }

void Animations::BaseSplineAnimation::Reset() { _spline->Reset(); }

void Animations::BaseSplineAnimation::DebugRender() const { _spline->DebugRender(); }

bool Animations::BaseSplineAnimation::Complete() const { return _spline->IsComplete(); }

void Animations::BaseSplineAnimation::OnStart(std::function<void(void *)> fn) { _startListeners.emplace_back(fn); }

void Animations::BaseSplineAnimation::OnComplete(std::function<void(void *)> fn) {
  _completeListeners.emplace_back(fn);
}

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

  _spline->AddCurve(Vec2{-200.0f, 600.0f}, Vec2{0.0f, -50.0f}, Vec2{800.0f, 0.0f}, Vec2{400.0f, 100.0f});
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

Animations::SplineAnimation::SplineAnimation() {}

Animations::SplineAnimation::~SplineAnimation() {
  _startListeners.clear();
  _completeListeners.clear();
}

void Animations::SplineAnimation::OnStart(std::function<void(void *)> fn) { _startListeners.push_back(fn); }

void Animations::SplineAnimation::OnComplete(std::function<void(void *)> fn) { _completeListeners.push_back(fn); }

Scope<CoffeeMaker::BSpline> Animations::EnemyEntrance001::_bSpline = nullptr;

void Animations::EnemyEntrance001::LoadBSpline() {
  using Pt2 = CoffeeMaker::Math::Point2D;
  _bSpline = CreateScope<CoffeeMaker::BSpline>();
  _bSpline->AddControlPoint(Pt2{.x = 0, .y = 0});
  _bSpline->AddControlPoint(Pt2{.x = 28, .y = 111});
  _bSpline->AddControlPoint(Pt2{.x = 50, .y = 220});
  _bSpline->AddControlPoint(Pt2{.x = 80, .y = 327});
  _bSpline->AddControlPoint(Pt2{.x = 117, .y = 421});
  _bSpline->AddControlPoint(Pt2{.x = 189, .y = 446});
  _bSpline->AddControlPoint(Pt2{.x = 249, .y = 408});
  _bSpline->AddControlPoint(Pt2{.x = 263, .y = 362});
  _bSpline->AddControlPoint(Pt2{.x = 266, .y = 287});
  _bSpline->AddControlPoint(Pt2{.x = 179, .y = 252});
  _bSpline->AddControlPoint(Pt2{.x = 134, .y = 273});
  _bSpline->AddControlPoint(Pt2{.x = 109, .y = 318});
  _bSpline->AddControlPoint(Pt2{.x = 110, .y = 358});
  _bSpline->AddControlPoint(Pt2{.x = 122, .y = 392});

  _bSpline->AddControlPoint(Pt2{.x = 151, .y = 417});
  _bSpline->AddControlPoint(Pt2{.x = 230, .y = 405});
  _bSpline->AddControlPoint(Pt2{.x = 273, .y = 347});
  _bSpline->AddControlPoint(Pt2{.x = 298, .y = 295});
  _bSpline->AddControlPoint(Pt2{.x = 297, .y = 235});
  _bSpline->AddControlPoint(Pt2{.x = 263, .y = 195});

  _bSpline->AddControlPoint(Pt2{.x = 196, .y = 181});
  _bSpline->AddControlPoint(Pt2{.x = 150, .y = 228});
  _bSpline->AddControlPoint(Pt2{.x = 152, .y = 299});
  _bSpline->AddControlPoint(Pt2{.x = 174, .y = 329});
  _bSpline->AddControlPoint(Pt2{.x = 246, .y = 336});
  _bSpline->AddControlPoint(Pt2{.x = 308, .y = 288});
  _bSpline->AddControlPoint(Pt2{.x = 344, .y = 225});

  _bSpline->AddControlPoint(Pt2{.x = 366, .y = 171});
  _bSpline->AddControlPoint(Pt2{.x = 403, .y = 93});
  _bSpline->AddControlPoint(Pt2{.x = 421, .y = 63});
}

Animations::EnemyEntrance001::EnemyEntrance001(float duration) : _knot(0.0f), _currentTime(0.0f), _duration(duration) {
  if (_bSpline == nullptr) {
    LoadBSpline();
  }
}

void Animations::EnemyEntrance001::Reset() {
  _knot = 0.0f;
  _currentTime = 0.0f;
  _currentPoint = _bSpline->Point2DAtKnot(_knot);
}

void Animations::EnemyEntrance001::Update(float deltaTime) {
  _currentTime += deltaTime;
  _knot = _currentTime / _duration;
  _currentPoint = _bSpline->Point2DAtKnot(_knot);
  if (_knot >= 1.0f) {
    for (auto f : _completeListeners) {
      f(nullptr);
    }
  }
}

void Animations::EnemyEntrance001::SetFinalPosition(const CoffeeMaker::Math::Point2D &pos) {
  _bSpline->SetControlPointAt(_bSpline->NumControlPoints() - 1, pos);
}

CoffeeMaker::Math::Point2D Animations::EnemyEntrance001::CurrentPosition() { return _currentPoint; }
