#include "Spline.hpp"

#include <SDL2/SDL.h>

#include "Color.hpp"
#include "Renderer.hpp"

CoffeeMaker::Spline::Spline() :
    _spline({}),
    _currentSegment({}),
    _time(3.0f),
    _offset(0),
    _currentTime(0),
    _finalOffset(0),
    _complete(false),
    _weight(0.0f) {}

CoffeeMaker::Spline::Spline(float animationTime) :
    _spline({}),
    _currentSegment({}),
    _time(animationTime),
    _offset(0),
    _currentTime(0),
    _finalOffset(0),
    _complete(false),
    _weight(0.0f) {}

CoffeeMaker::Spline::~Spline() {
  _trail.clear();
  _currentSegment.clear();
  _spline.clear();
}

void CoffeeMaker::Spline::AddCurve(const Vec2& start, const Vec2& control1, const Vec2& control2, const Vec2& end) {
  _spline.emplace_back(start);
  _spline.emplace_back(control1);
  _spline.emplace_back(control2);
  _spline.emplace_back(end);
  _finalOffset = static_cast<unsigned int>(_spline.size());
}

float CoffeeMaker::Spline::Weight() { return _spline.size() / 4.0f; }

void CoffeeMaker::Spline::Start() {
  _currentSegment.emplace_back(_spline.at(0));
  _currentSegment.emplace_back(_spline.at(1));
  _currentSegment.emplace_back(_spline.at(2));
  _currentSegment.emplace_back(_spline.at(3));
  _offset = 0;
}

void CoffeeMaker::Spline::Reset() {
  _trail.clear();
  _currentSegment.clear();
  Start();
  _complete = false;
  _currentTime = 0;
  _weight = 0;
}

bool CoffeeMaker::Spline::IsComplete() const { return _complete; }

void CoffeeMaker::Spline::Update(float deltaTime) {
  _currentTime += deltaTime;
  _weight = _currentTime / (_time / (_spline.size() * 0.25f));

  if (_weight >= 1.0f && !_complete) {
    _currentTime = 0;
    _offset += 4;
    _weight = 0;
    // Are we done?
    if (_offset == _finalOffset) {
      _complete = true;
      return;
    }
    _currentSegment.clear();
    _currentSegment.emplace_back(_spline.at(_offset));
    _currentSegment.emplace_back(_spline.at(_offset + 1));
    _currentSegment.emplace_back(_spline.at(_offset + 2));
    _currentSegment.emplace_back(_spline.at(_offset + 3));
  }
}

void CoffeeMaker::Spline::DebugRender() const {
  // Debug Bezier Curve
  for (auto& point : _trail) {
    SDL_SetRenderDrawColor(CoffeeMaker::Renderer::Instance(), CoffeeMaker::Colors::Yellow.r,
                           CoffeeMaker::Colors::Yellow.g, CoffeeMaker::Colors::Yellow.b, CoffeeMaker::Colors::Yellow.a);
    SDL_RenderDrawPointF(CoffeeMaker::Renderer::Instance(), point.x, point.y);
    CoffeeMaker::Renderer::IncDrawCalls();
  }
}

CoffeeMaker::Math::Vector2D CoffeeMaker::Spline::CurrentPosition() {
  using Vec2 = CoffeeMaker::Math::Vector2D;
  if (_complete) {
    return _spline.at(_spline.size() - 1);
  }
  Vec2 p = CoffeeMaker::Math::CubicBezierCurve(_currentSegment[0], _currentSegment[1], _currentSegment[2],
                                               _currentSegment[3], _weight);
  // NOTE: nice for debugging, but when the game is paused this could lead to a soft memory leak.
  _trail.emplace_back(p);
  return p;
}

void CoffeeMaker::Spline::Run(float precision) {
  _trail.clear();
  float w = 0.0f;
  for (float i = 0.0f; i < precision; i++) {
    w = i / precision;
    _trail.emplace_back(CoffeeMaker::Math::CubicBezierCurve(_spline[0], _spline[1], _spline[2], _spline[3], w));
  }
}
