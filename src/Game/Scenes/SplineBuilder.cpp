#include "Game/Scenes/SplineBuilder.hpp"

#include <iostream>
#include <string>

#include "InputManager.hpp"
#include "Logger.hpp"
#include "Renderer.hpp"

SplineBuilder::SplineBuilder() :
    _backgroundColor(CoffeeMaker::Colors::Black),
    _bSpline(CreateScope<CoffeeMaker::BSpline>()),
    _bSplineCurvePoints({}),
    _bSplineControlPoints({}),
    _current(0) {}

SplineBuilder::~SplineBuilder() {}

void SplineBuilder::Render() {
  SDL_SetRenderDrawColor(CoffeeMaker::Renderer::Instance(), _backgroundColor.r, _backgroundColor.g, _backgroundColor.b,
                         _backgroundColor.a);
  SDL_RenderClear(CoffeeMaker::Renderer::Instance());

  for (auto& v : _bSplineControlPoints) {
    v->Render();
  }

  SDL_SetRenderDrawColor(CoffeeMaker::Renderer::Instance(), 255, 255, 255, 255);
  for (auto& curvePoint : _bSplineCurvePoints) {
    SDL_FRect s = SDL_FRect{.x = curvePoint.x, .y = curvePoint.y, .w = 1, .h = 1};
    SDL_RenderFillRectF(CoffeeMaker::Renderer::Instance(), &s);
  }
}

void SplineBuilder::Update(float) {
  for (auto& v : _bSplineControlPoints) {
    v->Update();
  }

  if (CoffeeMaker::InputManager::IsKeyPressed(SDL_SCANCODE_C)) {
    // clear the points
    _bSplineControlPoints.clear();
    _bSplineCurvePoints.clear();
    _current = 0;
  }

  if (CoffeeMaker::InputManager::IsKeyPressed(SDL_SCANCODE_R)) {
    std::vector<tinyspline::real> knot = _bSpline->GetKnots();
    for (auto& k : knot) {
      std::cout << k << std::endl;
    }
  }

  if (CoffeeMaker::InputManager::IsKeyPressed(SDL_SCANCODE_S)) {
    _bSpline->Save();
  }
}

void SplineBuilder::Init() {
  _bSpline->Load("assets/DroneEntrance1.spline");
  _bSpline->GenerateCurves();
}
void SplineBuilder::Destroy() {}
void SplineBuilder::Pause() {}
void SplineBuilder::Unpause() {}

void SplineBuilder::OnSDLUserEvent(const SDL_UserEvent&) {}

void SplineBuilder::OnMouseDown(const SDL_MouseButtonEvent& event) {
  if (CoffeeMaker::InputManager::IsKeyDown(SDL_SCANCODE_LSHIFT) && event.button == SDL_BUTTON_LEFT) {
    Ref<SplinePoint> splinePoint =
        CreateRef<SplinePoint>(static_cast<float>(event.x), static_cast<float>(event.y), _current);
    splinePoint->OnDrag([this](size_t i, float x, float y) {
      _bSpline->SetControlPointAt(i, CoffeeMaker::Math::Point2D{.x = x, .y = y});
      if (_current >= 4) {
        _bSpline->GenerateCurves();
        _bSplineCurvePoints = _bSpline->GetPoints();
      }
    });

    _bSplineControlPoints.push_back(splinePoint);
    _bSpline->AddControlPoint(splinePoint->GetPoint());
    _current++;
    if (_current >= 4) {
      _bSpline->GenerateCurves();
      _bSplineCurvePoints = _bSpline->GetPoints();
    }
  }
}

void SplineBuilder::OnMouseUp(const SDL_MouseButtonEvent&) {}
void SplineBuilder::OnMouseWheel(const SDL_MouseWheelEvent&) {}
void SplineBuilder::OnMouseMove(const SDL_MouseMotionEvent&) {}
