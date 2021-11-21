#include "Game/Scenes/SplineBuilder.hpp"

#include <iostream>
#include <string>

#include "InputManager.hpp"
#include "Logger.hpp"
#include "Renderer.hpp"

SplineBuilder::SplineBuilder() :
    _backgroundColor(CoffeeMaker::Colors::Black),
    _spline(nullptr),
    _vec2({}),
    _points({}),
    _spline2({}),
    _bezierSplinePoints({}),
    _bspline(CreateScope<tinyspline::BSpline>(8)),
    _current(0),
    _bsplineConPts({}) {}

SplineBuilder::~SplineBuilder() {}

void SplineBuilder::Render() {
  SDL_SetRenderDrawColor(CoffeeMaker::Renderer::Instance(), _backgroundColor.r, _backgroundColor.g, _backgroundColor.b,
                         _backgroundColor.a);
  SDL_RenderClear(CoffeeMaker::Renderer::Instance());

  SDL_SetRenderDrawColor(CoffeeMaker::Renderer::Instance(), 255, 255, 255, 255);
  for (auto& v : _points) {
    SDL_FRect s = SDL_FRect{.h = 16, .w = 16, .x = v.x, .y = v.y};
    SDL_RenderDrawRectF(CoffeeMaker::Renderer::Instance(), &s);
  }

  // for (unsigned int i = 0; i < _bsplineConPts.size(); i++) {
  //   SDL_FRect s = SDL_FRect{.h = 4, .w = 4, .x = _bsplineConPts[i].x, .y = _bsplineConPts[i].y};
  //   SDL_RenderFillRectF(CoffeeMaker::Renderer::Instance(), &s);
  // }

  for (unsigned int i = 0; i < _bezierSplinePoints.size() / 2; i++) {
    SDL_RenderDrawPointF(CoffeeMaker::Renderer::Instance(), _bezierSplinePoints[i * 2], _bezierSplinePoints[i * 2 + 1]);
  }

  for (auto& splinePoint : _splinePoints) {
    splinePoint->Render();
  }
}
void SplineBuilder::Update(float) {
  for (auto& splinePoint : _splinePoints) {
    splinePoint->Update();
  }

  if (CoffeeMaker::InputManager::IsKeyPressed(SDL_SCANCODE_C)) {
    // clear the points
    _vec2.clear();
    _bsplineConPts.clear();
    _bezierSplinePoints.clear();
    _current = 0;
    // _spline->Reset();
    // _spline2.clear();
    // _points.clear();
  }

  if (CoffeeMaker::InputManager::IsKeyPressed(SDL_SCANCODE_R)) {
    // _spline->Reset();
    _spline2.clear();
    _points.clear();
  }

  if (CoffeeMaker::InputManager::IsKeyPressed(SDL_SCANCODE_UP)) {
    if (!_points.empty()) {
      _points.back().weight++;
      _spline2 = CoffeeMaker::Math::SplineCurve(_points);
    }
  }

  if (CoffeeMaker::InputManager::IsKeyPressed(SDL_SCANCODE_DOWN)) {
    if (!_points.empty()) {
      _points.back().weight--;
      _spline2 = CoffeeMaker::Math::SplineCurve(_points);
    }
  }

  if (CoffeeMaker::InputManager::IsKeyPressed(SDL_SCANCODE_1)) {
    if (!_points.empty()) {
      _points.back().weight = 1.0f;
      _spline2 = CoffeeMaker::Math::SplineCurve(_points);
    }
  }
}

void SplineBuilder::Init() {}
void SplineBuilder::Destroy() {}
void SplineBuilder::Pause() {}
void SplineBuilder::Unpause() {}

void SplineBuilder::OnSDLUserEvent(const SDL_UserEvent&) {}

void SplineBuilder::OnMouseDown(const SDL_MouseButtonEvent& event) {
  // NOTE: just print to test this....
  // CoffeeMaker::Logger::Trace("Mouse button down " + std::to_string(event.button));
  // _vec2.push_back(CoffeeMaker::Math::Vector2D(event.x, event.y));
  if (CoffeeMaker::InputManager::IsKeyDown(SDL_SCANCODE_LSHIFT)) {
    _splinePoints.push_back(CreateRef<SplinePoint>((float)event.x, (float)event.y));
    std::vector<double> cp{static_cast<double>(event.x), static_cast<double>(event.y)};
    _bspline->setControlPointAt(_current++, cp);
    _bsplineConPts.push_back(
        CoffeeMaker::Math::Point2D{.x = static_cast<float>(event.x), .y = static_cast<float>(event.y), .weight = 1.0f});
    if (_current == 8) {
      _bezierSplinePoints = _bspline->sample(1000);
    }
  }

  // _points.push_back(
  //     CoffeeMaker::Math::Point2D{.x = static_cast<float>(event.x), .y = static_cast<float>(event.y), .weight
  //     = 1.0f});
  // if (_vec2.size() == 4) {
  //   _spline = CreateScope<CoffeeMaker::Spline>(5.0f);
  //   _spline->AddCurve(_vec2[0], _vec2[1], _vec2[2], _vec2[3]);
  //   _spline->Run(1000.0f);
  // }
  // _spline2 = CoffeeMaker::Math::SplineCurve(_points);
}

void SplineBuilder::OnMouseUp(const SDL_MouseButtonEvent&) {}
void SplineBuilder::OnMouseWheel(const SDL_MouseWheelEvent&) {}

void SplineBuilder::OnMouseMove(const SDL_MouseMotionEvent&) {
  // NOTE: just print to test this....
}
